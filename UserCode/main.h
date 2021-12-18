#include "Lcd_Function.h"
#include "Inits.h"
#include "Math.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"

void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
void init_RCC(void);
void adc_init(void);
void init_inputs(void);
void init_motor(void);
void init_timer(void);
void init_LCD(void);
void init_buttons(void);
void init_ADC12(void);


#define BUT_UP() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15)
#define BUT_DOWN() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define NEXT_BUT() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define BACK_BUT() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)

#define IN1() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)
#define IN2() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define IN3() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_2)//проверка состояния второго датчика
#define IN4() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)//проверка состояния четвертого датчика авария
#define IN5() GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)// АВТОМАТИЧЕСКИЙ РЕЖИМ. ТУМБЛЕР.

#define Motor1_ON()GPIO_SetBits(GPIOA, GPIO_Pin_8)
#define Motor2_ON()GPIO_SetBits(GPIOA, GPIO_Pin_7)
#define AlarmOver()GPIO_SetBits(GPIOA, GPIO_Pin_11)
#define AlarmMotor1()GPIO_SetBits(GPIOA, GPIO_Pin_2)
#define AlarmMotor2()GPIO_SetBits(GPIOA, GPIO_Pin_12)

//#define Motor1_ON()GPIO_SetBits(GPIOA, GPIO_Pin_7)
//#define Motor2_ON()GPIO_SetBits(GPIOA, GPIO_Pin_11)
//#define AlarmOver()GPIO_SetBits(GPIOA, GPIO_Pin_2)
//#define AlarmMotor1()GPIO_SetBits(GPIOA, GPIO_Pin_12)
//#define AlarmMotor2()GPIO_SetBits(GPIOA, GPIO_Pin_8)

#define AlarmOverOff()GPIO_ResetBits(GPIOA, GPIO_Pin_11)
#define Motor1_Off()GPIO_ResetBits(GPIOA, GPIO_Pin_8)
#define Motor2_Off()GPIO_ResetBits(GPIOA, GPIO_Pin_7)
#define AlarmMotorOff1()GPIO_ResetBits(GPIOA, GPIO_Pin_2)
#define AlarmMotorOff2()GPIO_ResetBits(GPIOA, GPIO_Pin_12)

//#define Motor1_Off()GPIO_ResetBits(GPIOA, GPIO_Pin_7)
//#define Motor2_Off()GPIO_ResetBits(GPIOA, GPIO_Pin_11)
//#define AlarmOverOff()GPIO_ResetBits(GPIOA, GPIO_Pin_2)
//#define AlarmMotorOff1()GPIO_ResetBits(GPIOA, GPIO_Pin_12)
//#define AlarmMotorOff2()GPIO_ResetBits(GPIOA, GPIO_Pin_8)




