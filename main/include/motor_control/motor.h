#include <driver/ledc.h>
#include "esp_err.h"

#include "state_machine/states.h"

#define PWM_GPIO_L 5
#define PWM_GPIO_R 6

void config_pwm_channels(void);