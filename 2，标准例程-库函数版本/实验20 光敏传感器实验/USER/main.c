#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc3.h"
#include "lsens.h"


//ALIENTEK ̽����STM32F407������ ʵ��18
//����������ʵ��-�⺯���汾  
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK


int main(void)
{ 
 	u8 adcx;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//��ʼ��LCD
	Lsens_Init(); 			//��ʼ������������
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"LSENS TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/5/7");	  
	POINT_COLOR=BLUE;//��������Ϊ��ɫ
	LCD_ShowString(30,130,200,16,16,"LSENS_VAL:");	             
	while(1)
	{
		adcx=Lsens_Get_Val();
		LCD_ShowxNum(30+10*8,130,adcx,3,16,0);//��ʾADC��ֵ 
		LED0=!LED0;
		delay_ms(250);	
	}
}





