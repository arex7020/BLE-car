#include <stdio.h>
#include "esp_log.h"
#include "state_machine/states.h"


void main_task(){

    change_state(&S_INIT);

    while (1) {
        
        //keep main loop alive
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}

void app_main(void)
{
    xTaskCreate(main_task, "MainTask", 4096, NULL, 5, NULL);
    
}

