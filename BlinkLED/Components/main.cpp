/*
 * main.cpp
 *
 *  Created on: Sep 11, 2023
 *      Author: LENOVO
 */
#include <DS1307/DS1307.h>
#include <main.h>
#include <gpio.h>
#include <Timer/pwm.h>
#include <i2c.h>
#define Read_Address 0x68

extern "C" void SystemClock_Config(void);

DS1307_Data DateTime;

int main()
{
	SystemClock_Config();
	MX_GPIO_Init();
	DS1307_RTC::I2C_HAL::init();
	DS1307_RTC::I2C_HAL::setTime(I2C1, 7, 1, 0x00, 9, 0, 0, 5, 21, 9, 23);
//	pwm::HAL::init();
//	pwm::HAL::on(8500);
while (1)
{
	DS1307_RTC::I2C_HAL::getTime(&DateTime, I2C1, 7, 1, 0x00);
	LL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	LL_mDelay(1000);
}
}


