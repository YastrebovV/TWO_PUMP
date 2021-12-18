#include "hd44780.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

GPIO_InitTypeDef port;
GPIO_InitTypeDef port1;

void _delay_ms(uint32_t ms)
{
    volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}
void _delay_us(uint32_t us)
{
    volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000000)*us;
        for (; nCount!=0; nCount--);
}

void lcd_init(void) {
	
	RCC_APB2PeriphClockCmd(PORT_DATA_RCC, ENABLE);
	port.GPIO_Pin = DB4 | DB5 | DB6 | DB7;
	port.GPIO_Mode = GPIO_Mode_Out_PP;
	port.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_DATA, &port);
	
	RCC_APB2PeriphClockCmd(PORT_SIG_RCC, ENABLE);
	port1.GPIO_Pin = RS | RW | EN;
	port1.GPIO_Mode = GPIO_Mode_Out_PP;
	port1.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(PORT_SIG, &port1);

	_delay_ms(40);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_SetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_ms(5);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_SetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200); //more 100us
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_SetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_DATA, DB7);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_SetBits(PORT_DATA, DB6);
	GPIO_SetBits(PORT_DATA, DB7);
	GPIO_SetBits(PORT_DATA, DB5);
	GPIO_SetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_SetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);

	GPIO_ResetBits(PORT_SIG, EN); // E V
	GPIO_SetBits(PORT_SIG, RS);
	GPIO_ResetBits(PORT_SIG, RW);
	GPIO_ResetBits(PORT_DATA, DB6);
	GPIO_ResetBits(PORT_DATA, DB7);
	GPIO_ResetBits(PORT_DATA, DB5);
	GPIO_ResetBits(PORT_DATA, DB4);
	GPIO_SetBits(PORT_SIG, EN); // E ^

	_delay_us(200);
	lcd_set_state(LCD_ENABLE,CURSOR_DISABLE,NO_BLINK);
	lcd_clear();
	lcd_send(0x06,COMMAND);
}

void lcd_set_user_char(uint8_t char_num, uint8_t * char_data) {
	uint8_t i;
	lcd_send(((1<<6) | (char_num * 8) ), COMMAND);
	for (i=0;i<=7;i++) {
		lcd_send(char_data[i],DATA);
	}
	lcd_send((1<<7), COMMAND);
}

void lcd_set_xy(uint8_t x, uint8_t y)  {

		lcd_send( (((((y)&1)*0x40)+((((y)&3)>>1)*0x14)+(x))|128),COMMAND);

}


void lcd_out(char * txt) {
	uint8_t byte_ru;
	uint8_t big_char_ru [56];
	uint8_t COUNT = 0;
	uint8_t COUNT2 = 0;
	uint8_t D1 = 0;
	uint8_t temp_var=0;
	 
	while(*txt) {
		byte_ru = *txt;
		
    if(byte_ru == 0xD1)
		  D1=1;
		
		if(byte_ru != 0xD0 && byte_ru != 0xD1){
			temp_var=*txt;
			if(temp_var==0x91 && D1==1)
				  temp_var = 0xF1; 
			if(temp_var==0x81 && D1==1)
				  temp_var = 0xF2; 	
		    big_char_ru[COUNT] = temp_var;						
			 COUNT++;
			 D1=0;
		}
		txt++;
		
	}
	for(int i =0; i<COUNT+COUNT2; i++){
		switch(big_char_ru[i]){
			case 0x90: byte_ru = 0x41; break;	
			case 0x91: byte_ru = 0xA0; break;
      case 0x92: byte_ru = 0x42; break;
			case 0x93: byte_ru = 0xA1; break;
			case 0x94: byte_ru = 0xE0; break;
			case 0x95: byte_ru = 0x45; break;
			case 0x81: byte_ru = 0xA2; break;
			case 0x96: byte_ru = 0xA3; break;
			case 0x97: byte_ru = 0xA4; break;
			case 0x98: byte_ru = 0xA5; break;
			case 0x99: byte_ru = 0xA6; break;
			case 0x9A: byte_ru = 0x4B; break;
			case 0x9B: byte_ru = 0xA7; break;
			case 0x9C: byte_ru = 0x4D; break;
			case 0x9D: byte_ru = 0x48; break;
			case 0x9E: byte_ru = 0x4F; break;
			case 0x9F: byte_ru = 0xA8; break;
			case 0xA0: byte_ru = 0x50; break;
			case 0xA1: byte_ru = 0x43; break;
			case 0xA2: byte_ru = 0x54; break;
			case 0xA3: byte_ru = 0xA9; break;
			case 0xA4: byte_ru = 0xAA; break;
			case 0xA5: byte_ru = 0x58; break;
			case 0xA6: byte_ru = 0xE1; break;
			case 0xA7: byte_ru = 0xAB; break;
			case 0xA8: byte_ru = 0xAC; break;
			case 0xA9: byte_ru = 0xE2; break;
			case 0xAA: byte_ru = 0xAD; break;
			case 0xAB: byte_ru = 0xAE; break;
			case 0xAC: byte_ru = 0xC4; break;
			case 0xAD: byte_ru = 0xAF; break;			
			case 0xAE: byte_ru = 0xB0; break;
			case 0xAF: byte_ru = 0xB1; break;
			
			case 0xB0: byte_ru = 0x61; break;
			case 0xB1: byte_ru = 0xB2; break;
			case 0xB2: byte_ru = 0xB3; break;
			case 0xB3: byte_ru = 0xB4; break;
			case 0xB4: byte_ru = 0x67; break;
			case 0xB5: byte_ru = 0x65; break;
			case 0xBE: byte_ru = 0x6F; break;
      case 0xBF: byte_ru = 0xBE; break;
			
			case 0xF1: byte_ru = 0xB5; break;	
			case 0x80: byte_ru = 0x70; break;
      case 0xF2: byte_ru = 0x63; break;
			case 0x82: byte_ru = 0xBF; break;
			case 0x83: byte_ru = 0x79; break;
			case 0x84: byte_ru = 0xE4; break;
			case 0x85: byte_ru = 0x78; break;
			case 0x86: byte_ru = 0xE5; break;
			case 0x87: byte_ru = 0xC0; break;
			case 0x88: byte_ru = 0xC1; break;
			case 0x89: byte_ru = 0xE6; break;
			case 0x8A: byte_ru = 0xC2; break;
			case 0x8B: byte_ru = 0xC3; break;
			case 0x8C: byte_ru = 0xC4; break;
			case 0x8D: byte_ru = 0xC5; break;
			case 0x8E: byte_ru = 0xC6; break;
		  case 0x8F: byte_ru = 0xC7; break;
			default: byte_ru = big_char_ru[i]; break;
			}
		if(byte_ru!=0x00){
       lcd_send(byte_ru,DATA);	
		}
		}

}

void lcd_clear(void) {
	lcd_send(0x01,COMMAND);
	_delay_ms(2);
}

void lcd_set_state(lcd_state state, cursor_state cur_state, cursor_mode cur_mode)  {
	if (state==LCD_DISABLE)  {
		lcd_send(0x08,COMMAND);
	} else {
		if (cur_state==CURSOR_DISABLE) {
			if (cur_mode==NO_BLINK)  {
				lcd_send(0x0C,COMMAND);
			} else {
				lcd_send(0x0D,COMMAND);
			}
		} else  {
			if (cur_mode==NO_BLINK)  {
				lcd_send(0x0E,COMMAND);
			} else {
				lcd_send(0x0F,COMMAND);
			}
		}
	}
}



void lcd_send(uint8_t byte, dat_or_comm dc)  {

	GPIO_ResetBits(PORT_DATA, DB7 | DB6 | DB5 | DB4);
	GPIO_ResetBits(PORT_SIG, RS | EN);
	//LCD_PORT->BSRR=(LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC | LCD_CD_BC | LCD_EN_BC);

	if (dc) {
		GPIO_SetBits(PORT_SIG, RS);
		//LCD_PORT->BSRR=LCD_CD_BS;
	}

	if (byte & 0x10) {
		GPIO_SetBits(PORT_DATA, DB4);
		//LCD_PORT->BSRR=LCD_DB4_BS;
	}
	if (byte & 0x20) {
		GPIO_SetBits(PORT_DATA, DB5);
		//LCD_PORT->BSRR=LCD_DB5_BS;
	}
	if (byte & 0x40) {
		GPIO_SetBits(PORT_DATA, DB6);
		//LCD_PORT->BSRR=LCD_DB6_BS;
	}
	if (byte & 0x80) {
		GPIO_SetBits(PORT_DATA, DB7);
		//LCD_PORT->BSRR=LCD_DB7_BS;
	}

	GPIO_SetBits(PORT_SIG, EN);
	//LCD_PORT->BSRR=LCD_EN_BS;
	_delay_ms(1);
	GPIO_ResetBits(PORT_SIG, EN);
	//LCD_PORT->BSRR=LCD_EN_BC;
	_delay_us(40);


	GPIO_ResetBits(PORT_DATA, DB7 | DB6 | DB5 | DB4);
	//LCD_PORT->BSRR=(LCD_DB7_BC | LCD_DB6_BC | LCD_DB5_BC | LCD_DB4_BC );

	if (byte & 0x01) {
		GPIO_SetBits(PORT_DATA, DB4);
		//LCD_PORT->BSRR=LCD_DB4_BS;
	}
	if (byte & 0x02) {
		GPIO_SetBits(PORT_DATA, DB5);
		//LCD_PORT->BSRR=LCD_DB5_BS;
	}
	if (byte & 0x04) {
		GPIO_SetBits(PORT_DATA, DB6);
		//LCD_PORT->BSRR=LCD_DB6_BS;
	}
	if (byte & 0x08) {
		GPIO_SetBits(PORT_DATA, DB7);
		//LCD_PORT->BSRR=LCD_DB7_BS;
	}

	GPIO_SetBits(PORT_SIG, EN);
	//LCD_PORT->BSRR=LCD_EN_BS;
	_delay_us(2);
	GPIO_ResetBits(PORT_SIG, EN);
	//LCD_PORT->BSRR=LCD_EN_BC;
	_delay_us(40);


}

