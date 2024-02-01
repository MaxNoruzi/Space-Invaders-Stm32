/*
 * Keypad.h
 *
 *  Created on: Jan 23, 2023
 *      Author: mo_n1
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_
extern GPIO_TypeDef *const rowPorts[];
extern const uint16_t rowPins[];
extern GPIO_TypeDef *const columnPorts[];
extern const uint16_t columnPins[];
extern uint32_t lastGpioExti;
void keypadAssign(uint16_t gpioPin);

#endif /* INC_KEYPAD_H_ */
