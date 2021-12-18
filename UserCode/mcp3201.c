#include "mcp3201.h"

void PeripheralInit_SPI1_Master(void){
 
    GPIO_InitTypeDef GPIO_InitDef;
    GPIO_InitTypeDef GPIO_InitStruct;
		  
    // initialize clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
	
    // initialize A5/SCK alternate function push-pull (50 MHz)
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitDef);
 
    // initialize A6/MISO input pull-up (50MHz)
    GPIO_InitDef.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitDef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitDef);
	
 //********************************************************************
    SPI_I2S_DeInit(SPI1);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  
   //GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);
   //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 
 
    SPI_InitTypeDef SPI_InitStructure;
    SPI_StructInit(&SPI_InitStructure);

	  SPI_Cmd ( SPI1, DISABLE );
	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	  SPI_InitStructure.SPI_CRCPolynomial = 7;
	  SPI_Init ( SPI1, &SPI_InitStructure );

   
					// Controls Pins setup - nCS (PA3) - OUT
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init (GPIOA, &GPIO_InitStruct );
		
		CS1_LOW();
		CS1_HIGH();
		CS2_LOW();
		CS2_HIGH();
		
		SPI_Cmd(SPI1, ENABLE);
}


uint8_t MCP3201_Read_(void)
{
	 while(!(SPI1->SR & SPI_SR_RXNE)){};
		return SPI1->DR;
}

float mcp3201_data_1(void)
{
	
	  uint8_t dataHigh =0;
    uint8_t dataLow =0;
	  uint16_t result;
	  float temp_float;
	
	  SPI_Cmd(SPI1, ENABLE);
	  CS1_LOW();
	
	  dataHigh = MCP3201_Read_();
	  dataLow = MCP3201_Read_();
	 	
    CS1_HIGH();
	  SPI_Cmd ( SPI1, DISABLE );
	  
	  result = dataHigh;
	  result = result<<8;
    result = result|dataLow;
	  result = result<<3;
	  result = result>>4;
	
	  temp_float = ((float) result/4096*5);
	  return temp_float;
}

float mcp3201_data_2(void)
{
	
	  uint8_t dataHigh =0;
    uint8_t dataLow =0;
	  uint16_t result;
	  float temp_float;
	
	  SPI_Cmd(SPI1, ENABLE);
	  CS2_LOW();
	
	  dataHigh = MCP3201_Read_();
	  dataLow = MCP3201_Read_();
	 	
    CS2_HIGH();
	  SPI_Cmd ( SPI1, DISABLE );
	  
	  result = dataHigh;
	  result = result<<8;
    result = result|dataLow;
	  result = result<<3;
	  result = result>>4;
	
	  temp_float = ((float) result/4096*5);
	  return temp_float;
}

