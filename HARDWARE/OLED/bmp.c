#include "sys.h"
unsigned char BMP1[] =
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x80,0xA0,0x78,0x78,0x18,0x60,0xF0,0x70,0x70,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,0xC0,0xB8,0xBC,0x9C,0x00,0x70,
0x78,0xBC,0x9C,0x80,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xC0,0xC0,0xC0,0xD8,0xDC,0xDE,0x8C,0x80,0x10,0x38,0xBC,0xDC,0xC8,0x80,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0xB8,0xBC,0xBC,0x98,0x00,0x70,0x78,0x78,0x98,0x80,0x80,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,
0x07,0x1F,0x7F,0x7F,0x3F,0x1C,0x30,0x70,0x73,0x37,0x07,0x03,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x07,0x3F,0x3F,0x1F,0x0F,0x10,0x38,
0x39,0x3B,0x1B,0x03,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x07,0x0F,0x3F,0x3F,0x3F,0x07,0x08,0x1C,0x1D,0x1D,0x09,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x03,0x07,0x3F,0x7F,0x3F,0x1F,0x00,0x30,0x3B,0x3B,0x13,0x01,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x80,0x80,0x80,0xB0,0xB8,0xBC,0x18,0x00,0x20,0x70,0x78,0xB8,0x90,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xC0,0xC0,
0xD0,0xBC,0xBC,0x0C,0x30,0x78,0xB8,0xB8,0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x78,0x78,0x30,0x00,0xE0,0xF0,
0xF0,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0xB8,0xBC,0xBC,0x98,0x00,0x70,0x78,0x78,0x98,
0x80,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,
0xC0,0xC0,0xD0,0xBC,0xBC,0x0C,0x30,0x78,0xB8,0xB8,0x80,0x80,0x00,0x00,0x00,0x00,
0x00,0x01,0x03,0x0F,0x1F,0x7F,0x7F,0x7F,0x0F,0x10,0x38,0x3B,0x3B,0x13,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x0F,
0x3F,0x3F,0x1F,0x0E,0x18,0x38,0x39,0x1B,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x07,0x0F,0x7F,0xFF,0x7F,0x3E,0x00,0x60,
0x76,0x77,0x27,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x01,0x03,0x07,0x3F,0x7F,0x3F,0x1F,0x00,0x30,0x3B,0x3B,
0x13,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x03,0x0F,0x3F,0x3F,0x1F,0x0E,0x18,0x38,0x39,0x1B,0x03,0x01,0x00,0x00,0x00,0x00,//��ӡ1
};


unsigned char BMP2[][512] = 
{
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xE0,0xE0,0x40,0x40,0x20,0x20,0x20,0x20,0x20,0x20,0x40,0x60,0xE0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0xE0,0x60,0x40,0x20,0x20,0x20,0x20,0x20,0x20,0x40,0x40,0xE0,0xE0,
0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xB0,0x78,0x38,0x10,0x10,
0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x38,0xF8,0x30,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x60,0xF0,0x70,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x24,0x24,
0x74,0xF4,0x62,0x06,0x08,0x30,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0xF8,0x87,0x03,0x00,0x38,0x3C,0x1C,0x04,0x00,0x20,0x20,0x00,0x04,0x1C,0x39,
0x87,0x78,0x00,0x00,0x00,0x00,0x00,0xD8,0x3C,0x1C,0x08,0x08,0x04,0x04,0x04,0x04,
0x04,0x08,0x1C,0x3C,0xF0,0x88,0x08,0x08,0x08,0x10,0x60,0x80,0x00,0x00,0x00,0x00,
0x00,0xFC,0x03,0x70,0x38,0x08,0x40,0x40,0x00,0x08,0x38,0x78,0x70,0x00,0x80,0x81,
0x86,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x91,0xE0,0xC0,0xC0,0x80,
0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0xC0,0xFF,0x00,0x00,0x00,0x00,0x00,
0x00,0xE0,0x20,0xFC,0x83,0x00,0x70,0x38,0x08,0x00,0x40,0x40,0x00,0x08,0x38,0x78,
0x70,0x00,0x83,0xF8,0xE0,0xF0,0xFF,0x7E,0x38,0x30,0x00,0x00,0x00,0x00,0xE0,0xF8,
0xE6,0x81,0xBF,0xFF,0xFF,0xFF,0xFF,0x07,0x06,0x06,0x86,0xC6,0xF6,0xFF,0xFF,0xFF,
0x8F,0x00,0x00,0x00,0x00,0x00,0x3F,0x70,0xE0,0xE0,0xEE,0xEF,0x47,0xC1,0xC0,0xC8,
0xC8,0xC1,0xE7,0xF6,0xF0,0xBF,0x80,0xC0,0xF8,0xFF,0x7F,0x1F,0x00,0x00,0x00,0x00,
0x00,0x80,0xF1,0xFF,0x9E,0xC6,0xC6,0xC6,0xC6,0xC7,0x87,0x03,0x03,0x03,0x03,0x01,
0x01,0x01,0x87,0x78,0x00,0x00,0x00,0x00,0xE0,0xEE,0xFF,0x8F,0x07,0x03,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03,0x07,0xFE,0x00,0x00,0x00,0x00,
0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x01,0x01,0x00,0x01,0x03,0x03,0x03,0x01,0x01,0x01,0x03,0x03,0x03,0x01,0x01,0x01,
0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,
0x01,0x01,0x01,0x00,0x00,0x00,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x01,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0x02,0x02,0x02,0x02,
0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x03,0x03,0x02,0x02,0x02,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x01,0x00,0x00,0x00,0x00,0x00},//��è

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x30,0x18,0x38,0x6C,0x0C,0x0C,0x0C,0x6C,
0x3C,0x1C,0x3C,0x78,0x38,0x70,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x60,0x58,0xAC,0xAC,0x5E,0x36,0x06,0x06,0xE6,
0x76,0x56,0xBC,0x7C,0x38,0xF0,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x70,0x58,0xC8,0x8C,0x0C,0x0C,0x0C,0x8C,
0x8C,0xCC,0x4C,0x58,0x78,0x70,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0xC0,0x40,0x80,0x00,0x00,0x80,0xE0,0xF0,0x58,0x78,0xEC,0x0C,0x0C,
0x0C,0xEC,0x7C,0x5C,0xBC,0x78,0x38,0x70,0xE0,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0xC0,0x78,0x44,0x82,0x82,0x05,0x84,0x44,0x24,0x24,0xC0,0x00,0x00,0x04,
0x04,0x84,0x84,0x84,0x80,0x40,0x41,0x8F,0x87,0x44,0x38,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x81,0x81,0x80,0xE3,0x97,0x96,0xE3,0x80,0x80,0x80,0x86,
0x8F,0x8D,0x86,0x80,0x40,0x40,0x87,0x87,0x44,0x38,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x38,0x44,0x82,0x82,0x05,0x04,0x84,0x04,0x05,0x00,0x00,0x00,0x05,
0x84,0x84,0x84,0x44,0x44,0x20,0x21,0xC7,0x41,0x22,0x1C,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x02,0x7C,0x85,0x02,0x03,0x00,0x86,0x4D,0x2F,0x26,0xC0,0x00,
0x00,0x06,0x8D,0x8F,0x86,0x40,0x40,0xA0,0x21,0x47,0x43,0x22,0x1C,0x00,0x00,0x00,
0x00,0x00,0x00,0x01,0x01,0x02,0x02,0x05,0x19,0xE1,0x41,0x41,0x81,0x87,0x4B,0x55,
0x55,0x54,0xA2,0xA0,0x90,0x48,0x40,0xC7,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x06,0x0A,0x14,0x12,0x11,0x10,0x20,0xC0,0xA0,0x90,0x90,0x90,0x88,
0x88,0x88,0x88,0x88,0xE8,0x88,0x89,0x8A,0x94,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x0E,0x39,0xC7,0x41,0x41,0x81,0x81,0x41,0x41,0x41,
0x40,0x80,0x80,0x80,0x40,0x44,0xC8,0x30,0x13,0x1C,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,0x41,0x41,0x82,0x82,0x41,0x41,0x41,
0x41,0x41,0x40,0x8E,0x92,0xA4,0xA0,0xE0,0x1F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x0A,0x32,0x2E,0x12,0x02,0x02,
0x01,0x02,0x02,0x02,0x06,0x1A,0x22,0x3E,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x2E,0x32,0x2A,0x16,0x02,
0x02,0x03,0x02,0x06,0x0A,0x32,0x2E,0x12,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x26,0x3A,0x22,0x3E,0x02,0x01,0x02,
0x02,0x02,0x06,0x1A,0x22,0x3E,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x26,0x3A,0x22,0x1E,0x02,0x01,
0x02,0x02,0x02,0x06,0x1A,0x22,0x3E,0x23,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//С��

};







