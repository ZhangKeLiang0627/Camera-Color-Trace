#include "EasyTracered.h"
#include "stm32f4xx.h"

extern uint16_t lcd_buff[240 * 120];

#define min3v(v1, v2, v3) ((v1) > (v2) ? ((v2) > (v3) ? (v3) : (v2)) : ((v1) > (v3) ? (v3) : (v1))) // ȡ���
#define max3v(v1, v2, v3) ((v1) < (v2) ? ((v2) < (v3) ? (v3) : (v2)) : ((v1) < (v3) ? (v3) : (v1))) // ȡ��Сֵ

typedef struct
{
	unsigned char red;	 // [0,255]
	unsigned char green; // [0,255]
	unsigned char blue;	 // [0,255]
} COLOR_RGB;			 // RGB��ʽ��ɫ

typedef struct
{
	unsigned char hue;		  // [0,240]
	unsigned char saturation; // [0,240]
	unsigned char luminance;  // [0,240]
} COLOR_HSL;				  // HSL��ʽ��ɫ

typedef struct
{
	unsigned int X_Start;
	unsigned int X_End;
	unsigned int Y_Start;
	unsigned int Y_End;
} SEARCH_AREA; // ����

// ת�ҶȺ���
void Gray(unsigned short *p)
{
	COLOR_RGB Rgb;
	int l, maxVal, minVal;
	Rgb.red = (unsigned char)((*p & 0xf800) >> 8);
	Rgb.green = (unsigned char)((*p & 0x07e0) >> 3);
	Rgb.blue = (unsigned char)((*p & 0x001f) << 3);

	maxVal = max3v(Rgb.red, Rgb.green, Rgb.blue);
	minVal = min3v(Rgb.red, Rgb.green, Rgb.blue);

	l = (maxVal + minVal) * 240 / 255 / 2;
	if (l > ThresholdValue)
		*p = 0xffff;
	else
		*p = 0x0000;
}

// ��ȡRBG��ʽ��ɫ��Ψһ��Ҫ��ֲ�ĺ���
unsigned short LCD_ReadPoint(unsigned short x, unsigned short y) // ��ĳ����ɫ
{
	return lcd_buff[x + 240 * y];
}

static void ReadColor(unsigned int x, unsigned int y, COLOR_RGB *Rgb)
{
	unsigned short C16;

	C16 = LCD_ReadPoint(x, y); // ��ĳ����ɫ

	Rgb->red = (unsigned char)((C16 & 0xf800) >> 8);
	Rgb->green = (unsigned char)((C16 & 0x07e0) >> 3);
	Rgb->blue = (unsigned char)((C16 & 0x001f) << 3);
}

// RGBתHSL
static void RGBtoHSL(const COLOR_RGB *Rgb, COLOR_HSL *Hsl)
{
	int h, s, l, maxVal, minVal, difVal;
	int r = Rgb->red;
	int g = Rgb->green;
	int b = Rgb->blue;

	maxVal = max3v(r, g, b);
	minVal = min3v(r, g, b);

	difVal = maxVal - minVal;

	// ��������
	l = (maxVal + minVal) * 240 / 255 / 2;

	if (maxVal == minVal) // ��r=g=b
	{
		h = 0;
		s = 0;
	}
	else
	{
		// ����ɫ��
		if (maxVal == r)
		{
			if (g >= b)
				h = 40 * (g - b) / (difVal);
			else
				h = 40 * (g - b) / (difVal) + 240;
		}
		else if (maxVal == g)
			h = 40 * (b - r) / (difVal) + 80;
		else if (maxVal == b)
			h = 40 * (r - g) / (difVal) + 160;
		// ���㱥�Ͷ�
		if (l == 0)
			//	s = 0;
			s = (difVal)*240 / (511 - (maxVal + minVal));
		else if (l <= 120)
			s = (difVal)*240 / (maxVal + minVal);
		else
			s = (difVal)*240 / (511 - (maxVal + minVal));
	}
	Hsl->hue = (unsigned char)(((h > 240) ? 240 : ((h < 0) ? 0 : h)));		  // ɫ��
	Hsl->saturation = (unsigned char)(((s > 240) ? 240 : ((s < 0) ? 0 : s))); // ���Ͷ�
	Hsl->luminance = (unsigned char)(((l > 240) ? 240 : ((l < 0) ? 0 : l)));  // ����
}

// ƥ����ɫ
static int ColorMatch(const COLOR_HSL *Hsl, const TARGET_CONDI *Condition) // HSL��ʽ��ɫ���ж�Ϊ��Ŀ������
{
	if (
		Hsl->hue > Condition->H_MIN &&
		Hsl->hue < Condition->H_MAX &&
		Hsl->saturation > Condition->S_MIN &&
		Hsl->saturation < Condition->S_MAX &&
		Hsl->luminance > Condition->L_MIN &&
		Hsl->luminance < Condition->L_MAX) // hueΪɫ����saturationΪ���Ͷ� ��luminanceΪ����
		return 1;
	else
		return 0;
}

// ������ʴ����
static int SearchCentre(unsigned int *x, unsigned int *y, const TARGET_CONDI *Condition, const SEARCH_AREA *Area)
// TARGET_CONDI�ж�Ϊ��Ŀ��������SEARCH_AREA����
{
	unsigned int SpaceX, SpaceY, i, j, k, FailCount = 0;
	COLOR_RGB Rgb;
	COLOR_HSL Hsl;

	SpaceX = Condition->WIDTH_MIN / 3; // Ŀ����С����
	SpaceY = Condition->HEIGHT_MIN / 3; // Ŀ����С�߶�

	for (i = Area->Y_Start; i < Area->Y_End; i += SpaceY) // i����������ʼ�㣬iС����������㣬iÿ���Լ�Ŀ����С�߶ȵ�1/3
	{
		for (j = Area->X_Start; j < Area->X_End; j += SpaceX) // j���ں�����ʼ��,jС�ں�������㣬jÿ���Լ�Ŀ����С����1/3
		{
			FailCount = 0;
			for (k = 0; k < SpaceX + SpaceY; k++) // kС��Ŀ����С������Ŀ����С�߶Ⱥ�
			{
				if (k < SpaceX)										   // ���kС��Ŀ����С����
					ReadColor(j + k, i + SpaceY / 2, &Rgb);			   // ����j+k,i+SpaceY/2����ɫ
				else												   // ����
					ReadColor(j + SpaceX / 2, i + (k - SpaceX), &Rgb); // ����j+SpaceX/2,i+(k-SpaceX)����ɫ
				RGBtoHSL(&Rgb, &Hsl);								   // RGBתHSL

				if (!ColorMatch(&Hsl, Condition))					   // �����ɫƥ�䲻�ɹ�
					FailCount++;									   // ʧ�ܼ���
				if (FailCount > ((SpaceX + SpaceY) >> ALLOW_FAIL_PER)) // ���ʧ�ܴ��������ݴ���
					break;											   // ����ѭ��
			}
			if (k == SpaceX + SpaceY) // ���k����Ŀ����С������Ŀ����С�߶Ⱥ�
			{
				*x = j + SpaceX / 2;
				*y = i + SpaceY / 2;
				return 1;
			}
		}
	}
	return 0;
}
// �Ӹ�ʴ�������ⸯʴ���õ��µĸ�ʴ����
static int Corrode(unsigned int oldx, unsigned int oldy, const TARGET_CONDI *Condition, RESULT *Resu)
{
	unsigned int Xmin, Xmax, Ymin, Ymax, i, FailCount = 0;
	COLOR_RGB Rgb;
	COLOR_HSL Hsl;

	for (i = oldx; i > IMG_X; i--)
	{
		ReadColor(i, oldy, &Rgb);
		RGBtoHSL(&Rgb, &Hsl);
		if (!ColorMatch(&Hsl, Condition))
			FailCount++;
		if (FailCount > (((Condition->WIDTH_MIN + Condition->WIDTH_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Xmin = i;
	FailCount = 0;

	for (i = oldx; i < IMG_X + IMG_W; i++)
	{
		ReadColor(i, oldy, &Rgb);
		RGBtoHSL(&Rgb, &Hsl);
		if (!ColorMatch(&Hsl, Condition))
			FailCount++;
		if (FailCount > (((Condition->WIDTH_MIN + Condition->WIDTH_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Xmax = i;
	FailCount = 0;

	for (i = oldy; i > IMG_Y; i--)
	{
		ReadColor(oldx, i, &Rgb);
		RGBtoHSL(&Rgb, &Hsl);
		if (!ColorMatch(&Hsl, Condition))
			FailCount++;
		if (FailCount > (((Condition->HEIGHT_MIN + Condition->HEIGHT_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Ymin = i;
	FailCount = 0;

	for (i = oldy; i < IMG_Y + IMG_H; i++)
	{
		ReadColor(oldx, i, &Rgb);
		RGBtoHSL(&Rgb, &Hsl);
		if (!ColorMatch(&Hsl, Condition))
			FailCount++;
		if (FailCount > (((Condition->HEIGHT_MIN + Condition->HEIGHT_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Ymax = i;
	FailCount = 0;

	Resu->x = (Xmin + Xmax) / 2;
	Resu->y = (Ymin + Ymax) / 2;
	Resu->w = Xmax - Xmin;
	Resu->h = Ymax - Ymin;

	if (
		((Xmax - Xmin) > (Condition->WIDTH_MIN)) && ((Ymax - Ymin) > (Condition->HEIGHT_MIN)) &&
		((Xmax - Xmin) < (Condition->WIDTH_MAX)) && ((Ymax - Ymin) < (Condition->HEIGHT_MAX)))
		return 1;
	else
		return 0;
}

// Ψһ��API���û���ʶ������д��Conditionָ��Ľṹ���У��ú���������Ŀ���x��y����ͳ���
// ����1ʶ��ɹ�������1ʶ��ʧ��
int Trace(const TARGET_CONDI *Condition, RESULT *Resu) // TARGET_CONDIʶ������  RESULTʶ����
{
	unsigned int i;
	static unsigned int x0, y0, flag = 0;									// ��̬����
	static SEARCH_AREA Area = {IMG_X, IMG_X + IMG_W, IMG_Y, IMG_Y + IMG_H}; // x���� y����  w����  h�߶�
	RESULT Result;															// RESULTʶ����

	if (flag == 0) // �Ѿ�����
	{
		if (SearchCentre(&x0, &y0, Condition, &Area)) // ������ʴ����   &��ȡ��ַ�����
			flag = 1;
		else
		{
			Area.X_Start = IMG_X;
			Area.X_End = IMG_X + IMG_W;
			Area.Y_Start = IMG_Y;
			Area.Y_End = IMG_Y + IMG_H;

			if (SearchCentre(&x0, &y0, Condition, &Area))
			{
				flag = 0;
				return 0;
			}
		}
	}
	Result.x = x0;
	Result.y = y0;

	for (i = 0; i < ITERATE_NUM; i++) // ���е�������
		Corrode(Result.x, Result.y, Condition, &Result);

	if (Corrode(Result.x, Result.y, Condition, &Result)) // �Ӹ�ʴ�������ⸯʴ
	{
		x0 = Result.x;
		y0 = Result.y;
		Resu->x = Result.x;
		Resu->y = Result.y;
		Resu->w = Result.w;
		Resu->h = Result.h;
		flag = 1;

		Area.X_Start = Result.x - ((Result.w) >> 1);
		Area.X_End = Result.x + ((Result.w) >> 1);
		Area.Y_Start = Result.y - ((Result.h) >> 1);
		Area.Y_End = Result.y + ((Result.h) >> 1);

		return 1;
	}
	else
	{
		flag = 0;
		return 0;
	}
}

/*Camera*/
extern uint16_t lcd_buff[240 * 120];

// ƥ���ɫ
static int BlackColorMatch(const uint16_t color_buff)
{
	if (color_buff == 0x0) // ��ɫ����1
		return 1;
	else
		return 0;
}

// ������ʴ����
static int SearchBlackCentre(unsigned int *x, unsigned int *y, const TARGET_CONDI *Condition, const SEARCH_AREA *Area)
// TARGET_CONDI�ж�Ϊ��Ŀ��������SEARCH_AREA����
{
	unsigned int SpaceX, SpaceY, i, j, k, FailCount = 0;
	uint16_t tmp_buff;

	SpaceX = Condition->WIDTH_MIN / 3; // Ŀ����С����
	SpaceY = Condition->HEIGHT_MIN / 3; // Ŀ����С�߶�

	for (i = Area->Y_Start; i < Area->Y_End; i += SpaceY) // i����������ʼ�㣬iС����������㣬iÿ���Լ�Ŀ����С�߶ȵ�1/3
	{
		for (j = Area->X_Start; j < Area->X_End; j += SpaceX) // j���ں�����ʼ��,jС�ں�������㣬jÿ���Լ�Ŀ����С����1/3
		{
			FailCount = 0;
			for (k = 0; k < SpaceX + SpaceY; k++) // kС��Ŀ����С������Ŀ����С�߶Ⱥ�
			{
				if (k < SpaceX) // ���kС��Ŀ����С����
					// ReadColor(j + k, i + SpaceY / 2, &Rgb);			   // ����j+k,i+SpaceY/2����ɫ
					tmp_buff = LCD_ReadPoint(j + k, i + SpaceY / 2);
				else													   // ����
					// LCD_ReadPoint(j + SpaceX / 2, i + (k - SpaceX), &Rgb); // ����j+SpaceX/2,i+(k-SpaceX)����ɫ
					tmp_buff = LCD_ReadPoint(j + SpaceX / 2, i + (k - SpaceX));								   

				if (!BlackColorMatch(tmp_buff))					   			// �����ɫƥ�䲻�ɹ�
					FailCount++;									   // ʧ�ܼ���
				if (FailCount > ((SpaceX + SpaceY) >> ALLOW_FAIL_PER)) // ���ʧ�ܴ��������ݴ���
					break;											   // ����ѭ��
			}
			if (k == SpaceX + SpaceY) // ���k����Ŀ����С������Ŀ����С�߶Ⱥ�
			{
				*x = j + SpaceX / 2;
				*y = i + SpaceY / 2;
				return 1;
			}
		}
	}
	return 0;
}
// �Ӹ�ʴ�������ⸯʴ���õ��µĸ�ʴ����
static int BlackCorrode(unsigned int oldx, unsigned int oldy, const TARGET_CONDI *Condition, RESULT *Resu)
{
	uint16_t Xmin, Xmax, Ymin, Ymax, i, j, aa, FailCount = 0;
	uint16_t distance_X, dis_x, distance_Y, dis_y = 0;

	uint16_t tmp_buff;

	for (i = oldx; i > IMG_X; i--)
	{
		// ReadColor(i, oldy, &Rgb);
		tmp_buff = LCD_ReadPoint(i, oldy);
		if (!BlackColorMatch(tmp_buff))
			FailCount++;
		if (FailCount > ((Condition->WIDTH_MIN) / 4)) // ʶ���ݴ��ʣ�����Сɫ��Ϊ40����40/4=10����ζ��ʶ�𳬹�10��ʧ�ܣ�������ǰʶ��
			break;
	}
	Xmin = i;
	FailCount = 0;

	for (i = oldx; i < IMG_X + IMG_W; i++)
	{
		tmp_buff = LCD_ReadPoint(i, oldy);
		if (!BlackColorMatch(tmp_buff))
			FailCount++;
		if (FailCount > ((Condition->WIDTH_MIN) / 4))
			break;
	}
	Xmax = i;
	FailCount = 0;

	// FailCount = 0; // ʧ�ܴ�������
	// Xmax = i;	   // ��������������õ�
	dis_y = oldy;
	Ymax = Ymin = oldy;

	// /*����ʶ��ɫ��Y�ᣨ���ȣ�*/
	// for (i = Xmin; i < Xmax; i++) // ���ϸ�ʴ
	// {
	// 	for (j = dis_y; j > IMG_Y; j--)
	// 	{
	// 		tmp_buff = LCD_ReadPoint(oldx, i);
	// 		if (!BlackColorMatch(tmp_buff))
	// 			FailCount++;
	// 		if (FailCount > ((Condition->WIDTH_MIN) / ALLOW_FAIL_PER))
	// 			break;
	// 	}
	// 	if (j < Ymin)
	// 		Ymin = j; // ����ʶ�𵽵�Y�����Сֵ
	// 	FailCount = 0;

	// 	/*----------------------------------------------*/
	// 	for (aa = dis_y; aa < IMG_Y + IMG_H; aa++) // ���¸�ʴ
	// 	{
	// 		tmp_buff = LCD_ReadPoint(oldx, i);
	// 		if (!BlackColorMatch(tmp_buff))
	// 			FailCount++;
	// 		if (FailCount > ((Condition->WIDTH_MIN) / ALLOW_FAIL_PER))
	// 			break;
	// 	}
	// 	if (aa > Ymax)
	// 		Ymax = aa;					// ����ʶ�𵽵�Y������ֵ��distance_Y�Ǵ���Ymin&Ymax�Ĳ�ֵ��Ҳ��������ĸ߶�
	// 	if ((Ymax - Ymin) > distance_Y) // ����ʶ�𵽵���������¼x������꣬������õ�
	// 	{
	// 		distance_Y = Ymax - Ymin;
	// 		dis_x = i;
	// 	}
	// 	FailCount = 0;
	// }

	// /*����ʶ��ɫ��X�ᣨ�߶ȣ�*/
	// for (i = Ymin; i < Ymax; i++)
	// {
	// 	for (j = dis_x; j > IMG_X; j--) // ����ʴ����ֵ��С
	// 	{
	// 		tmp_buff = LCD_ReadPoint(oldx, i);
	// 		if (!BlackColorMatch(tmp_buff))
	// 			FailCount++;
	// 		if (FailCount > ((Condition->WIDTH_MIN) / ALLOW_FAIL_PER))
	// 			break;
	// 	}
	// 	if (j < Xmin)
	// 		Xmin = j;
	// 	FailCount = 0;

	// 	/*----------------------------------------------*/
	// 	for (aa = dis_x; aa < IMG_X + IMG_W; aa++) // ���Ҹ�ʴ����ֵ���
	// 	{
	// 		tmp_buff = LCD_ReadPoint(oldx, i);
	// 		if (!BlackColorMatch(tmp_buff))
	// 			FailCount++;
	// 		if (FailCount > ((Condition->WIDTH_MIN) / ALLOW_FAIL_PER))
	// 			break;
	// 	}
	// 	if (aa > Xmax)
	// 		Xmax = aa;
	// 	if ((Xmax - Xmin) > distance_X)
	// 	{
	// 		distance_X = Xmax - Xmin;
	// 	}
	// 	FailCount = 0;
	// }

	// FailCount = 0;

	/*����ƫ�����Ը�һ����ֵ���仯��֪����*/
	// Xmax -= 3;
	// Xmin += 3;
	// Ymax -= 3;
	// Ymin += 3;
	// distance_X = Xmax - Xmin;
	// distance_Y = Ymax - Ymin;

	for (i = oldy; i > IMG_Y; i--)
	{
		// ReadColor(oldx, i, &Rgb);
		tmp_buff = LCD_ReadPoint(oldx, i);
		if (!BlackColorMatch(tmp_buff))
			FailCount++;
		if (FailCount > (((Condition->HEIGHT_MIN + Condition->HEIGHT_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Ymin = i;
	FailCount = 0;

	for (i = oldy; i < IMG_Y + IMG_H; i++)
	{
		tmp_buff = LCD_ReadPoint(oldx, i);
		if (!BlackColorMatch(tmp_buff))
			FailCount++;
		if (FailCount > (((Condition->HEIGHT_MIN + Condition->HEIGHT_MAX) >> 2) >> ALLOW_FAIL_PER))
			break;
	}
	Ymax = i;
	FailCount = 0;

	Resu->x = (Xmin + Xmax) / 2;
	Resu->y = (Ymin + Ymax) / 2;
	Resu->w = Xmax - Xmin;
	Resu->h = Ymax - Ymin;
	// Resu->x = Xmin + (distance_X / 2);
	// Resu->y = Ymin + (distance_Y / 2);
	// Resu->w = distance_X;
	// Resu->h = distance_Y;

	// if ((Resu->w < Condition->WIDTH_MAX) && (Resu->h < Condition->HEIGHT_MAX))
		if (
			((Xmax - Xmin) > (Condition->WIDTH_MIN)) && ((Ymax - Ymin) > (Condition->HEIGHT_MIN)) &&
			((Xmax - Xmin) < (Condition->WIDTH_MAX)) && ((Ymax - Ymin) < (Condition->HEIGHT_MAX)))
		return 1; // �����ʴ�������û�г�������޶�������û��С����С�޶���������Ч��
	else
		return 0;
}

// Ψһ��API���û���ʶ������д��Conditionָ��Ľṹ���У��ú���������Ŀ���x��y����ͳ���
// ����1ʶ��ɹ�������1ʶ��ʧ��
int BlackTrace(const TARGET_CONDI *Condition, RESULT *Resu) // TARGET_CONDIʶ������  RESULTʶ����
{
	unsigned int i;
	static unsigned int x0, y0, flag = 0;									// ��̬����
	static SEARCH_AREA Area = {IMG_X, IMG_X + IMG_W, IMG_Y, IMG_Y + IMG_H}; // x���� y����  w����  h�߶�
	RESULT Result;															// RESULTʶ����

	if (flag == 0) // �Ѿ�����
	{
		if (SearchBlackCentre(&x0, &y0, Condition, &Area)) // ������ʴ����   &��ȡ��ַ�����
			flag = 1;
		else
		{
			Area.X_Start = IMG_X;
			Area.X_End = IMG_X + IMG_W;
			Area.Y_Start = IMG_Y;
			Area.Y_End = IMG_Y + IMG_H;

			if (SearchBlackCentre(&x0, &y0, Condition, &Area))
			{
				flag = 0;
				return 0;
			}
		}
	}
	Result.x = x0;
	Result.y = y0;

	for (i = 0; i < ITERATE_NUM; i++) // ���е�������
		BlackCorrode(Result.x, Result.y, Condition, &Result);

	if (BlackCorrode(Result.x, Result.y, Condition, &Result)) // �Ӹ�ʴ�������ⸯʴ
	{
		x0 = Result.x;
		y0 = Result.y;
		Resu->x = Result.x;
		Resu->y = Result.y;
		Resu->w = Result.w;
		Resu->h = Result.h;
		flag = 1;

		Area.X_Start = Result.x - ((Result.w) >> 1);
		Area.X_End = Result.x + ((Result.w) >> 1);
		Area.Y_Start = Result.y - ((Result.h) >> 1);
		Area.Y_End = Result.y + ((Result.h) >> 1);

		return 1;
	}
	else
	{
		flag = 0;
		return 0;
	}
}