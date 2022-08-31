#include "task.h"
#include "lcd.h"
#include "rtthread.h"


/*控制变量*/
uint16_t on_off_flag=0;
uint8_t setting_flag=1;

uint32_t vin=0,temp=0;
float vout=0,iout=0;

/*Spinbox 控制变量*/
int8_t encode_pos=7;
int16_t encoder_value=0;
Spinbox_TypeDef spinbox_v,spinbox_i;


/*ADC 变量*/
extern ADC_HandleTypeDef hadc;
/*DAC 变量*/
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim3;

/*---------------------LDP_Thread_Spinbox_Entry-------------------------------------*/
void spinbox_vset_init(void)
{	
	spinbox_v.value=330;
	spinbox_v.range_max=3200;
	spinbox_v.dec_point=2;
	spinbox_v.digit_count=4;
	spinbox_v.index=0;
}

void spinbox_iset_int(void)
{
	spinbox_i.value=1000;
	spinbox_i.range_max=3000;
	spinbox_i.dec_point=3;
	spinbox_i.digit_count=4;
	spinbox_v.index=1;	
}

void LDP_Thread_Spinbox_Entry(void *parameter)
{
	spinbox_vset_init();
	spinbox_iset_int();
	while(1)
	{
		rt_thread_mdelay(50);
		if(encoder_value)
		{
			if(encode_pos>3)
			{
				spinbox_v.value += encoder_value*mypow(10,encode_pos-4);
				if(spinbox_v.value>spinbox_v.range_max)spinbox_v.value=spinbox_v.range_max;
				if(spinbox_v.value<=0)spinbox_v.value=0;
//				rt_kprintf("spinbox_v.value=%d\n",spinbox_v.value);	
			}
			else
			{			
				spinbox_i.value += encoder_value*mypow(10,encode_pos);
				if(spinbox_i.value>spinbox_i.range_max)spinbox_i.value=spinbox_i.range_max;
				if(spinbox_i.value<=0)spinbox_i.value=0;
//				rt_kprintf("spinbox_i.value=%d\n",spinbox_i.value);		
			}
			setting_flag=1;
			encoder_value=0;
		}
	}
}

/*---------------------LDP_Thread_Settings_Entry-------------------------------------*/
void LDP_Thread_Settings_Entry(void *parameter)
{
	float vset=0,iset=0;
	while(1)
	{
		rt_thread_mdelay(50);
		if(setting_flag)
		{
//			vset = spinbox_v.value;//for test
//			vset = ((float)spinbox_v.value-0.0141)/0.8029;//polyfit no #1
			vset = ((float)spinbox_v.value-0.0178)/0.8062;//polyfit no #2 or no #3
			iset = spinbox_i.value;//for test
//			iset = ((float)spinbox_i.value-0.8169)/0.7328;//polyfit no #1
//			iset = ((float)spinbox_i.value-0.1445)/0.676;//polyfit no #2
			HAL_DAC_SetValue(&hdac,DAC_CHANNEL_2,DAC_ALIGN_12B_R,(uint16_t)iset);
			if(on_off_flag)HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,(uint16_t)vset);
			else HAL_DAC_SetValue(&hdac,DAC_CHANNEL_1,DAC_ALIGN_12B_R,0);		
			setting_flag=0;	
		}	
	}	
}

/*---------------------LDP_Thread_GUI_Entry-------------------------------------*/
void OLED_Show_Spinbox(Spinbox_TypeDef *spinbox_t)
{
	uint16_t spinbox_v_h=(spinbox_t->value)/mypow(10,spinbox_t->dec_point);
	uint16_t spinbox_v_l=(spinbox_t->value)%mypow(10,spinbox_t->dec_point);
	if(spinbox_t->index)
	{
		OLED_ShowNum(32,0,spinbox_v_h,spinbox_t->digit_count-spinbox_t->dec_point,6,12,0);
		OLED_ShowChar(32+7*(spinbox_t->digit_count-spinbox_t->dec_point),0,'.',6,12,1);
		OLED_ShowNum(32+7*(spinbox_t->digit_count-spinbox_t->dec_point+1),0,spinbox_v_l,spinbox_t->dec_point,6,12,0);		
	}
	else
	{
		OLED_ShowNum(85,0,spinbox_v_h,spinbox_t->digit_count-spinbox_t->dec_point,6,12,1);
		OLED_ShowChar(85+7*(spinbox_t->digit_count-spinbox_t->dec_point),0,'.',6,12,1);
		OLED_ShowNum(85+7*(spinbox_t->digit_count-spinbox_t->dec_point+1),0,spinbox_v_l,spinbox_t->dec_point,6,12,0);			
	}
}

void OLED_Show_Spinbox_pos(int8_t pos,uint8_t mode)
{
	if(mode)
	{
		switch(pos)
		{
			case 0:
				OLED_ShowChar(111,0,' ',6,12,1);
				break;
			case 1:
				OLED_ShowChar(105,0,' ',6,12,1);
				break;
			case 2:
				OLED_ShowChar(99,0,' ',6,12,1);
				break;
			case 3:
				OLED_ShowChar(85,0,' ',6,12,1);
				break;		
			case 4:
				OLED_ShowChar(59,0,' ',6,12,1);
				break;	
			case 5:
				OLED_ShowChar(53,0,' ',6,12,1);
				break;	
			case 6:
				OLED_ShowChar(38,0,' ',6,12,1);
				break;	
			case 7:
				OLED_ShowChar(32,0,' ',6,12,1);
				break;		
		}
	}
}

void OLED_Show_Out(uint16_t value, uint8_t mode)
{
	uint16_t value_h=0,value_l=0;
	if(mode)
	{	
		value_h=value/100;
		value_l=value%100;
		OLED_ShowNum(51,12,value_h,2,12,24,1);
		OLED_ShowChar(77,12,'.',12,24,1);
		OLED_ShowNum(89,12,value_l,2,12,24,0);				
	}
	else
	{
		value_h=value/1000;
		value_l=value%1000;	
		OLED_ShowNum(51,40,value_h,1,12,24,1);
		OLED_ShowChar(64,40,'.',12,24,1);
		OLED_ShowNum(77,40,value_l,3,12,24,0);				
	}
}


void LDP_Thread_GUI_Entry(void *parameter)
{
	uint8_t show_spinbox_t=0;
	/*Init OLED*/
	OLED_Init();
	/*output uint*/
	OLED_ShowString(120,22,"V",6,12,DISPLAY_MODE);
	OLED_ShowString(120,51,"A",6,12,DISPLAY_MODE);
	/*input uint*/
	OLED_ShowString(28,15,"v",6,12,DISPLAY_MODE);
	/*setting ui*/
	OLED_ShowString(0,0,"SET:",6,12,DISPLAY_MODE);
	OLED_ShowString(67,0,"V",6,12,DISPLAY_MODE);
	OLED_ShowString(120,0,"A",6,12,DISPLAY_MODE);	
	/*output parameter ui*/
	OLED_ShowString(15,40,"CV",6,12,DISPLAY_MODE);
	OLED_ShowString(15,52,"OFF",6,12,DISPLAY_MODE);
	/*output ICON*/
	LDP_Show_ICON();
	
	while(1)
	{
		rt_thread_mdelay(150);
		
		OLED_Show_Spinbox(&spinbox_v);
		OLED_Show_Spinbox(&spinbox_i);
		show_spinbox_t =! show_spinbox_t;
		OLED_Show_Spinbox_pos(encode_pos,show_spinbox_t);
		
		OLED_Show_Out(vout,1);
		OLED_Show_Out(iout,0);
		
		OLED_ShowNum(15,15,vin,2,6,12,1);
		OLED_ShowNum(15,27,temp,2,6,12,1);
		
		if(on_off_flag)OLED_ShowString(15,52,"ON ",6,12,1);
		else OLED_ShowString(15,52,"OFF",6,12,1);
		if(iout>=spinbox_i.value)OLED_ShowString(15,40,"CC",6,12,DISPLAY_MODE);
		else OLED_ShowString(15,40,"CV",6,12,DISPLAY_MODE);
		OLED_Refresh_Gram();
	}
}


/* LDP_Thread_Creat
Thread 1: LDP_Thread_FB ADC Sampling and process
Thread 2: LDP_Thread_Spinbox  spinbox for encoder edit
Thread 3:	LDP_Thread_Settings	update settings for LDP Power
Thread 4:	LDP_Thread_GUI	GUI create and refresh
*/

void LDP_Thread_Creat(void)
{	
	rt_thread_t TD_Spinbox = RT_NULL;
	rt_thread_t TD_Settings = RT_NULL;
	rt_thread_t TD_GUI = RT_NULL;
	if(HAL_ADCEx_Calibration_Start(&hadc)!=HAL_OK)rt_kprintf("ADC_Calibration_Error!\n");	
	HAL_TIM_Base_Start_IT(&htim3);

	/* 创建线程 1 LDP_Thread_Spinbox*/
	TD_Spinbox = rt_thread_create("TD_Spinbox",
											LDP_Thread_Spinbox_Entry, RT_NULL,
											THREAD_STACK_SIZE,
											THREAD_PRIORITY+1, THREAD_TIMESLICE);

	/* 如果获得线程控制块，启动这个线程 */
	if (TD_Spinbox != RT_NULL)rt_thread_startup(TD_Spinbox);

	/* 创建线程 2 LDP_Thread_Settings*/
	TD_Settings = rt_thread_create("TD_Settings",
												LDP_Thread_Settings_Entry, RT_NULL,
												THREAD_STACK_SIZE,
												THREAD_PRIORITY+2, THREAD_TIMESLICE);

	/* 如果获得线程控制块，启动这个线程 */
	if (TD_Settings != RT_NULL)rt_thread_startup(TD_Settings);
	
	/* 创建线程 3 LDP_GUI*/
	TD_GUI = rt_thread_create("TD_GUI",
										LDP_Thread_GUI_Entry, RT_NULL,
										THREAD_STACK_SIZE*2,
										THREAD_PRIORITY+3, THREAD_TIMESLICE);

	/* 如果获得线程控制块，启动这个线程 */
	if (TD_GUI != RT_NULL)rt_thread_startup(TD_GUI);
}


