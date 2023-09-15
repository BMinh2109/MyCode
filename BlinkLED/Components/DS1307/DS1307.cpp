/*
 * RTC.cpp
 *
 *  Created on: Sep 13, 2023
 *      Author: Nguyen Binh Minh
 */
#include <DS1307/DS1307.h>
#include <main.h>
#include <i2c.h>
#include <stm32g4xx_it.h>

#define DS1307_ADDR (0x68<<1)
#define HAL_UNLOCKED 0x00U
#define MAX_NBYTE_SIZE 255U

#define I2C_MEMADD_SIZE_8BIT            (0x00000001U)
#define I2C_MEM_ADD_LSB(__ADDRESS__)              ((uint8_t)((uint16_t)((__ADDRESS__) & (uint16_t)(0x00FFU))))
#define I2C_MEM_ADD_MSB(__ADDRESS__)              ((uint8_t)((uint16_t)(((uint16_t)((__ADDRESS__) & \
                                                                         (uint16_t)(0xFF00U))) >> 8U)))

uint8_t DS1307_RTC::I2C_HAL::B2D (uint8_t num){
	return ((num>>4)*10 + (num&0x0f));
//	return((num/10*16) + (num % 10));
}
uint8_t DS1307_RTC::I2C_HAL::D2B (uint8_t num){
	return ((num/10)<<4|(num%10));
//	return((num/16*10) + (num % 16));
}

void DS1307_RTC::I2C_HAL::init(){
	MX_I2C1_Init();
	LL_I2C_Enable(I2C1);
	LL_I2C_EnableIT_ADDR(I2C1);
	LL_I2C_EnableIT_NACK(I2C1);
	LL_I2C_EnableIT_ERR(I2C1);
	LL_I2C_EnableIT_STOP(I2C1);
}

void DS1307_RTC::I2C_HAL::getTime(DS1307_Data *pData, I2C_TypeDef *hi2c, uint16_t Size, uint16_t MemAddSize, uint16_t MemAddress){ //FIXME
//	LL_I2C_GenerateStartCondition(hi2c);
//	LL_I2C_HandleTransfer(I2C1, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE);
//	LL_I2C_TransmitData8(I2C1, 0x00);
//	LL_I2C_HandleTransfer(I2C1, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
//	pData->sec = LL_I2C_ReceiveData8(I2C1);
//	pData->min = LL_I2C_ReceiveData8(I2C1);
//	pData->hour = LL_I2C_ReceiveData8(I2C1);
//	pData->day = LL_I2C_ReceiveData8(I2C1);
//	pData->date = LL_I2C_ReceiveData8(I2C1);
//	pData->month = LL_I2C_ReceiveData8(I2C1);
//	pData->year = LL_I2C_ReceiveData8(I2C1);
//	LL_I2C_GenerateStopCondition(I2C1);
	uint8_t buffer[7];
	LL_I2C_GenerateStartCondition(hi2c);
	hi2c->State     = HAL_I2C_STATE_BUSY_RX; //FIXME
	hi2c->Mode      = HAL_I2C_MODE_MEM;
	hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

	    /* Prepare transfer parameters */
	hi2c->pBuffPtr  = buffer;
	hi2c->XferCount = Size;
	hi2c->XferISR   = NULL;
	//I2C_RequestMemoryRead
	LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE);
	if(MemAddSize == I2C_MEMADD_SIZE_8BIT){
		hi2c->TXDR = I2C_MEM_ADD_LSB(MemAddress);
	}
	else{
		hi2c->TXDR = I2C_MEM_ADD_MSB(MemAddress);
		hi2c->TXDR = I2C_MEM_ADD_LSB(MemAddress);
	}
	do{
	    hi2c->Lock = HAL_UNLOCKED;     //FIXME
	}while (0U);
	//ConfigTransfer
	/* Set NBYTES to write and reload if hi2c->XferCount > MAX_NBYTE_SIZE and generate RESTART */
	if(hi2c->XferCount > MAX_NBYTE_SIZE){
		hi2c->XferSize = MAX_NBYTE_SIZE; //255u
		//I2C_TransferConfig(hi2c, DS1307_ADDR, (uint8_t)hi2c->XferSize, I2C_RELOAD_MODE, I2C_GENERATE_START_READ);
//		LL_I2C_SetSlaveAddr(hi2c, DS1307_ADDR & 0x3FF);
//		LL_I2C_Set
		LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_START_READ);
	}
	else{
		hi2c->XferSize = hi2c->XferCount;
		LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ);
	}
	do{
	  *hi2c->pBuffPtr = (uint8_t)hi2c->RXDR;
	  hi2c->pBuffPtr++;
	  hi2c->XferSize--;
	  hi2c->XferCount--;
	  if ((hi2c->XferCount != 0U) && (hi2c->XferSize == 0U))
	  {
		if (hi2c->XferCount > MAX_NBYTE_SIZE)
		{
		  hi2c->XferSize = MAX_NBYTE_SIZE;
		  LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
		}
		else
		{
		  hi2c->XferSize = hi2c->XferCount;
		  LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
		}
	  }
	}while (hi2c->XferCount > 0U);
	I2C_RESET_CR2(hi2c); //FIXME
    hi2c->State = HAL_I2C_STATE_READY;
	hi2c->Mode  = HAL_I2C_MODE_NONE; //FIXME

	LL_I2C_GenerateStopCondition(hi2c);
	pData->sec = DS1307_RTC::I2C_HAL::B2D(buffer[0]);
	pData->min = DS1307_RTC::I2C_HAL::B2D(buffer[1]);
	pData->hour = DS1307_RTC::I2C_HAL::B2D(buffer[2]);
	pData->day = DS1307_RTC::I2C_HAL::B2D(buffer[3]);
	pData->date = DS1307_RTC::I2C_HAL::B2D(buffer[4]);
	pData->month = DS1307_RTC::I2C_HAL::B2D(buffer[5]);
	pData->year = DS1307_RTC::I2C_HAL::B2D(buffer[6]);
}


//void rtc::I2C_HAL::setDate(){
//
//}
//
void DS1307_RTC::I2C_HAL::setTime(I2C_TypeDef *hi2c, uint16_t Size, uint16_t MemAddSize, uint16_t MemAddress, uint8_t hour, uint8_t min, uint8_t sec, uint8_t day, uint8_t date, uint8_t month, uint8_t year){
	uint8_t buffer[8];
	buffer[0] = DS1307_RTC::I2C_HAL::D2B(sec);
	buffer[1] = DS1307_RTC::I2C_HAL::D2B(min);
	buffer[2] = DS1307_RTC::I2C_HAL::D2B(hour);
	buffer[3] = DS1307_RTC::I2C_HAL::D2B(day);
	buffer[4] = DS1307_RTC::I2C_HAL::D2B(date);
	buffer[5] = DS1307_RTC::I2C_HAL::D2B(month);
	buffer[6] = DS1307_RTC::I2C_HAL::D2B(year);

	LL_I2C_GenerateStartCondition(hi2c);
	hi2c->State     = HAL_I2C_STATE_BUSY_TX; //FIXME
	hi2c->Mode      = HAL_I2C_MODE_MEM;
	hi2c->ErrorCode = HAL_I2C_ERROR_NONE;

	    /* Prepare transfer parameters */
	hi2c->pBuffPtr  = buffer;
	hi2c->XferCount = Size;
	hi2c->XferISR   = NULL;
	//I2C_RequestMemoryWrite
	LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_START_WRITE);
	if(MemAddSize == I2C_MEMADD_SIZE_8BIT){ //FIXME
		hi2c->TXDR = I2C_MEM_ADD_LSB(MemAddress);
	}
	else{
		hi2c->TXDR = I2C_MEM_ADD_MSB(MemAddress);
		hi2c->TXDR = I2C_MEM_ADD_LSB(MemAddress);
	}
	do{
		hi2c->Lock = HAL_UNLOCKED;     //FIXME
	}while (0U);
	//ConfigTransfer
	/* Set NBYTES to write and reload if hi2c->XferCount > MAX_NBYTE_SIZE and generate RESTART */
	if (hi2c->XferCount > MAX_NBYTE_SIZE){
	    hi2c->XferSize = MAX_NBYTE_SIZE;
		LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
	}
	else{
	    hi2c->XferSize = hi2c->XferCount;
		LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
	}
	do{
	  hi2c->Instance->TXDR = *hi2c->pBuffPtr;
	  hi2c->pBuffPtr++;
	  hi2c->XferSize--;
	  hi2c->XferCount--;
	  if ((hi2c->XferCount != 0U) && (hi2c->XferSize == 0U))
	  {
		if (hi2c->XferCount > MAX_NBYTE_SIZE)
		{
		  hi2c->XferSize = MAX_NBYTE_SIZE;
		  LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_RELOAD, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
		}
		else
		{
		  hi2c->XferSize = hi2c->XferCount;
		  LL_I2C_HandleTransfer(hi2c, DS1307_ADDR, LL_I2C_ADDRSLAVE_7BIT, (uint8_t)hi2c->XferSize, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_NOSTARTSTOP_NOSTARTSTOP);
		}
	  }
	}while (hi2c->XferCount > 0U);
	I2C_RESET_CR2(hi2c); //FIXME
	hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE; //FIXME
}
//
//}

extern "C" void I2C1_EV_IRQHandler(void)
{
	if(LL_I2C_IsActiveFlag_TXIS(I2C1)){}
	else if (LL_I2C_IsActiveFlag_RXNE(I2C1)){}
	else if (LL_I2C_IsActiveFlag_TCR(I2C1)){}
	else if (LL_I2C_IsActiveFlag_STOP(I2C1)){
	    LL_I2C_ClearFlag_STOP(I2C1);
	    if (!LL_I2C_IsActiveFlag_TXE(I2C1))
	    {
	      LL_I2C_ClearFlag_TXE(I2C1);
	    }
	}

//  if(LL_I2C_IsActiveFlag_ADDR(I2C1)){
//	  if(LL_I2C_GetAddressMatchCode(I2C1) == 0x68){
//		  if(LL_I2C_GetTransferDirection(I2C1) == LL_I2C_DIRECTION_READ){
//			  LL_I2C_ClearFlag_ADDR(I2C1);
//			  LL_I2C_EnableIT_TX(I2C1);
//		  }
//		  else{
//		      LL_I2C_ClearFlag_ADDR(I2C1);
//		      //Error_Callback();
//		  }
//	  }
//	  else{
//	      LL_I2C_ClearFlag_ADDR(I2C1);
//	      //Error_Callback();
//	  }
//  }
//  else if (LL_I2C_IsActiveFlag_NACK(I2C1))
//  {
//    LL_I2C_ClearFlag_NACK(I2C1);
//  }
//  else if (LL_I2C_IsActiveFlag_TXIS(I2C1))
//  {
//    //
//  }
//  else if (LL_I2C_IsActiveFlag_STOP(I2C1))
//  {
//    LL_I2C_ClearFlag_STOP(I2C1);
//    if (!LL_I2C_IsActiveFlag_TXE(I2C1))
//    {
//      LL_I2C_ClearFlag_TXE(I2C1);
//    }
//  }
//  else if (!LL_I2C_IsActiveFlag_TXE(I2C1)){}
//  else if (LL_I2C_IsActiveFlag_STOP(I2C1))
//  {
//    LL_I2C_ClearFlag_STOP(I2C1);
//  }
//  else if (LL_I2C_IsActiveFlag_RXNE(I2C1)){}
//  else
//  {
//    //Error_Callback();
//  }

}
