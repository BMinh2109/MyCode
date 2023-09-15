/*
 * I2C_OwnFunct.cpp
 *
 *  Created on: Sep 12, 2023
 *      Author: LENOVO
 */
#include <main.h>
#include <i2c.h>
#include <I2C/I2C_OwnFunct.h>
#include <stm32g4xx_it.h>

void I2C_Own::HAL::init(){
	MX_I2C1_Init();
	LL_I2C_Enable(I2C1);
	LL_I2C_EnableIT_ADDR(I2C1);
	LL_I2C_EnableIT_NACK(I2C1);
	LL_I2C_EnableIT_ERR(I2C1);
	LL_I2C_EnableIT_STOP(I2C1);
}

uint8_t I2C_Own::HAL::read(uint8_t data){
	//Handle_I2C_Master();
	LL_I2C_GenerateStartCondition(I2C1);
	//while (!LL_I2C_IsActiveFlag_SB(I2C1)) {}
	//LL_I2C_HandleTransfer(I2C1, 0x68, LL_I2C_ADDRSLAVE_7BIT, LL_I2C_ADDRSLAVE_7BIT, LL_I2C_MODE_RELOAD, LL_I2C_MODE_READ);
	LL_I2C_TransmitData8(I2C1, 0x68);
    data = LL_I2C_ReceiveData8(I2C1);
    LL_I2C_GenerateStopCondition(I2C1);
    return data;
}

void I2C_Own::HAL::write(){
	LL_I2C_GenerateStartCondition(I2C1);
	LL_I2C_TransmitData8(I2C1, 0x68);
	LL_I2C_TransmitData8(I2C1, (uint8_t)200);
	LL_I2C_GenerateStopCondition(I2C1);
}

//extern "C" void I2C1_EV_IRQHandler(void)
//{
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
//    //Master_Complete_Callback();
//  }
//  else if (LL_I2C_IsActiveFlag_RXNE(I2C1))
//  {
//    //Master_Reception_Callback();
//  }
//  else
//  {
//    //Error_Callback();
//  }

  /* USER CODE BEGIN I2C1_EV_IRQn 1 */

  /* USER CODE END I2C1_EV_IRQn 1 */



