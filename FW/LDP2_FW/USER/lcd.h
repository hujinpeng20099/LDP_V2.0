#ifndef __LCD_H
#define __LCD_H

#include "main.h"


//-----------------OLED端口定义----------------  					   

#define OLED_SCLK_Clr() LL_GPIO_ResetOutputPin(LCD_SCK_GPIO_Port,LCD_SCK_Pin)//CLK
#define OLED_SCLK_Set() LL_GPIO_SetOutputPin(LCD_SCK_GPIO_Port,LCD_SCK_Pin)

#define OLED_SDIN_Clr() LL_GPIO_ResetOutputPin(LCD_MOSI_GPIO_Port,LCD_MOSI_Pin)//DIN
#define OLED_SDIN_Set() LL_GPIO_SetOutputPin(LCD_MOSI_GPIO_Port,LCD_MOSI_Pin)

#define OLED_RST_Clr() LL_GPIO_ResetOutputPin(LCD_RST_GPIO_Port,LCD_RST_Pin)//RES
#define OLED_RST_Set() LL_GPIO_SetOutputPin(LCD_RST_GPIO_Port,LCD_RST_Pin)

#define OLED_DC_Clr() LL_GPIO_ResetOutputPin(LCD_DC_GPIO_Port,LCD_DC_Pin)//DC
#define OLED_DC_Set() LL_GPIO_SetOutputPin(LCD_DC_GPIO_Port,LCD_DC_Pin)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


void OLED_Init(void);
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t f_w,uint8_t f_h,uint8_t mode);
void OLED_ShowString(uint8_t x,uint8_t y,char *p,uint8_t f_w,uint8_t f_h,uint8_t mode);
void OLED_Refresh_Gram(void);
void OLED_ShowPicture(uint8_t x,uint8_t y,const uint8_t *p,uint8_t p_w,uint8_t p_h);
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t f_w,uint8_t f_h,uint8_t mode);
void LDP_Show_ICON(void);
uint32_t mypow(uint8_t m,uint8_t n);

#endif





