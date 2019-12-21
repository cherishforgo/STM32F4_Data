#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"    
#include "malloc.h"  
#include "wm8978.h"	 
#include "usbd_audio_core.h"
#include "stm324xg_usb_audio_codec.h"
#include "usbd_usr.h"
#include "usb_conf.h" 	
//ALIENTEK ̽����STM32F407������ ʵ��52
//USB���� ʵ�� ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK 

 USB_OTG_CORE_HANDLE USB_OTG_dev;
extern vu8 bDeviceState;		//USB���� ���
extern u8 volume;				//����(��ͨ����������)
int main(void)
{        
 	u8 key;
	u8 Divece_STA=0XFF;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ��  
 	WM8978_Init();				//��ʼ��WM8978
	WM8978_ADDA_Cfg(1,0);		//����DAC
	WM8978_Input_Cfg(0,0,0);	//�ر�����ͨ��
	WM8978_Output_Cfg(1,0);		//����DAC��� 
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 

 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(30,50,200,16,16,"Explorer STM32F4");	
	LCD_ShowString(30,70,200,16,16,"USB Sound Card TEST");	
	LCD_ShowString(30,90,200,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(30,110,200,16,16,"2014/7/22");	
	LCD_ShowString(30,130,200,16,16,"KEY2:Vol-  KEY0:vol+");	
 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
 	LCD_ShowString(30,160,200,16,16,"VOLUME:");		 //������ʾ 	  
	LCD_ShowxNum(30+56,160,DEFAULT_VOLUME,3,16,0X80);//��ʾ����
	LCD_ShowString(30,180,200,16,16,"USB Connecting...");//��ʾ���ڽ������� 	    
 	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&AUDIO_cb,&USR_cb);    
	while(1)
	{ 
		key=KEY_Scan(1);	//֧������
		if(key)
		{
			if(key==KEY0_PRES)		//KEY0����,��������
			{
				volume++;
				if(volume>100)volume=100; 
			}else if(key==KEY2_PRES)//KEY2����,��������
			{ 
				if(volume)volume--;
				else volume=0;
			} 
			EVAL_AUDIO_VolumeCtl(volume);
			LCD_ShowxNum(30+56,160,volume,3,16,0X80);//��ʾ���� 
			delay_ms(20);
		} 
		if(Divece_STA!=bDeviceState)//״̬�ı���
		{
			if(bDeviceState==1)LCD_ShowString(30,180,200,16,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else LCD_ShowString(30,180,200,16,16,"USB DisConnected ");				//��ʾUSB����ʧ��
			Divece_STA=bDeviceState;
		}	
		delay_ms(20);
	} 
}






