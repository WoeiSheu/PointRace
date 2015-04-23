#ifndef _OLED_H_
#define _OLED_H_
#include "include.h"

#define byte uint8
#define word uint16
#define GPIO_PIN_MASK      0x1Fu    //0x1f=31,限制位数为0--31有效
#define GPIO_PIN(x)        (((1)<<(x & GPIO_PIN_MASK)))  //把当前位置1

#define LCD_Port_Init()            gpio_init(PORTE,0, GPO,0);   \
                                   gpio_init(PORTE,2, GPO,0);   \
                                   gpio_init(PORTE,4, GPO,0);   \
                                   gpio_init(PORTE,6, GPO,0);   

  
#define LCD_SCL_HIGH    gpio_set(PORTE, 0, 1)         //D0
#define LCD_SCL_LOW     gpio_set(PORTE, 0, 0)

#define LCD_SDA_HIGH    gpio_set(PORTE, 2, 1)         //D1
#define LCD_SDA_LOW     gpio_set(PORTE, 2, 0)

#define LCD_RST_HIGH    gpio_set(PORTE, 4, 1)
#define LCD_RST_LOW     gpio_set(PORTE, 4, 0)

#define LCD_DC_HIGH     gpio_set(PORTE, 6, 1)
#define LCD_DC_LOW      gpio_set(PORTE, 6, 0)

 extern byte longqiu96x64[768];
 void LCD_Init(void);
 void LCD_CLS(void);
 void LCD_P6x8Str(byte x,byte y,byte ch[]);
 void LCD_P8x16Str(byte x,byte y,byte ch[]);
 void LCD_P14x16Str(byte x,byte y,byte ch[]);
 void LCD_Print(byte x, byte y, byte ch[]);
 void LCD_PutPixel(byte x,byte y);
 void LCD_Rectangle(byte x1,byte y1,byte x2,byte y2,byte gif);
 void Draw_LQLogo(void);
 void Draw_LibLogo(void);
 void Draw_BMP(byte x0,byte y0,byte x1,byte y1,byte bmp[]); 
 void LCD_Fill(byte dat);
#endif