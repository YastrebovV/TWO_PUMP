#include "main.h"
	
uint8_t MCP3201_Read(void)
{
	 while(!(SPI1->SR & SPI_SR_RXNE)){};
		return SPI1->DR;
}

uint16_t Read_Data_SPI_MC3201(void){
	
  	uint16_t result;
    uint8_t dataHigh =0;
    uint8_t dataLow =0;
	
	  SPI_Cmd(SPI1, ENABLE);
	  CS2_LOW();
	
	  dataHigh = MCP3201_Read();
	  dataLow = MCP3201_Read();
	 	
    CS2_HIGH();
	  SPI_Cmd ( SPI1, DISABLE );
	  
	  result = dataHigh;
	  result = result<<8;
    result = result|dataLow;
	  result = result<<3;
	  result = result>>4;
	
	  return ((float) result/4096*5);
}


