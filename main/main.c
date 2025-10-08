#include <stdio.h>
#include "esp_log.h"
#include "state_machine/states.h"

void app_main(void)
{
    ESP_LOGI("BLE-car", "Hello world!");
    change_state(&S_INIT);
}

