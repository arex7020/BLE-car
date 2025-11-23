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

void event_trigger(Event e)
{
    if(current_state && current_state->on_event)
        current_state->on_event(current_state, e);
}

/* if _on_ functions become too big, move them out into seperate files */

/* on_enter, exit and event functions for each state */
void init_on_enter(State *s) 
{  
    ESP_LOGI(s->name, "Entering %s", s->name); 
    // ultrasound_init(), dac_init(), speaker_init()

    ble_main_init();
    pwm_channels_init(4096);
    bridge_init();
}
void init_on_exit(State *s)  {  ESP_LOGI(s->name, "Exiting %s", s->name);   }
void init_on_event(State *s, Event e) 
{  
    // wait for all init events before changing state
    static bool e_gatt_rdy = false;
    static bool e_pwm_rdy = false;
    static bool e_bridge_rdy = false;
    static bool e_hcsr_rdy = false;
    static bool e_dac_rdy = false;
    static bool e_speak_rdy = false;


    /* NOT YET IMPLEMENTED, SET TO TRUE FOR TESTING */
    
    e_dac_rdy = true;
    e_speak_rdy = true;

    switch (e)
    {
    case E_GATT_RDY:
        e_gatt_rdy = true;
        ESP_LOGI(s->name, "GATT READY");
        break;
    case E_PWM_RDY:
        e_pwm_rdy = true;
        ESP_LOGI(s->name, "PWM READY");
        break;
    case E_BRIDGE_RDY:
        e_bridge_rdy = true;
        ESP_LOGI(s->name, "BRIDGE READY");
        break;
    case E_HCSR_RDY:
        e_hcsr_rdy = true;
        ESP_LOGI(s->name, "DISTANCE SENSOR READY");
        break;
    case E_DAC_RDY:
        e_dac_rdy = true;
        ESP_LOGI(s->name, "BRIDGE READY");
        break;
    case E_SPEAKER_RDY:
        e_speak_rdy = true;
        ESP_LOGI(s->name, "SPEAKER READY");
        break;
    default:
        ESP_LOGW(s->name, "Unexpected event recieved, Ignoring");
        break;
    }

    // check if ready to change state to idle
    if (e_gatt_rdy && e_pwm_rdy && e_bridge_rdy && e_hcsr_rdy && e_dac_rdy && e_speak_rdy) {
        change_state(&S_IDLE);
    }

}

void idle_on_enter(State *s) {  ESP_LOGI(s->name, "Entering %s", s->name);  }
void idle_on_exit(State *s)  {  ESP_LOGI(s->name, "Exiting %s", s->name);   }
void idle_on_event(State *s, Event e) 
{
    //in idle until we are connected to Bluetooth and press start on gamepad, //maybe add led logic

    static bool e_gatt_con = false;
    bool e_start = false;   //nonstatic so it expects start event when returning from MAN state

    switch (e)
    {
    case E_IDLE:
        //Here to avoid unexpected event print when releasing start button
        break;
    case E_GATT_CON:
        e_gatt_con = true;
        ESP_LOGI(s->name, "GATT CONNECTED");
        break;
    case E_START:
        e_start = true;
        ESP_LOGI(s->name, "START");
        break;
    default:
        ESP_LOGW(s->name, "Unexpected event recieved, Ignoring");
        break;
    }

    if(e_gatt_con && e_start) {
        change_state(&S_MAN);
    }

}

void man_on_enter(State *s)  {  ESP_LOGI(s->name, "Entering %s", s->name);    }
void man_on_exit(State *s)   {  ESP_LOGI(s->name, "Exiting %s", s->name);    }
void man_on_event(State *s, Event e) 
{

    switch (e) {
    case E_IDLE:
        ESP_LOGI(s->name, "IDLE");
        drive_idle();
        break;
    case E_FORWARD:
        ESP_LOGI(s->name, "FORWARD");
        drive_forward();
        break;
    case E_REVERSE:
        ESP_LOGI(s->name, "REVERSE");
        drive_reverse();
        break;
    case E_LEFT:
        ESP_LOGI(s->name, "LEFT");
        steer_left();
        break;
    case E_LEFT_SHARP:
        ESP_LOGI(s->name, "LEFT_SHARP");
        steer_left_sharp();
        break;
    case E_RIGHT:
        ESP_LOGI(s->name, "RIGHT");
        steer_right();
        break;
    case E_RIGHT_SHARP:
        ESP_LOGI(s->name, "RIGHT_SHARP");
        steer_right_sharp();
        break;
    case E_TURN_MODE:
        ESP_LOGI(s->name, "TURN MODE");
        break;
    case E_SPEAK1:
        ESP_LOGI(s->name, "SPEAK1");
        break;
    case E_SPEAK2:
        ESP_LOGI(s->name, "SPEAK2");
        break;
    case E_SPEAK3:
        ESP_LOGI(s->name, "SPEAK3");
        break;
    case E_SELECT:
        ESP_LOGI(s->name, "SELECT");
        change_state(&S_AUTO);
        break;
    case E_START:
        ESP_LOGI(s->name, "START");
        change_state(&S_IDLE);
        break;
    default:
        ESP_LOGW(s->name, "Unexpected event recieved, Ignoring");
        break;
    }
}

void auto_on_enter(State *s) 
{
    ESP_LOGI(s->name, "Entering %s", s->name);  
    xTaskCreate(hcsr_trigger, "HcsrTrig", 4096, NULL, 5, NULL);
}
void auto_on_exit(State *s)  {  ESP_LOGI(s->name, "Exiting %s", s->name);  }
void auto_on_event(State *s, Event e)
{  

    switch (e)
    {
    case E_IDLE:
        //Here to avoid unexpected event print when releasing select button
        break;
    case E_SELECT:
        ESP_LOGI(s->name, "UNSELECT");
        change_state(&S_MAN);
        break;
    case E_COL_DETECTED:
            ESP_LOGI(s->name, "COLLISION DETECTED");
            change_state(&S_COL);
        break;
    default:
        ESP_LOGW(s->name, "Unexpected event recieved, Ignoring");
        break;
    }
}

void col_on_enter(State *s)  {  ESP_LOGI(s->name, "Entering %s", s->name);    }
void col_on_exit(State *s)   {  ESP_LOGI(s->name, "Exiting %s", s->name);    }
void col_on_event(State *s, Event e)
{   

    switch (e)
    {
    case E_COL_CLEARED:
            ESP_LOGI(s->name, "COLLISION CLEARED");
            change_state(&S_AUTO);
        break;
    default:
        ESP_LOGW(s->name, "Unexpected event recieved, Ignoring");
        break;
    }   
}

//Maybe put speaker in thread, maybe state not needed
void speak_on_enter(State *s) {  ESP_LOGI(s->name, "Entering %s", s->name); }
void speak_on_exit(State *s)  {  ESP_LOGI(s->name, "Exiting %s", s->name); }
void speak_on_event(State *s, Event e)
{  
    ESP_LOGI(s->name, "%s event received", s->name);    
}

/* create and bind State objects to state functions  */
State S_INIT = {"INIT", init_on_enter, init_on_exit, init_on_event};
State S_IDLE = {"IDLE", idle_on_enter, idle_on_exit, idle_on_event};
State S_MAN = {"MAN", man_on_enter, man_on_exit, man_on_event};
State S_AUTO = {"AUTO", auto_on_enter, auto_on_exit, auto_on_event};
State S_COL = {"COL",col_on_enter, col_on_exit, col_on_event,};
State S_SPEAK = {"SPEAK", speak_on_enter, speak_on_exit, speak_on_event};











