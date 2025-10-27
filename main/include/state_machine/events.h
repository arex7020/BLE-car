#ifndef EVENTS_H
#define EVENTS_H

/* Event typedef used for the onevent function to handle commands from BLE */
typedef enum {
    // INIT Events, all these events need to trigger before leaving init
    E_GATT_RDY,
    E_PWM_RDY,
    E_BRIDGE_RDY,
    E_SPEAKER_RDY,
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
    E_LEFT_SHARP,
    E_RIGHT,
    E_RIGHT_SHARP,
    E_TURN_MODE,
    E_SPEAK1,
    E_SPEAK2,
    E_SPEAK3,
    E_SELECT,
    // AUTO Events
    E_COL_DETECTED,
    // COL Events
    E_COL_CLEARED

} Event;

/* function to call event trigger */
void event_trigger(Event e);

#endif // EVENTS_H