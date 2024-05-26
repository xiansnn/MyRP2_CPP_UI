#if !defined(ROTARY_ENCODER_H)
#define ROTARY_ENCODER_H

#include <pico/stdio.h>
#include "switch_button.h"

class RotaryEncoder : public SwitchButtonWithIRQ, public UIController
{
private:
    uint dt_gpio;

public:
    RotaryEncoder(uint encoder_clk_gpio, uint encoder_dt_gpio,
                  gpio_irq_callback_t call_back, StructSwitchButtonConfig clk_conf = {});
    ~RotaryEncoder();
    void interrupt_service_routine(uint32_t irq_event_mask);
};

#endif // ROTARY_ENCODER_H
