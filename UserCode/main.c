#include "main.h"

struct data_for_lcd d_lcd;

uint8_t count_up_down=4;
uint8_t screen = 0;
uint32_t TimeMotor1 = 0;
uint32_t TimeMotor2 = 0;
uint32_t TimeSec = 0;
uint32_t TimeSec2 = 0;
uint32_t TimeSec3 = 0;
//uint32_t TimeSec4 = 0;
uint8_t TimerState = 0;
uint8_t TimerState2 = 0;
uint8_t TimerState3 = 0;
uint8_t StateAlarm=0;
uint8_t OneTwoMotor = 0;
uint32_t MotorTimeDo = 3600; //переменная задающая интервал между переключением двигателей и их стартов в случаи длительного простоя

float RatedCurrMotor1=0;
float RatedCurrMotor2=0;
float ActCurrMotor1=0;
float ActCurrMotor2=0;
uint8_t AlarmMotor1 = 0;
uint8_t AlarmMotor2 = 0;

uint8_t FirstCycleAuto=0;
uint8_t M1_Start_Stop=0;

TIM_TimeBaseInitTypeDef timer;

uint32_t FLASH_Read(uint32_t address)
{
    return (*(__IO uint32_t*)address);
}

uint32_t Read_Flash(uint8_t offset_address)
{
	uint32_t st_address = (FLASH_BASE + 127 * 1024) + offset_address;
	uint32_t tempp=0;
	tempp = FLASH_Read(st_address);
	return tempp;
}

void Write_Read_Flash(uint32_t data[])
{
	uint8_t offset_address=0;
	uint32_t st_address = (FLASH_BASE + 127 * 1024) + offset_address;;
	
  FLASH_Unlock();
	FLASH_ErasePage(st_address);
	
	for(int i=0; i<8;i++){
	  	st_address = (FLASH_BASE + 127 * 1024) + offset_address;
    	//FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	    FLASH_ProgramWord(st_address, data[i]);
		  offset_address+=4;
	}
	FLASH_Lock();
}
//***************************************************************************************************************

void TIM2_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
        {
        	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
        	TimeSec++;
        }
}
void TIM3_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
        {
        	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
        	TimeSec2++;
        }
}
void TIM4_IRQHandler(void)
{
        if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
        {
        	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
        	TimeSec3++;
        }
}

int main(void)
{	
	uint8_t button_stat = 0;	
	uint8_t button2_stat = 0;	
	uint8_t button3_stat = 0;		
	uint8_t button4_stat = 0;
	
	init_RCC();    
	init_buttons();  
	init_motor();
	
	Motor1_ON();
	Motor2_ON();
	AlarmOver();
	AlarmMotor1();
	AlarmMotor2();
	
	init_timer();
	init_inputs();
	init_ADC12();
	
  d_lcd.data_setting[0] = Read_Flash(0);//мощность первого мотора
  d_lcd.data_setting[1] = Read_Flash(4);//мощность второго мотора
  d_lcd.data_setting[2] = Read_Flash(8);//время переключения
  d_lcd.data_setting[3] = Read_Flash(12);//тип датчика 2 (не используется)
	d_lcd.data_setting[4] = Read_Flash(16);//время наработки мотора 1
	d_lcd.data_setting[5] = Read_Flash(20);//время наработки мотора 2
	d_lcd.data_setting[6] = Read_Flash(24);//максимальное значение токового датчика мотора1
	d_lcd.data_setting[7] = Read_Flash(28);//максимальное значение токового датчика мотора2
	
//	if(d_lcd.data_setting[0]==0xffffffff)// на время тестирования
//	{
//		d_lcd.data_setting[0] = 150;
//    d_lcd.data_setting[1] = 150;
//    d_lcd.data_setting[2] = 420;
//    d_lcd.data_setting[3] = 100;
//  	d_lcd.data_setting[4] = 0;
//  	d_lcd.data_setting[5] = 0;
//  	d_lcd.data_setting[6] = 500;
//  	d_lcd.data_setting[7] = 500;
//	}
	
	if(d_lcd.data_setting[4]==0xffffffff)
	{
  	d_lcd.data_setting[4] = 0;
	}
	
	if(d_lcd.data_setting[5]==0xffffffff)
	{
  	d_lcd.data_setting[5] = 0;
	}
	
	
	RatedCurrMotor1=d_lcd.data_setting[0]*100/(sqrt(3)*380*0.85*0.85); //номинальный ток первого мотора
	RatedCurrMotor2=d_lcd.data_setting[1]*100/(sqrt(3)*380*0.85*0.85); //номинальный ток второго мотора
  MotorTimeDo = d_lcd.data_setting[2] * 60.0;
	
	
	delay_ms(100);
	
	lcd_init();
  lcd_set_xy(0,4);
  lcd_out(">Инфо");
	
	lcd_set_xy(0,5);
  lcd_out(" Настройки");
	
while(1)
{
	
	
if(IN5()!=1)// АВТОМАТИЧЕСКИЙ РЕЖИМ. ТУМБЛЕР.
{
	
if(FirstCycleAuto==0)	
{
  AlarmMotor1=0;
	AlarmMotor2=0;
	TimerState=0;
	TimerState2=0;
	TimerState3=0;
	
	AlarmMotor1();
	AlarmMotor2();
	
	//FirstCycleAuto=1;
}
					
	 if(IN1()!=1 && IN2()!=1)
	 {
		 M1_Start_Stop=1;
	 }else if(IN1()==1 && IN2()==1)
	 {
		 M1_Start_Stop=0;
	 }
	 
	 if(M1_Start_Stop==1 && AlarmMotor1!=1)//проверка состояния первого датчика
	  {
			if(TimerState==0){
				  TIM_Cmd(TIM2, ENABLE);
    		  TIM_SetCounter(TIM2, 0);
				  TimerState = 1;
				  TIM_Cmd(TIM4, ENABLE);
    		  TIM_SetCounter(TIM4, 0);
				  Motor1_Off();
			}		

			if(TimeSec3>MotorTimeDo&&IN3()==1){  // если насос отработал час переключиться на второй		
				if(OneTwoMotor==0){
			  	Motor1_ON();
				  Motor2_Off();
			  	TimeSec3=0;
			  	OneTwoMotor=1;
				}else{
					Motor2_ON();
				  Motor1_Off();
			  	TimeSec3=0;
			  	OneTwoMotor=0;
				}			
			}else if(IN3()!=1){
			    Motor1_Off();
			}
			
			}else{
				if(TimerState==1){
				   TimeMotor1 += TimeSec;		  
    		   TIM_Cmd(TIM2, DISABLE);
					 d_lcd.data_setting[4] = TimeMotor1;	
					 Write_Read_Flash(d_lcd.data_setting);
					 TimerState = 0;		
				 	 TimeSec=0;
				   Motor1_ON();
					if(AlarmMotor1!=1)
					   Motor2_ON();
				}					
			}
			if(IN3()!=1&& AlarmMotor2!=1)//проверка состояния второго датчика
	    {
		  	if(TimerState2==0){
				   TIM_Cmd(TIM4, DISABLE);
					 TimeSec3=0;
				   TIM_Cmd(TIM3, ENABLE);
    		   TIM_SetCounter(TIM3, 0);
				   TimerState2 = 1;
				   Motor2_Off();
			  }
			}else{
				if(TimerState2==1){
				   TimeMotor2 += TimeSec2;
    		   TIM_Cmd(TIM3, DISABLE);
					 d_lcd.data_setting[5] = TimeMotor2;	
					 Write_Read_Flash(d_lcd.data_setting);
					 TimerState2 = 0;		
				 	 TimeSec2=0;
				   Motor2_ON();
					 TIM_Cmd(TIM4, ENABLE);
    		   TIM_SetCounter(TIM4, 0);
				}
			}		
			
			if(IN1()==1&&IN2()==1&&IN3()==1){    //время простоя обоих двигателей, если двигателя стоят более часа прокрутить их
				if(TimerState3==0){
			  	TIM_Cmd(TIM4, ENABLE);
    		  TIM_SetCounter(TIM4, 0);
					TimerState3=1;
				}
				if(TimeSec3>MotorTimeDo){
					 Motor1_Off();
					 Motor2_Off();
				 	 delay_ms(5000);
				   Motor1_ON();
					 Motor2_ON();
					 TimeSec3=0;
				}
			}else{
				if(TimerState3==1){
				  TIM_Cmd(TIM4, DISABLE);
			    TimerState3 = 0;		
				  TimeSec3=0;
				}
			}
					
			if(IN4()!=1)//проверка состояния четвертого датчика авария
	    {
				if(StateAlarm==0){		  
					AlarmOverOff();
				  StateAlarm=1;
				}
			}else{
				if(StateAlarm==1){
					AlarmOver();		  	
			  	StateAlarm=0;
				}
			}
							
				
d_lcd.value_adc_ch1 = (float)ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1)/4095 * 3.3;	    
d_lcd.value_adc_ch2 = (float)ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1)/4095 * 3.3;		
			 
					 
ActCurrMotor1=(d_lcd.value_adc_ch1*(d_lcd.data_setting[6]/10.0))*0.6666666666666667;    //коэффициент введен так ка напряжение на входе поменялось с 1-го вольта до 1,5 + от 10-ки нужно избавиться
ActCurrMotor2=(d_lcd.value_adc_ch2*(d_lcd.data_setting[7]/10.0))*0.6666666666666667;   

 if(ActCurrMotor1>RatedCurrMotor1 && FirstCycleAuto==1){
	 AlarmMotor1=1;
	 AlarmMotorOff1();	 
 }
if(ActCurrMotor2>RatedCurrMotor2 && FirstCycleAuto==1){
	 AlarmMotor2=1;
   AlarmMotorOff2(); 
 }

 FirstCycleAuto=1;
 
}else if(FirstCycleAuto==1)	
           {
						 FirstCycleAuto=0;
						 AlarmMotor1();
						 AlarmMotor2();
						 Motor1_ON();
						 Motor2_ON();
						 StateAlarm=0;
						 AlarmOver();
}	
	///визуализация состояния цифровых и аналоговых сигналов
	    if((screen==5||screen==6||screen==7||screen==18)&&
				button_stat==0 && button2_stat==0 && button3_stat==0 && button4_stat==0){
         Update_Data(&count_up_down, screen, d_lcd);
					delay_ms(60);
			}
	//******************************************************					 
					 
		  if (BUT_UP() == 1)//Up button
			{
				if(button_stat==0){	
					count_up_down--;
				  Up_Down(&count_up_down, screen, d_lcd);
					button_stat=1;
					
					if(screen==12){
				   if(d_lcd.data_setting[0]==0xffffffff)
			        d_lcd.data_setting[0]=10;
						  d_lcd.data_setting[0] += 10;	
              Write_Read_Flash(d_lcd.data_setting);	
					    Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==14){
						if(d_lcd.data_setting[1]==0xffffffff)
			        d_lcd.data_setting[1]=10;	
						  d_lcd.data_setting[1] += 10;	
              Write_Read_Flash(d_lcd.data_setting);	
						  Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==16){
						if(d_lcd.data_setting[6]==0xffffffff)
			        d_lcd.data_setting[6]=10;	
						  d_lcd.data_setting[6] += 10;	
              Write_Read_Flash(d_lcd.data_setting);	
						  Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==17){
						if(d_lcd.data_setting[7]==0xffffffff)
			        d_lcd.data_setting[7]=10;	
						  d_lcd.data_setting[7] += 10;	
              Write_Read_Flash(d_lcd.data_setting);	
						  Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==19){
						if(d_lcd.data_setting[2]==0xffffffff)
			        d_lcd.data_setting[2]=60;	
						  d_lcd.data_setting[2] += 1;	
              Write_Read_Flash(d_lcd.data_setting);	
						  Update_Data(&count_up_down, screen, d_lcd);
					}
					
					
				} 
			}else{
				if(button_stat==1){
					delay_ms(10);
					button_stat=0;
				}										
			}	
			if (BUT_DOWN() == 1)//Down button
			{
				if(button3_stat==0){	
					count_up_down++;
				  Up_Down(&count_up_down, screen, d_lcd);					
					button3_stat=1;
					
				  if(screen==12){
					  if(d_lcd.data_setting[0]==0xffffffff)
			        d_lcd.data_setting[0]=10;
						  d_lcd.data_setting[0] -= 1;	
              Write_Read_Flash(d_lcd.data_setting);
              Update_Data(&count_up_down, screen, d_lcd);						
					}
					if(screen==14){
						if(d_lcd.data_setting[1]==0xffffffff)
			        d_lcd.data_setting[1]=10;	
						  d_lcd.data_setting[1] -= 1;	
              Write_Read_Flash(d_lcd.data_setting);	
					  	Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==16){
						if(d_lcd.data_setting[6]==0xffffffff)
			        d_lcd.data_setting[6]=10;	
					  	d_lcd.data_setting[6] -= 1;	
              Write_Read_Flash(d_lcd.data_setting);	
					  	Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==17){
						if(d_lcd.data_setting[7]==0xffffffff)
			        d_lcd.data_setting[7]=10;	
						  d_lcd.data_setting[7] -= 1;	
              Write_Read_Flash(d_lcd.data_setting);	
					  	Update_Data(&count_up_down, screen, d_lcd);
					}
					if(screen==19){
						if(d_lcd.data_setting[2]==0xffffffff)
			        d_lcd.data_setting[2]=60;	
						  d_lcd.data_setting[2] -= 1;	
              Write_Read_Flash(d_lcd.data_setting);	
						  Update_Data(&count_up_down, screen, d_lcd);
					}
				} 
			}else{
				if(button3_stat==1){
           delay_ms(10);					
					 button3_stat=0;
				}										
			}	
			
			if (NEXT_BUT() == 1)//next screen button
			{
				if(button2_stat==0){             				
					switch(count_up_down){
						case 4: {	
							switch(screen){
								case 0: {
                   screen = 1;									
                   next_screeen(&count_up_down, screen, d_lcd);		
							     }break;
							  case 1: {
                   screen = 2;									
									next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 3: {
                   screen = 4;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 4: {
                   screen = 6;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 8: {
                   screen = 10;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 9: {
//                   screen = 11;									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 10: {
                   screen = 12;								  
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 11: {
//                   screen = 11;
//								 	 d_lcd.data_setting[2] = 100;	
//									 Write_Read_Flash(d_lcd.data_setting);
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 12: {
                   screen = 12;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 13: {
//                   screen = 13;
//								 	 d_lcd.data_setting[3] = 100;	
//									 Write_Read_Flash(d_lcd.data_setting);
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 14: {
                   screen = 14;							
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								
							  case 15: {
                   screen = 16;							
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;	 
							}
						}break;	
            case 5: {							
						switch(screen){
								case 0: {
                   screen = 8;									
									next_screeen(&count_up_down, screen, d_lcd);
							     }break;
							  case 1: {
								   screen = 3;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 3: { 
								   screen = 5;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 4: { 
									 screen = 7;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 8: { 
								   screen = 15;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 9: {
//                   screen = 13;									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 10: {
                   screen = 14;	                 							
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 11: {
//                   screen = 11;
//								   d_lcd.data_setting[2] = 420;	
//                   Write_Read_Flash(d_lcd.data_setting);									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
                case 12: {
                   screen = 12;								
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 13: {
//                   screen = 13;
//								   d_lcd.data_setting[3] = 420;	
//                   Write_Read_Flash(d_lcd.data_setting);									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 14: {
                   screen = 14;								
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 15: {
                   screen = 17;							
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
							}
						}break;
					  case 6: {							
						switch(screen){
						  case 1: {
                screen = 18;									
							  next_screeen(&count_up_down, screen, d_lcd);
							    }break;
							case 8: {
                screen = 19;									
							  next_screeen(&count_up_down, screen, d_lcd);
							    }break;
//							case 8: { 
//						    screen = 15;
//								next_screeen(&count_up_down, screen, d_lcd);
//							    }break;
						}
					}break;
					}
					 button2_stat=1;
				}
			}else{
				if(button2_stat==1){
					 delay_ms(10);
					 button2_stat=0;
				}										
			}	
			
	  	if (BACK_BUT() == 1)//back screen button
			{
				if(button4_stat==0){   
					if(screen!=0){
						switch(screen){
								case 1: {
                   screen = 0;									
                   next_screeen(&count_up_down, screen, d_lcd);		
							     }break;
							  case 2: {
                   screen = 1;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 3: {
                   screen = 1;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 4: {	
									 screen = 3;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 5: {	
                   screen = 3;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 6: {
                   screen = 4;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 7: {
									 screen = 4;
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 8: {
                   screen = 0;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 9: {	
//									 screen = 8;
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 10: {
                   screen = 8;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
//								case 11: {
//                   screen = 9;									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
//								case 13: {
//                   screen = 9;									
//									 next_screeen(&count_up_down, screen, d_lcd);
//							     }break;
								case 12: {
                   screen = 10;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 14: {
                   screen = 10;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 15: {
                   screen = 8;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 16: {
                   screen = 15;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 17: {
                   screen = 15;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 18: {
                   screen = 1;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
								case 19: {
                   screen = 8;									
									 next_screeen(&count_up_down, screen, d_lcd);
							     }break;
							}
					}
					 button4_stat=1;
				}
			}else{
				if(button4_stat==1){
           delay_ms(10);					
					 button4_stat=0;
				}										
			}	

}
}


