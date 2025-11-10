#ifndef ULTRASOUND_H
#define ULTRASOUND_H

#include "esp_attr.h"
#include "driver/gpio.h"

#define ECHO_PIN 99
#define TRIG_PIN 100

void hcsr04_init(void);
void hcsr04_trigger(void);
void IRAM_ATTR echo_isr_handler(void *arg);

#endif // ULTRASOUND_H
