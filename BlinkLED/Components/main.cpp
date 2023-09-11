/*
 * main.cpp
 *
 *  Created on: Sep 11, 2023
 *      Author: LENOVO
 */
#include <main.h>
#include <gpio.h>
#include <Timer/pwm.h>
extern "C" void SystemClock_Config(void);
int main()
{
	SystemClock_Config();
	MX_GPIO_Init();
	pwm::HAL::init();
	pwm::HAL::on(8500);
while (1)
{


	//LL_mDelay(500);
}
}


