#include "speaker.h"
/* configures i2s channel tx_chan */
void i2s_init(void) {

    // channel config
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    i2s_new_channel(&chan_cfg, &tx_chan, NULL);

    // standard config
    i2s_std_config_t std_cfg = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(44100),
        .slot_cfg = {
            .slot_mode      = I2S_SLOT_MODE_STEREO,
            .data_bit_width = I2S_DATA_BIT_WIDTH_16BIT,
            .slot_mask      = I2S_STD_SLOT_BOTH,
            .ws_width       = 16
        },
        .gpio_cfg = {
            .mclk   = I2S_GPIO_UNUSED,
            .bclk = I2S_BCLK_PIN,
            .ws   = I2S_LRCLK_PIN,
            .dout = I2S_DATA_PIN,
            .din  = I2S_GPIO_UNUSED
        }
    };

    //init and enable channel
    i2s_channel_init_std_mode(tx_chan, &std_cfg);
    i2s_channel_enable(tx_chan);
}