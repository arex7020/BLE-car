#include "state_machine/states.h"



/* Global pointer to state */
State *current_state;

/* Maybe create StateManager typedef, so example: StateMgr.change_state can be called instead */

void change_state(State* new_state)
{   
    /* checks if current on_exit function existson current state before changing state, then checks and runs on_enter function on new state */
    if(current_state->on_exit)  current_state->on_exit(current_state);
    current_state = new_state;
    if(current_state->on_enter) current_state->on_enter(current_state);
}

void trigger_event(Event e)
{
    if(current_state && current_state->on_event)  current_state->on_event(current_state, e);
}

/* if _on_ functions become too big, move them out into seperate files */

/* on_enter, exit and event functions for each state */
void init_on_enter(State *s) 
{  
    ESP_LOGI(STATE_TAG, "Entering %s", s->name); 
    // start GATT_server, init utrasoundsensor, init dac, etc
}
void init_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Exiting %s", s->name);   }
void init_on_event(State *s, Event e) 
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);
    //
};

void idle_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void idle_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Exiting %s", s->name);   }
void idle_on_event(State *s, Event e) 
{
    ESP_LOGI(STATE_TAG, "%s event received", s->name);
    //in idle until we are connected to Bluetooth, then:
    //change_state(&S_MANUAL)
};

//Maybe put speaker in thread, maybe state not needed
void speak_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name); }
void speak_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name); }
void speak_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);    
};

void auto_on_enter(State *s) {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void auto_on_exit(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);  }
void auto_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name);    
};

void col_on_enter(State *s)  {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void col_on_exit(State *s)   {  ESP_LOGI(STATE_TAG, "Entering %s", s->name);    }
void col_on_event(State *s, Event e)
{  
    ESP_LOGI(STATE_TAG, "%s event received", s->name); 
};

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
    case E_SPEAK:
        ESP_LOGI("%s", "SPEAK",EVENT_TAG);
        change_state(&S_SPEAK);
        break;
    case E_AUTO:
        ESP_LOGI("%s", "AUTO",EVENT_TAG);
        change_state(&S_AUTO);
        break;
    default:
        ESP_LOGI("%s", "IDK",EVENT_TAG);
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











