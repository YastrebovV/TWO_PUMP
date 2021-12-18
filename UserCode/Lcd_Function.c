#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

#include "Lcd_Function.h"

char * menu_string[19][10] = {{"Инфо","Настройки"},{"Время наработки","Состояние i/o","Ток моторов"},{"Время M1: ", "Время M2: "},{"Дискретные", "Аналоговые"},{"Входа", "Выходы"},{"АнВх1 ", "АнВх2 "},
{"Вх1 ", "Вх2 ", "Вх3 ", "Вх4 ", "Вх5 "},{"Вых1 ", "Вых2 ", "Вых3 ", "Вых4 ", "Вых5 "},{"Мощность мот-ов", "Макс.ток датчиков","Время перекл-ия"},{"Аналог. вход 1", "Аналог. вход 2"},{"Мотор 1", "Мотор 2"},{"0-10V", "4-20mA"},
{"11kWa","15kWa", "16kWa","25kWa"},{"0-10V", "4-20mA"},{"11kWa","15kWa", "16kWa","25kWa"},{"Аналог. вход 1", "Аналог. вход 2"},{" ", " "},{" ", " "},{"Ток М1 ", "Ток М2 "}};

//char * menu_string[15][10] = {{"Info","Setting"},{"Time work motor","State i/o"},{"Time M1: ", "Time M2: "},{"Discrete", "Analog"},{"In", "Out"},{"AnIn1 ", "AnIn2 "},
//{"In1 ", "In2 ", "In3 ", "In4 "},{"Out1 ", "Out2 "},{"Type of analog inputs", "Engine power"},{"Analog Input 1", "Analog Input 2"},{"Motor 1", "Motor 2"},{"0-10V", "4-20mA"},
//{"0.75kWa","1.1kWa", "2.2kWa","3kWa"},{"0-10V", "4-20mA"},{"0.75kWa","1.1kWa", "2.2kWa","3kWa"}};


void Update_Data(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd)
{
	char* tempp;
	char* temp2;
	
	//char* temp3;
	//char* temp4;
	size_t sumlen, sumlen2; //sumlen3, sumlen4;
	
	switch(screen){
	case 1: {
			if(*count_up_down==4){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", ">", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", " ", menu_string[screen][1]);	}
			
			if(*count_up_down==5){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", " ", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", ">", menu_string[screen][1]);	}
			
			if(*count_up_down==6){
				sumlen = strlen(menu_string[screen][1])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", " ", menu_string[screen][1]);

			  sumlen2 = strlen(menu_string[screen][2])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", ">", menu_string[screen][2]);	}	
		}break;
	case 2:{ //Времена наработки моторов	 
					
	   if(d_lcd.data_setting[4]==0xffffffff)
			  d_lcd.data_setting[4]=0;
		 if(d_lcd.data_setting[5]==0xffffffff)
			  d_lcd.data_setting[5]=0;
		 
		 if(*count_up_down==4){ 
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%d", ">", menu_string[screen][0], d_lcd.data_setting[4]/60);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%d", " ", menu_string[screen][1], d_lcd.data_setting[5]/60);}
			if(*count_up_down==5){ 
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%d", " ", menu_string[screen][0], d_lcd.data_setting[4]/60);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%d", ">", menu_string[screen][1], d_lcd.data_setting[5]/60);}
			
		}break;
	case 5:{//экран аналоговых входов
			if(*count_up_down==4){
	      sumlen = strlen(menu_string[screen][0])+10;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%.2f%s", ">", menu_string[screen][0],d_lcd.value_adc_ch1,"V");
			
				sumlen2 = strlen(menu_string[screen][1])+10;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%.2f%s", " ", menu_string[screen][1],d_lcd.value_adc_ch2,"V");}
			if(*count_up_down==5){
	      sumlen = strlen(menu_string[screen][0])+10;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%.2f%s", " ", menu_string[screen][0],d_lcd.value_adc_ch1,"V");
			
				sumlen2 = strlen(menu_string[screen][1])+10;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%.2f%s", ">", menu_string[screen][1],d_lcd.value_adc_ch2,"V");}
		}break;
	case 6:{//экран цифровых входов
			  char* in1;
			  char* in2;
			  char* in3;
			  char* in4;
	    	char* in5;
					
		    if(IN1()==1){
					in1 = "0";
				}else in1 = "1";
				if(IN2()==1){
					in2 = "0";
				}else in2 = "1";
				if(IN3()==1){
					in3 = "0";
				}else in3 = "1";
				if(IN4()==1){
					in4 = "0";
				}else in4 = "1";
				if(IN5()==1){
					in5 = "0";
				}else in5 = "1";
				
			if(*count_up_down==4){
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", ">", menu_string[screen][0],in1);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", " ", menu_string[screen][1], in2);}
			if(*count_up_down==5){
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][0],in1);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][1], in2);}
			
			if(*count_up_down==6){
		    sumlen = strlen(menu_string[screen][1])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][1],in2);
			 
		  	sumlen2 = strlen(menu_string[screen][2])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][2], in3);}
			if(*count_up_down==7){
		    sumlen = strlen(menu_string[screen][2])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][2],in3);
			 
		  	sumlen2 = strlen(menu_string[screen][3])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][3], in4);}
			if(*count_up_down==8){
		    sumlen = strlen(menu_string[screen][3])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][3],in4);
			 
		  	sumlen2 = strlen(menu_string[screen][4])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][4], in5);}
		}break;
  case 7:{//экран цифровых выходов
			  char* out1;
			  char* out2;
				char* out3;
			  char* out4;
		    char* out5;
			
		    if(Out1()==1){
					out1 = "0";
				}else out1 = "1";
				if(Out2()==1){
					out2 = "0";
				}else out2 = "1";
				if(Out3()==1){
					out3 = "0";
				}else out3 = "1";
				if(Out4()==1){
					out4 = "0";
				}else out4 = "1";
				if(Out5()==1){
					out5 = "0";
				}else out5 = "1";
				
			if(*count_up_down==4){
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", ">", menu_string[screen][0],out1);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", " ", menu_string[screen][1], out2);}
			if(*count_up_down==5){
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][0],out1);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][1], out2);}
			if(*count_up_down==6){
		    sumlen = strlen(menu_string[screen][1])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][1],out2);
			 
		  	sumlen2 = strlen(menu_string[screen][2])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][2], out3);}
			if(*count_up_down==7){
		    sumlen = strlen(menu_string[screen][2])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][2],out3);
			 
		  	sumlen2 = strlen(menu_string[screen][3])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][3], out4);}
			if(*count_up_down==8){
		    sumlen = strlen(menu_string[screen][3])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][3],out4);
			 
		  	sumlen2 = strlen(menu_string[screen][4])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][4], out5);}
		}break;
	case 8: {//экран настроек
			if(*count_up_down==4){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", ">", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", " ", menu_string[screen][1]);	}
			
			if(*count_up_down==5){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", " ", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", ">", menu_string[screen][1]);	}
			
			if(*count_up_down==6){
				sumlen = strlen(menu_string[screen][1])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", " ", menu_string[screen][1]);

			  sumlen2 = strlen(menu_string[screen][2])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", ">", menu_string[screen][2]);	}	
		}break;	
	case 12:{ //мощность двигателя 1		   
		 float powerMotor;
		 
		 if(d_lcd.data_setting[0]==0xffffffff)
			  d_lcd.data_setting[0]=10;
		 
		 powerMotor=d_lcd.data_setting[0]/10.0;
		 
		 sumlen = strlen("           ");
     tempp = malloc(sumlen);
		 snprintf(tempp, sumlen, "%.1f%s", powerMotor, "кВт");
		 sumlen2 = strlen("  ");
     temp2 = malloc(sumlen2);
     snprintf(temp2, sumlen2, "%s", " ");		 
			
		}break;
	 
	case 14:{ //мощность двигателя 2		  				
     float powerMotor;
		 			
		 if(d_lcd.data_setting[1]==0xffffffff)
			  d_lcd.data_setting[1]=10;		
			
		 powerMotor=d_lcd.data_setting[1]/10.0;
		 
		 sumlen = strlen("           ");
     tempp = malloc(sumlen);
		 snprintf(tempp, sumlen, "%.1f%s", powerMotor, "кВт");
			
		 sumlen2 = strlen("  ");
     temp2 = malloc(sumlen2);
     snprintf(temp2, sumlen2, "%s", " ");		
		 
		}break;
	case 11:{ //тип аналоговых сигналов	(в данный момент не используется)
	   
		 char* temp_state[2];
		
		 if(d_lcd.data_setting[2] == 0xffffffff)
			 d_lcd.data_setting[2] =100;
		
		 switch (d_lcd.data_setting[2])
		 {
			 case 100: {
				 temp_state[0] = " set";
				 temp_state[1] = "";			 
			 }   break;
			 case 420: {
				 temp_state[1] = " set";
				 temp_state[0] = "";
			 }   break;
		 }
		 
		 if(*count_up_down==4){ //0-10
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", ">", menu_string[screen][0], temp_state[0]);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", " ", menu_string[screen][1], temp_state[1]);}
			if(*count_up_down==5){ //4-20
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][0], temp_state[0]);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][1], temp_state[1]);}
			
		}break;
	case 13:{ //тип аналоговых сигналов	(в данный момент не используется)
	   
		 char* temp_state[2];
		
	   if(d_lcd.data_setting[3] == 0xffffffff)
		   d_lcd.data_setting[3] =100;
		
		 switch (d_lcd.data_setting[3])
		 {
			 case 100: {
				 temp_state[0] = " set";
				 temp_state[1] = "";			 
			 }   break;
			 case 420: {
				 temp_state[1] = " set";
				 temp_state[0] = "";
			 }   break;
		 }
		 
		 if(*count_up_down==4){ //0-10
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", ">", menu_string[screen][0], temp_state[0]);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", " ", menu_string[screen][1], temp_state[1]);}
			if(*count_up_down==5){ //4-20
		    sumlen = strlen(menu_string[screen][0])+7;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%s", " ", menu_string[screen][0], temp_state[0]);
			 
		  	sumlen2 = strlen(menu_string[screen][1])+7;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%s", ">", menu_string[screen][1], temp_state[1]);}
			
		}break;
	case 16:{ //максимальное значение токового датчика мотора1	   
		 float MaxCurr;
		 
		 if(d_lcd.data_setting[6]==0xffffffff)
			  d_lcd.data_setting[6]=10;
		 
		 MaxCurr=d_lcd.data_setting[6]/10.0;
		 
		 sumlen = strlen("           ");
     tempp = malloc(sumlen);
		 snprintf(tempp, sumlen, "%.1f%s", MaxCurr, "А");
		 sumlen2 = strlen("  ");
     temp2 = malloc(sumlen2);
     snprintf(temp2, sumlen2, "%s", " ");		 
			
		}break;
  case 17:{ //максимальное значение токового датчика мотора1	   
		 float MaxCurr;
		 
		 if(d_lcd.data_setting[7]==0xffffffff)
			  d_lcd.data_setting[7]=10;
		 
		 MaxCurr=d_lcd.data_setting[7]/10.0;
		 
		 sumlen = strlen("           ");
     tempp = malloc(sumlen);
		 snprintf(tempp, sumlen, "%.1f%s", MaxCurr, "А");
		 sumlen2 = strlen("  ");
     temp2 = malloc(sumlen2);
     snprintf(temp2, sumlen2, "%s", " ");		 
			
		}break;
	case 18:{//экран "Актуальный ток двигателей"
		
		  float ActCurrMotor1, ActCurrMotor2;
		
		ActCurrMotor1=(d_lcd.value_adc_ch1*(d_lcd.data_setting[6]/10.0))*0.6666666666666667;    //коэффициент введен так ка напряжение на входе поменялось с 1-го вольта до 1,5 + от 10-ки нужно избавиться
			ActCurrMotor2=(d_lcd.value_adc_ch2*(d_lcd.data_setting[7]/10.0))*0.6666666666666667;

			if(*count_up_down==4){
	      sumlen = strlen(menu_string[screen][0])+10;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%.2f%s", ">", menu_string[screen][0],ActCurrMotor1," А");
			
				sumlen2 = strlen(menu_string[screen][1])+10;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%.2f%s", " ", menu_string[screen][1],ActCurrMotor2," А");}
			if(*count_up_down==5){
	      sumlen = strlen(menu_string[screen][0])+10;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s%.2f%s", " ", menu_string[screen][0],ActCurrMotor1," А");
			
				sumlen2 = strlen(menu_string[screen][1])+10;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s%.2f%s", ">", menu_string[screen][1],ActCurrMotor2," А");}
		}break;
	case 19:{ //время переключения	   
		 
		 if(d_lcd.data_setting[2]==0xffffffff)
			  d_lcd.data_setting[2]=60;	
		 
		 sumlen = strlen("           ");
     tempp = malloc(sumlen);
		 snprintf(tempp, sumlen, "%d%s", d_lcd.data_setting[2], " мин");
		 sumlen2 = strlen("  ");
     temp2 = malloc(sumlen2);
     snprintf(temp2, sumlen2, "%s", " ");		 
			
		}break;	
		default: {
			if(*count_up_down==4){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", ">", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", " ", menu_string[screen][1]);	}
			
			if(*count_up_down==5){
				sumlen = strlen(menu_string[screen][0])+2;
        tempp = malloc(sumlen);
        snprintf(tempp, sumlen, "%s%s", " ", menu_string[screen][0]);

			  sumlen2 = strlen(menu_string[screen][1])+2;
        temp2 = malloc(sumlen2);
        snprintf(temp2, sumlen2, "%s%s", ">", menu_string[screen][1]);	}
			
		}break;
	}
	 if(*count_up_down==4){
			  lcd_clear();			   
				lcd_set_xy(0,*count_up_down);
        lcd_out(tempp);
				free(tempp);

			  lcd_set_xy(0,*count_up_down+1);
        lcd_out(temp2);	
        free(temp2);	
	 }
	 	if(*count_up_down==5){
			  lcd_clear();			   
				lcd_set_xy(0,*count_up_down-1);
        lcd_out(tempp);
				free(tempp);

			  lcd_set_xy(0,*count_up_down);
        lcd_out(temp2);	
        free(temp2);	
	 }
	if(*count_up_down==6){
			  lcd_clear();			   
				lcd_set_xy(0,*count_up_down-2);
        lcd_out(tempp);
				free(tempp);

			  lcd_set_xy(0,*count_up_down-1);
        lcd_out(temp2);	
        free(temp2);	
	 }
		if(*count_up_down==7){
			  lcd_clear();			   
				lcd_set_xy(0,*count_up_down-3);
        lcd_out(tempp);
				free(tempp);

			  lcd_set_xy(0,*count_up_down-2);
        lcd_out(temp2);	
        free(temp2);	
	 }
	 if(*count_up_down==8){
			  lcd_clear();			   
				lcd_set_xy(0,*count_up_down-4);
        lcd_out(tempp);
				free(tempp);

			  lcd_set_xy(0,*count_up_down-3);
        lcd_out(temp2);	
        free(temp2);	
	 }
}
void Up_Down(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd)
{	  
					if(*count_up_down==6 && screen!=6 && screen!=7 && screen!=8 && screen!=1){
					   *count_up_down=4;
				  }else if(*count_up_down==7 &&(screen==8 || screen==1)){
             *count_up_down=4;
					}else if(*count_up_down==9 &&(screen==6 || screen==7)){
             *count_up_down=4;
					}	
					
					if(*count_up_down==3 && screen!=6 && screen!=7 && screen!=8 && screen!=1){
					   *count_up_down=5;
				  }else if(*count_up_down==3 &&(screen==8 || screen==1)){
             *count_up_down=6;
					}else if(*count_up_down==3 &&(screen==6 || screen==7)){
             *count_up_down=8;
					}	
					
          Update_Data(count_up_down, screen, d_lcd);								
}

void next_screeen(uint8_t* count_up_down, uint8_t screen, struct data_for_lcd d_lcd)
{         
	 if(*count_up_down==5){//чтобы на слудующем экране курсор был вверху
					*count_up_down = *count_up_down-1;
				}
	 	 if(*count_up_down==6){//чтобы на слудующем экране курсор был вверху
					*count_up_down = *count_up_down-2;
				}
		 	 if(*count_up_down==7){//чтобы на слудующем экране курсор был вверху
					*count_up_down = *count_up_down-3;
				}
			if(*count_up_down==8){//чтобы на слудующем экране курсор был вверху
					*count_up_down = *count_up_down-4;
				}
	    Update_Data(count_up_down, screen, d_lcd);    
}


