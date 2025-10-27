#ifndef SPEAKER_H
#define SPEAKER_H

#include <math.h>
#include <stdio.h>
#include "driver/i2s_std.h"

//CHANGE

#define I2S_BCLK_PIN  18
#define I2S_LRCLK_PIN 19
#define I2S_DATA_PIN  22

static i2s_chan_handle_t tx_chan = NULL;

void i2s_init(void);

#endif // SPEAKER_H