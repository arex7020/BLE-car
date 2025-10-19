/**
 * File: states.h
 * Description: Defines driving/steering functions to control wheels
 * Author: arex7020
 * Date: 2025-10-13
 */

#ifndef STATES_H
#define STATES_H

#include <stdio.h>
#include "esp_log.h"
#include "gatt-nimble/bluetooth_gatt_server.h"
#include "motor_control/drive.h"
#include "state_machine/events.h"

/* LOG State tag */
static const char *STATE_TAG = "STATE";
/* LOG Event tag */
static const char *EVENT_TAG = "EVENT";

struct State;


/* NOTE:
*  To call change_state and event_trigger, other files dont need to
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

/* functions to change the state */
void change_state(State *new_state);

#endif // STATES_H