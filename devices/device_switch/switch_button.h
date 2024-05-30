/**
 * @file switch_button.h
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#if !defined(SWITCH_BUTTON_H)
#define SWITCH_BUTTON_H

#include "pico/stdio.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "ui_core.h"

#define GPIO_HI true
#define GPIO_LO false

/**
 * @brief
 *
 */
enum class ButtonState
{
    ACTIVE,
    INACTIVE,
};

#define DEBOUNCE_us 10000
#define LONG_RELEASE_DELAY_us 3000000
#define LONG_PUSH_DELAY_us 1000000

/**
 * @brief
 *
 */
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
    /**
     * @brief
     *
     */
    uint gpio;
    /**
     * @brief
     *
     */
    bool active_lo;
    /**
     * @brief
     *
     */
    uint32_t previous_change_time_us;
    /*mechanical switch state machine*/
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_switch_active();
    /**
     * @brief
     *
     */
    bool previous_switch_active_state;
    /**
     * @brief
     *
     */
    uint debounce_delay_us;
    /*logical button state machine*/
    /**
     * @brief
     *
     */
    bool button_is_active;
    /**
     * @brief
     *
     */
    uint long_push_delay_us;
    /**
     * @brief
     *
     */
    uint long_release_delay_us;

public:
    /**
     * @brief Construct a new Switch Button object
     *
     * @param gpio
     * @param conf
     */
    SwitchButton(uint gpio, StructSwitchButtonConfig conf = {});
    /**
     * @brief Destroy the Switch Button object
     *
     */
    ~SwitchButton();
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool is_button_active();
    /**
     * @brief
     *
     * @return ControlEvent
     */
    ControlEvent process_sample_event();
};

/**
 * @brief
 *
 */
class SwitchButtonWithIRQ : public SwitchButton
{
protected:
    /**
     * @brief
     *
     * @param current_event_mask
     * @return true
     * @return false
     */
    bool is_switch_pushed(uint32_t current_event_mask);
    /**
     * @brief
     *
     */
    uint32_t irq_event_mask_config;

public:
    /**
     * @brief Construct a new Switch Button With I R Q object
     *
     * @param gpio
     * @param call_back
     * @param conf
     * @param event_mask_config
     */
    SwitchButtonWithIRQ(uint gpio, gpio_irq_callback_t call_back, StructSwitchButtonConfig conf = {},
                        uint32_t event_mask_config = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE);
    /**
     * @brief Destroy the Switch Button With I R Q object
     *
     */
    ~SwitchButtonWithIRQ();
    /**
     * @brief 
     * 
     * @param current_event_mask 
     * @return ControlEvent 
     */
    ControlEvent process_IRQ_event(uint32_t current_event_mask);
    /**
     * @brief 
     * 
     * @param enabled 
     */
    void irq_enabled(bool enabled);
};

#endif // SWITCH_BUTTON_H
