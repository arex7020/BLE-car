/**
 * File: drive.h
 * Description: Defines driving/steering functions to control wheels
 * Author: arex7020
 * Date: 2025-10-19
 */

#ifndef DRIVE_H
#define DRIVE_H

#include "motor_control/motor.h"

void drive_forward(void);
void drive_backward(void);
void drive_left(void);
void drive_right(void);

#endif //DRIVE_H