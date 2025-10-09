#include "state_machine/states.h"

/* Global pointer to state */
State *current_state;

/* Maybe create StateManager typedef, so example: StateMgr.change_state can be called instead */

void change_state(State* new_state)
{   
    /* checks if current on_exit function existson current state before changing state, then checks and runs on_enter function on new state */
    if(current_state && current_state->on_exit) 
        current_state->on_exit(current_state);

    current_state = new_state;

    if(current_state && current_state->on_enter)
        current_state->on_enter(current_state);
}

void trigger_event(Event e)
{
    if(current_state && current_state->on_event)
        current_state->on_event(current_state, e);
}

/* if _on_ functions become too big, move them out into seperate files */

/* on_enter, exit and event functions for each state */
void init_on_enter(State *s) 
{  
    ESP_LOGI(STATE_TAG, "Entering %s", s->name); 
    // gatt_init(), ultrasound_init(), dac_init(), speaker_init()

    ble_main_init();
}
void init_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Exiting %s", s->name);   }
void init_on_event(State *s, Event e) 
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);

    // wait for all init events before changing state
    static bool e_gatt_rdy = false;
    static bool e_motor_rdy = true;
    static bool e_uss_rdy = true;
    static bool e_dac_rdy = true;
    static bool e_speak_rdy = true;
    

    switch (e)
    {
    case E_GATT_RDY:
        e_gatt_rdy = true;
        break;
    case E_MOTOR_RDY:
        e_motor_rdy = true;
        break;
    case E_USS_RDY:
        e_uss_rdy = true;
        break;
    case E_DAC_RDY:
        e_dac_rdy = true;
        break;
    case E_SPEAK_RDY:
        e_speak_rdy = true;
        break;
    default:
        ESP_LOGW(STATE_TAG, "Unexpected event recieved");
        break;
    }

    // check if ready to change state to idle
    if (e_gatt_rdy && e_motor_rdy && e_uss_rdy && e_dac_rdy && e_speak_rdy) {
        change_state(&S_IDLE);
    }

}

void idle_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void idle_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Exiting %s", s->name);   }
void idle_on_event(State *s, Event e) 
{
    ESP_LOGI(STATE_TAG, "%s event received", s->name);
    //in idle until we are connected to Bluetooth and press start on gamepad, //maybe add led logic

    static bool e_gatt_con = false;
    static bool e_start = false;

    switch (e)
    {
    case E_GATT_CON:
        e_gatt_con = true;
        break;
    case E_START:
        e_start = true;
        break;
    default:
        ESP_LOGW(STATE_TAG, "Unexpected event recieved");
        break;
    }

    if(e_gatt_con && e_start) {
        change_state(&S_MAN);
    }

}

//Maybe put speaker in thread, maybe state not needed
void speak_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name); }
void speak_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name); }
void speak_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);    
}

void auto_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void auto_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void auto_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);

    switch (e)
    {
    case E_COL_DETECTED:
            change_state(&S_COL);
        break;
    default:
        ESP_LOGW(STATE_TAG, "Unexpected event recieved");
        break;
    }
}

void col_on_enter(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void col_on_exit(State *s)   {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void col_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name); 

    switch (e)
    {
    case E_COL_CLEARED:
            change_state(&S_AUTO);
        break;
    default:
        ESP_LOGW(STATE_TAG, "Unexpected event recieved");
        break;
    }   
}

void man_on_enter(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void man_on_exit(State *s)   {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void man_on_event(State *s, Event e) 
{
    ESP_LOGI(STATE_TAG, "%s event received", s->name);

    switch (e) {
    case E_IDLE:
        ESP_LOGI("%s", "IDLE",EVENT_TAG);
        break;
    case E_FORWARD:
        ESP_LOGI("%s", "FORWARD",EVENT_TAG);
        break;
    case E_REVERSE:
        ESP_LOGI("%s", "REVERSE",EVENT_TAG);
        break;
    case E_LEFT:
        ESP_LOGI("%s", "LEFT",EVENT_TAG);
        break;
    case E_RIGHT:
        ESP_LOGI("%s", "RIGHT",EVENT_TAG);
        break;
    case E_SPEAK1:
        ESP_LOGI("%s", "SPEAK1",EVENT_TAG);
        change_state(&S_SPEAK);
        break;
    case E_SPEAK2:
        ESP_LOGI("%s", "SPEAK2",EVENT_TAG);
        change_state(&S_SPEAK);
        break;
    case E_SPEAK3:
        ESP_LOGI("%s", "SPEAK3",EVENT_TAG);
        change_state(&S_SPEAK);
        break;
    case E_SPEAK4:
        ESP_LOGI("%s", "SPEAK4",EVENT_TAG);
        change_state(&S_SPEAK);
        break;
    case E_AUTO_SELECT:
        ESP_LOGI("%s", "AUTO",EVENT_TAG);
        change_state(&S_AUTO);
        break;
    default:
        ESP_LOGW(STATE_TAG, "Unexpected event recieved");
        break;
    }
}

/* create and bind State objects to state functions  */
State S_INIT = {"INIT", init_on_enter, init_on_exit, init_on_event};
State S_IDLE = {"IDLE", idle_on_enter, idle_on_exit, idle_on_event};
State S_SPEAK = {"SPEAK", speak_on_enter, speak_on_exit, speak_on_event};
State S_AUTO = {"AUTO", auto_on_enter, auto_on_exit, auto_on_event};
State S_COL = {"COL",col_on_enter, col_on_exit, col_on_event,};
State S_MAN = {"MAN", man_on_enter, man_on_exit, man_on_event};











