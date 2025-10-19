/**
 * File: drive.h
 * Description: Defines driving/steering functions to control wheels
 * Author: arex7020
 * Date: 2025-10-19
 */
#ifndef DRIVE_H
#define DRIVE_H

#include "motor_control/motor.h"

void drive_idle(void);
void drive_forward(void);
void drive_backward(void);

void steer_left(void);
void steer_left_sharp(void);

void steer_right(void);
void steer_right_sharp(void);

#endif //DRIVE_H