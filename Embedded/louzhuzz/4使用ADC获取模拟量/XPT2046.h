#ifndef __XPT2046_H__
#define __XPT2046_H__

#define XPT2046_XP 0X9C
#define XPT2046_YP 0XDC
#define XPT2046_VBAT 0XAC
#define XPT2046_AUX 0XEC


unsigned int XPT2046_ReadAD(unsigned char Command);

#endif
