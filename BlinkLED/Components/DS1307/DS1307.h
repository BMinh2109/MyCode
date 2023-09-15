/*
 * RTC.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Nguyen Binh Minh
 */
#include <main.h>
#ifndef DS1307_RTC_H_
#define DS1307_RTC_H_

namespace DS1307_RTC{
class I2C_HAL{
public:
	static void init();
	static void getTime(DS1307_Data *pData, I2C_TypeDef *hi2c, uint16_t Size, uint16_t MemAddSize, uint16_t MemAddress);
//	static void setDate();
	static void setTime(I2C_TypeDef *hi2c, uint16_t Size, uint16_t MemAddSize, uint16_t MemAddress, uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, uint8_t month, uint8_t year);
	static uint8_t B2D(uint8_t num);
	static uint8_t D2B(uint8_t num);
};
}




#endif /* DS1307_RTC_H_ */
