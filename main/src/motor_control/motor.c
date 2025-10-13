#include "motor_control/motor.h"

/* Configures Timer and two channels for each DC motor */
void config_pwm_channels(void)
{
    ledc_timer_config_t ledc_timer = {
    .speed_mode     = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_13_BIT,   //8192
    .timer_num      = LEDC_TIMER_0,
    .freq_hz        = 5000,
    .clk_cfg        = LEDC_AUTO_CLK
    };

    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t channel_conf_left = {
    .gpio_num   = PWM_GPIO_L,             // Replace with your motor control pin
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel    = LEDC_CHANNEL_0,         // Use 0-7 for ESP32
    .intr_type  = LEDC_INTR_DISABLE,
    .timer_sel  = LEDC_TIMER_0,           // Must match timer used above
    .duty       = 0,                      // Start with 0% duty
    .hpoint     = 0
    };

    ledc_channel_config(&channel_conf_left);
    
    ledc_channel_config_t channel_conf_right = {
        .gpio_num   = PWM_GPIO_R,             // Replace with your motor control pin
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_1,         // Use 0-7 for ESP32
        .intr_type  = LEDC_INTR_DISABLE,
        .timer_sel  = LEDC_TIMER_0,           // Must match timer used above
        .duty       = 0,                      // Start with 0% duty
        .hpoint     = 0
    };
    
    ledc_channel_config(&channel_conf_right);

    trigger_event(E_PWM_RDY);

}