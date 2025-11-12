#include "collision_avoidance/ultrasound.h"

#define SPEED_OF_SOUND 343.0f

/* Interrupt handler for ECHO PIN */
void IRAM_ATTR echo_isr_handler(void *arg) {

    int64_t now = esp_timer_get_time();

    if (gpio_get_level(ECHO_PIN) == 1)
    {
        echo_start = now;
    }
    else
    {
        int64_t pulse = now - echo_start;
        hcsr_distance = (pulse / 2.0f) * SPEED_OF_SOUND / 1000000; 
    }
    
}

/* Init pins for collision avoidance sensor */
void hcsr_init(void) {
    gpio_config_t conf_hcsr_trig = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << TRIG_PIN
    }; gpio_config(&conf_hcsr_trig);

    gpio_config_t conf_hcsr_echo = {
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = 1ULL << ECHO_PIN
    }; gpio_config(&conf_hcsr_echo);
    
    gpio_install_isr_service(0);
    gpio_isr_handler_add(ECHO_PIN, echo_isr_handler, NULL);

}

/*  */
void hcsr_trigger(void) {
    gpio_set_level(TRIG_PIN, 1);
    //put this in xtask cus esp_rom_delay literally pauses the whole cpu
    esp_rom_delay_us(10);
    gpio_set_level(TRIG_PIN, 0);
}



