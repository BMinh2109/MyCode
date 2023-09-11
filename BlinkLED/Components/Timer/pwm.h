/*
 * tim.h
 *
 *  Created on: Sep 11, 2023
 *      Author: LENOVO
 */

#ifndef PWM_H_
#define PWM_H_

namespace pwm
{
class HAL{
public:
	static void init();
	static void on(int pulse);
	static void off();
};
}



#endif /* PWM_H_ */
