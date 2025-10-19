#include "motor_control/motor.h"

/* Defines pwm timer, channels and binds it to PWM_GPIO Pin, starts at 0% duty cycle */
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
    .gpio_num   = GPIO_PWM_L,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel    = LEDC_CHANNEL_0,
    .intr_type  = LEDC_INTR_DISABLE,
    .timer_sel  = LEDC_TIMER_0,
    .duty       = 0,
    .hpoint     = 0
    };

    ledc_channel_config(&channel_conf_left);
    
    ledc_channel_config_t channel_conf_right = {
        .gpio_num   = GPIO_PWM_R,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel    = LEDC_CHANNEL_1,
        .timer_sel  = LEDC_TIMER_0,
        .duty       = 0,
        .hpoint     = 0
    };
    
    ledc_channel_config(&channel_conf_right);

    event_trigger(E_PWM_RDY);

}

/* Configure LN298_IN pins to Output */
void config_ln298_pins(void)
{
    gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_LN298_IN1) | (1ULL << GPIO_LN298_IN2) | (1ULL << GPIO_LN298_IN3) | (1ULL << GPIO_LN298_IN4),
    .mode = GPIO_MODE_OUTPUT,
    .pull_up_en = GPIO_PULLUP_DISABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);

    event_trigger(E_BRIDGE_RDY);
}


