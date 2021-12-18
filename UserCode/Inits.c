#include "main.h"

/* функция задержки */
void delay_ms(uint32_t ms)
{
    volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}
void delay_us(uint32_t us)
{
    volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000000)*us;
        for (; nCount!=0; nCount--);
}



void init_RCC(void)
{

//	RCC_ClocksTypeDef clocks;
//	uint32_t cl;
	
RCC_DeInit(); //	сброс настроек тактового генератора
	delay_ms(10);
RCC_HSICmd(DISABLE); //	выключение внутреннего RC HSI 8МГц генератора
	delay_ms(10);
RCC_HSEConfig(RCC_HSE_ON); //	включение внешнего тактового генератора
	delay_ms(10);
//RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div2);//	Предделитель PREDIV1: HSE перед множителем PLLMUL
	delay_ms(10);
RCC_PLLConfig(RCC_PLLSource_HSE_Div1 ,RCC_PLLMul_6); //	тактирование от HSE с PREDIV1 8/1*3 = 24МГц
	delay_ms(10);
RCC_PLLCmd(ENABLE); //	Включаем PLL
	delay_ms(10);
RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //	На системную шину подаем тактирование с множителя PLLMUL
	
//   RCC_DeInit(); 
//   RCC_HSICmd(DISABLE); 
//   RCC_HSEConfig(RCC_HSE_ON); 
//   RCC_PREDIV1Config(RCC_PREDIV1_Source_HSE, RCC_PREDIV1_Div2);
//   RCC_PLLConfig(RCC_PLLSource_PREDIV1 ,RCC_PLLMul_4);
//   RCC_PLLCmd(ENABLE); 
//   RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 
	
//RCC_DeInit(); //	сброс настроек тактового генератора
//	delay_ms(10);
//RCC_HSEConfig(RCC_HSE_OFF); //	отключение внешнего тактового генератора
//	delay_ms(10);
//RCC_HSICmd(ENABLE);
//	delay_ms(10);
//RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_12); //	тактирование от HSI с делителем 2: 8 / 2 * 9 = 36МГц
//	delay_ms(10);
//RCC_PLLCmd(ENABLE); //	Включаем PLL
//	delay_ms(10);
//RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); //	На системную шину подаем тактирование с множителя PLLMUL
//	delay_ms(10);
//RCC_PCLK1Config(RCC_HCLK_Div4);
//		delay_ms(10);

//	RCC_GetClocksFreq(&clocks);
//  cl = clocks.SYSCLK_Frequency;
//  delay_ms(100);
}



//***************************************************************************************************************
//Таймер1***************************************************************************************************************
void init_timer(void)
{
    // TIMER 2
  	TIM_TimeBaseInitTypeDef TIMER_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);

  	TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER_InitStructure.TIM_Prescaler = 47999;
    TIMER_InitStructure.TIM_Period = 1000;
    TIM_TimeBaseInit(TIM2, &TIMER_InitStructure);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    //TIM_Cmd(TIM2, ENABLE);

    /* NVIC Configuration */
    /* Enable the TIM1_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		// TIMER 3

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

  	TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER_InitStructure.TIM_Prescaler = 47999;
    TIMER_InitStructure.TIM_Period = 1000;
    TIM_TimeBaseInit(TIM3, &TIMER_InitStructure);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    //TIM_Cmd(TIM3, ENABLE);

    /* NVIC Configuration */
    /* Enable the TIM3_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		// TIMER 4
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);

  	TIM_TimeBaseStructInit(&TIMER_InitStructure);
    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIMER_InitStructure.TIM_Prescaler = 47999;
    TIMER_InitStructure.TIM_Period = 1000;
    TIM_TimeBaseInit(TIM4, &TIMER_InitStructure);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    //TIM_Cmd(TIM4, ENABLE);

    /* NVIC Configuration */
    /* Enable the TIM4_IRQn Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
//	  // TIMER 5
//		
//		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);

//  	TIM_TimeBaseStructInit(&TIMER_InitStructure);
//    TIMER_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
//    TIMER_InitStructure.TIM_Prescaler = 47999;
//    TIMER_InitStructure.TIM_Period = 1000;
//    TIM_TimeBaseInit(TIM5, &TIMER_InitStructure);
//    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
////    TIM_Cmd(TIM5, ENABLE);

//    /* NVIC Configuration */
//    /* Enable the TIM5_IRQn Interrupt */
//    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//    NVIC_Init(&NVIC_InitStructure);
}
//*************************************************************
void init_buttons(void)
{
	GPIO_InitTypeDef GPIO_Init_Button;
  RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_Init_Button.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init_Button.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init_Button.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init (GPIOB, &GPIO_Init_Button);
}

void init_inputs(void)
{
	GPIO_InitTypeDef GPIO_Init_Inputs;
  RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_Init_Inputs.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_Init_Inputs.GPIO_Mode = GPIO_Mode_IPU ;
	GPIO_Init_Inputs.GPIO_Speed = GPIO_Speed_50MHz;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//  AFIO->MAPR|=AFIO_MAPR_SWJ_CFG_JTAGDISABLE; //Отключили JTAG, SWD включен
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE );
  GPIO_PinRemapConfig (GPIO_Remap_SWJ_JTAGDisable, ENABLE );
	
	GPIO_Init (GPIOB, &GPIO_Init_Inputs);
}

void init_LCD(void)
{
	GPIO_InitTypeDef GPIO_InitLCD;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitLCD.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitLCD.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitLCD.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitLCD);
}
void init_motor(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void init_ADC12(void){
	
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef ADC_InitStructure;
 
    RCC_ADCCLKConfig (RCC_PCLK2_Div6);
    /* Enable ADC1 and GPIOA clock */
    RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 ,   ENABLE ) ;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
 
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_Init(ADC1, &ADC_InitStructure);
 
    ADC_InjectedSequencerLengthConfig(ADC1, 1);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_7Cycles5);   
 
    ADC_ExternalTrigInjectedConvConfig( ADC1, ADC_ExternalTrigInjecConv_None );
 
    ADC_Cmd ( ADC1 , ENABLE ) ;
 
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
 
    ADC_AutoInjectedConvCmd( ADC1, ENABLE );
    ADC_SoftwareStartInjectedConvCmd ( ADC1 , ENABLE ) ;
}

