#include "motor_control/drive.h"
//DEFINE FUNCTIONS THAT WILL BE CALLED in the S_MANUAL on_event function

// maybe implement logic that calls one of these functions from on_event, then do nothing until it enters drive_idle, 
// so we dont spam data to gpio pins when we dont have to, this should be done in states.c

/**
 * 
 * Forward:     IN1: 0 IN2: 1, IN3: 0 IN4: 1 
 * Reverse:     IN1: 1 IN2: 0, IN3: 1 IN4: 0
 * 
 * Steer Left:  IN1: 0 IN2: 0, IN3: 0 IN4: 1
 * Steer Right: IN1: 0 IN2: 1, IN3: 0 IN4: 0
 * 
 * Sharp Left:  IN1: 1 IN2: 0, IN3: 0 IN4: 1
 * Sharp Right: IN1: 0 IN2: 1, IN3: 1 IN4: 0
 * 
 * Brake:       IN1: 1 IN2: 1, IN3: 1 IN4: 1
 * Freewheel:   IN1: 0 IN2: 0, IN3: 0 IN4: 0
 */

 /* Set and Update duty cycle to chosen duty percentage */
void set_duty(uint8_t pwr) {
    uint16_t duty = pwr/100 * 8192;
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty, 0);
    ledc_set_duty_and_update(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_1, duty, 0);
}

/* Freewheel/Brake motors */
void drive_idle(void) {
    //might set this to 1(Brake) instead of 0(Freewheel)
    gpio_set_level(GPIO_LN298_IN1, 0);
    gpio_set_level(GPIO_LN298_IN2, 0);
    gpio_set_level(GPIO_LN298_IN3, 0);
    gpio_set_level(GPIO_LN298_IN4, 0);
}

/* Motors drive forward */
void drive_forward(void) {

    gpio_set_level(GPIO_LN298_IN1, 0);
    gpio_set_level(GPIO_LN298_IN2, 1);
    gpio_set_level(GPIO_LN298_IN3, 0);
    gpio_set_level(GPIO_LN298_IN4, 1);
}

/* Motors drive reverse */
void drive_reverse(void) {

    gpio_set_level(GPIO_LN298_IN1, 1);
    gpio_set_level(GPIO_LN298_IN2, 0);
    gpio_set_level(GPIO_LN298_IN3, 1);
    gpio_set_level(GPIO_LN298_IN4, 0);
}

/* Motors steer left */
void steer_left(void) {

    gpio_set_level(GPIO_LN298_IN1, 0);
    gpio_set_level(GPIO_LN298_IN2, 0);
    gpio_set_level(GPIO_LN298_IN3, 0);
    gpio_set_level(GPIO_LN298_IN4, 1);
}
/* Motors steer left sharply*/
void steer_left_sharp(void) {

    gpio_set_level(GPIO_LN298_IN1, 1);
    gpio_set_level(GPIO_LN298_IN2, 0);
    gpio_set_level(GPIO_LN298_IN3, 0);
    gpio_set_level(GPIO_LN298_IN4, 1);
}

/* Motors steer right */
void steer_right(void) {

    gpio_set_level(GPIO_LN298_IN1, 0);
    gpio_set_level(GPIO_LN298_IN2, 1);
    gpio_set_level(GPIO_LN298_IN3, 0);
    gpio_set_level(GPIO_LN298_IN4, 0);

}

/* Motors steer right sharply */
void steer_right_sharp(void) {

    gpio_set_level(GPIO_LN298_IN1, 0);
    gpio_set_level(GPIO_LN298_IN2, 1);
    gpio_set_level(GPIO_LN298_IN3, 1);
    gpio_set_level(GPIO_LN298_IN4, 0);
}

