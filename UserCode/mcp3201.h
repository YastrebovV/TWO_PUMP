#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"

float mcp3201_data_1(void);
float mcp3201_data_2(void);
void PeripheralInit_SPI1_Master(void);


#define CS2_LOW()   		GPIO_ResetBits (GPIOA, GPIO_Pin_4)
#define CS2_HIGH()				GPIO_SetBits (GPIOA, GPIO_Pin_4)
#define CS1_LOW()   		GPIO_ResetBits (GPIOA, GPIO_Pin_3)
#define CS1_HIGH()				GPIO_SetBits (GPIOA, GPIO_Pin_3)

