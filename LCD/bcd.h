#include "stm32f10x.h"

#ifndef BCD_H
#define BCD_H



//если закомментировать, то ноль в старших разрядах выводиться не будет
//#define MIRROR_NULL_



void BCD_1Lcd(unsigned char value);					// значение числа от 0 до 9 

void BCD_2Lcd(unsigned char value);					// значение числа от 0 до 99

void BCD_3Lcd(unsigned char value);					// значение числа от 0 до 255 

void BCD_3IntLcd(unsigned int value);				// значение числа от 0 до 999

void BCD_4IntLcd(unsigned int value);				// значение числа от 0 до 9999

#endif //BCD_H

