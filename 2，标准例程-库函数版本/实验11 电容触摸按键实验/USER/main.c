#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tpad.h"

//ALIENTEK ̽����STM32F407������ ʵ��11
//���ݴ�������ʵ�� -�⺯���汾 
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	u8 t=0; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);     //��ʼ����ʱ����
	uart_init(115200);	 //��ʼ�����ڲ�����Ϊ115200
	LED_Init();					 //��ʼ��LED
	
	TPAD_Init(8);				//��ʼ����������,��84/4=21MhzƵ�ʼ���
   	while(1)
	{					  						  		 
 		if(TPAD_Scan(0))	//�ɹ�������һ��������(�˺���ִ��ʱ������15ms)
		{
			LED1=!LED1;		//LED1ȡ��
		}
		t++;
		if(t==15)		 
		{
			t=0;
			LED0=!LED0;		//LED0ȡ��,��ʾ������������
		}
		delay_ms(10);
	}
}
