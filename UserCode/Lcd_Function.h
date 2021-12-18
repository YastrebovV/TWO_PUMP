#include "stm32f10x.h"
#include "hd44780.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data_for_lcd
{
  uint32_t data_setting[8];
  float value_adc_ch1;
  float value_adc_ch2;
  uint32_t motor1_work_time;
  uint32_t motor2_work_time;
};

void Update_Data(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd);
void Up_Down(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd);
void next_screeen(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd);


#define Out1()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)
#define Out2()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
#define Out3()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)
#define Out4()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
#define Out5()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)
//#define Out1()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)
//#define Out2()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11)
//#define Out3()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2)
//#define Out4()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)
//#define Out5()GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8)


#define IN1() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
#define IN2() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define IN3() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)
#define IN4() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)
#define IN5() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)

