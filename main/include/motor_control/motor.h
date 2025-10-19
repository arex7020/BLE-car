/**
 * File: motor.h
 * Description: Initializes PWM channels and Pins used for DC motors and LN298 H-bridge
 * Author: arex7020
 * Date: 2025-10-19
 */

#ifndef MOTOR_H
#define MOTOR_H

#include <driver/ledc.h>
#include "esp_err.h"
#include "driver/gpio.h"

#include "state_machine/states.h"

#define GPIO_PWM_L 5
#define GPIO_PWM_R 6
#define GPIO_LN298_IN1 7
#define GPIO_LN298_IN2 8
#define GPIO_LN298_IN3 9
#define GPIO_LN298_IN4 10



void config_pwm_channels(void);

void config_ln298_pins(void);

#endif // MOTOR_H