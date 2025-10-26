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
#include "state_machine/events.h"

#define GPIO_LN298_IN1 13
#define GPIO_LN298_IN2 14
#define GPIO_LN298_IN3 27
#define GPIO_LN298_IN4 26

#define GPIO_PWM_L 25
#define GPIO_PWM_R 33


void pwm_channels_init(uint32_t duty);

void bridge_init(void);

#endif // MOTOR_H