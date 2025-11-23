#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include "esp_attr.h"
#include "driver/gpio.h"
#include "esp_timer.h"

#define ECHO_PIN 99
#define TRIG_PIN 100

void hcsr_init(void);
void hcsr_trigger(void);
void IRAM_ATTR echo_isr_handler(void *arg);

static int64_t echo_start = 0;
static float hcsr_distance = 0;


#endif // ULTRASOUND_H
