#ifndef STATES_H
#define STATES_H

#include <stdio.h>
#include "esp_log.h"
#include "gatt-nimble/bluetooth_gatt_server.h"

/* LOG State tag */
static const char *STATE_TAG = "STATE";
/* LOG Event tag */
static const char *EVENT_TAG = "EVENT";

struct State;

/* Event typedef used for the onevent function to handle commands from BLE */
typedef enum {
    // INIT Events, all these events need to trigger before leaving init
    E_GATT_RDY,
    E_PWM_RDY,
    E_BRIDGE_RDY,
    E_SPEAK_RDY,
    E_DAC_RDY,
    E_USS_RDY,
    // IDLE Events
    E_GATT_CON,
    E_START,
    // MAN Events
    E_IDLE,
    E_FORWARD,
    E_REVERSE,
    E_LEFT,
    E_RIGHT,
    E_AUTO_SELECT,
    E_SPEAK1,
    E_SPEAK2,
    E_SPEAK3,
    E_SPEAK4,
    // AUTO Events
    E_COL_DETECTED,
    // COL Events
    E_COL_CLEARED

} Event;


/* NOTE:
*  To call change_state and trigger_event, other files dont need to
*  know about these 3 typedefs. maybe move them into seperate header in the future. 
*/


/* StateAction* function that returns void and takes State* struct as argument */
typedef void (*StateAction)(struct State *);

/* same as above but also takes Event as argument, used for on_event functions */
typedef void (*StateActionEvent)(struct State *, Event e);

/* State typedef containing state name(used for logs), and receives on_enter, exit and event functions */
typedef struct  State {
    const char *name;
    StateAction on_enter;
    StateAction on_exit;
    StateActionEvent on_event;

} State;

/* external forward declare for states, will be called in other files, extern  */
extern State S_INIT;
extern State S_IDLE;
extern State S_SPEAK;
extern State S_AUTO;
extern State S_COL;
extern State S_MAN;

/* functions to trigger events and change the state */
void change_state(State *new_state);
void trigger_event(Event e);

#endif // STATES_H