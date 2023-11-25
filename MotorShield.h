/*
 * MotorShield.h
 *
 *  Created on: Nov 20, 2023
 *      Author: jorgeleautaud
 */

#ifndef MOTORSHIELD_H_
#define MOTORSHIELD_H_

void initMotorControlPins(void);
void initFTM(void);
void moveForward(uint8_t percent);
void moveBackward(uint8_t percent);

#endif /* MOTORSHIELD_H_ */
