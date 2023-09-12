/*
 * tim.cpp
 *
 *  Created on: Sep 11, 2023
 *      Author: LENOVO
 */
#include <main.h>
#include <tim.h>
#include <Timer/pwm.h>

//extern TIM_HandleTypeDef htim1;

void pwm::HAL::init(){
	MX_TIM1_Init();
	LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH1);
	LL_TIM_EnableCounter(TIM1);
	LL_TIM_GenerateEvent_UPDATE(TIM1);
}

void pwm::HAL::on(int pulse){
	LL_TIM_OC_SetCompareCH1(TIM1, pulse);
		LL_TIM_ClearFlag_UPDATE( TIM1 );
		while ( LL_TIM_IsActiveFlag_UPDATE( TIM1 ) == 0u ){}
		LL_TIM_ClearFlag_UPDATE( TIM1 );
		TIM1->BDTR |= LL_TIM_OSSI_ENABLE;
		LL_TIM_EnableAllOutputs( TIM1 );
		LL_TIM_EnableIT_UPDATE( TIM1 );
}

extern "C" void TIM1_UP_TIM16_IRQHandler(void)
{
	LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	LL_TIM_ClearFlag_UPDATE(TIM1);

}

