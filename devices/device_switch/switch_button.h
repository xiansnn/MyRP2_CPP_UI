#if !defined(SWITCH_BUTTON_H)
#define SWITCH_BUTTON_H

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "ui_core.h"

#define GPIO_HI true
#define GPIO_LO false

enum class ButtonState
{
    ACTIVE,
    INACTIVE,
};

#define DEBOUNCE_us 10000
#define LONG_RELEASE_DELAY_us 3000000
#define LONG_PUSH_DELAY_us 1000000

struct StructSwitchButtonConfig
{
    uint debounce_delay_us = DEBOUNCE_us;
    uint long_release_delay_us = LONG_RELEASE_DELAY_us;
    uint long_push_delay_us = LONG_PUSH_DELAY_us;
    bool active_lo = true;
};

/// @brief SwitchButton can be associated with UIController only if button belongs to a UI
class SwitchButton
{
protected:
    uint gpio;
    bool active_lo;
    uint32_t previous_change_time_us;
    /*mechanical switch state machine*/
    bool is_switch_active();
    bool previous_switch_active_state;
    uint debounce_delay_us;
    /*logical button state machine*/
    bool button_is_active;
    uint long_push_delay_us;
    uint long_release_delay_us;

public:
    SwitchButton(uint gpio, StructSwitchButtonConfig conf = {});
    ~SwitchButton();
    bool is_button_active();
    ControlEvent process_sample_event();
};

class SwitchButtonWithIRQ : public SwitchButton
{
protected:
    bool is_switch_pushed(uint32_t current_event_mask);
    uint32_t irq_event_mask_config;

public:
    SwitchButtonWithIRQ(uint gpio, gpio_irq_callback_t call_back, StructSwitchButtonConfig conf = {},
                        uint32_t event_mask_config = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE);
    ~SwitchButtonWithIRQ();
    ControlEvent process_IRQ_event(uint32_t current_event_mask);
    void irq_enabled(bool enabled);
};

#endif // SWITCH_BUTTON_H
