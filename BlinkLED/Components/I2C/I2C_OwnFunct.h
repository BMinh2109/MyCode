/*
 * I2C_OwnFunct.h
 *
 *  Created on: Sep 12, 2023
 *      Author: LENOVO
 */

#ifndef I2C_I2C_OWNFUNCT_H_
#define I2C_I2C_OWNFUNCT_H_

namespace I2C_Own{
class HAL{
public:
	static void init();
	static void enable();
	static uint8_t read(uint8_t data);
	static void write();
};
}



#endif /* I2C_I2C_OWNFUNCT_H_ */
