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
 * @brief The logical state of the switch
 *
 */
enum class ButtonState
{
    /**
     * @brief the switch is pushed
     * 
     */
    ACTIVE,
    /**
     * @brief the switch is not pushed
     * 
     */
    INACTIVE,
};

#define DEBOUNCE_us 10000
#define LONG_RELEASE_DELAY_us 3000000
#define LONG_PUSH_DELAY_us 1000000

/**
 * @brief These are the values used to configure a switch button
 *
 */
struct StructSwitchButtonConfig
{
    /**
     * @brief The time during which all changes in the switch state is ignored
     *
     */
    uint debounce_delay_us = DEBOUNCE_us;
    /**
     * @brief if the button is released after long_release_delay_us (in microseconds) a ControlEvent::RELEASED_AFTER_LONG_TIME is returned,
     * else a ControlEvent::RELEASED_AFTER_SHORT_TIME is released.
     *
     */
    uint long_release_delay_us = LONG_RELEASE_DELAY_us;
    /**
     * @brief when a button is pushed more than long_push_delay_us (in microseconds) a ControlEvent::LONG_PUSH is returned.
     *
     */
    uint long_push_delay_us = LONG_PUSH_DELAY_us;
    /**
     * @brief this indicates that when the button is pushed, a logical LO (0) signal is read.
     *
     */
    bool active_lo = true;
};

/**
 * @brief SwitchButton status is sampled periodically by software.
 * Switch status is the status of the physical switch device.
 *
 * Button status is the logical status of the button (regardless the switch is wired active Lo or HI)
 * During each period, the status of the button is compared to the previous status and the function member process_sample_event() return an evant accordingly.
 *
 * SwitchButton can be associated with UIController only if button belongs to a UI.
 *
 */
class SwitchButton
{
protected:
    /**
     * @brief the GPIO that reads the logical state of the switch (pushed or released)
     *
     */
    uint gpio;
    /**
     * @brief this indicates that when the switch is pushed, a logical LO (0) signal is read.
     *
     */
    bool active_lo;
    /**
     * @brief the system time stored on the previous switch state change.
     *
     */
    uint32_t previous_change_time_us;
    /*mechanical switch state machine*/
    /**
     * @brief the logical status of the switch
     *
     * @return true if switch status is read LO (resp. HI) if active_lo is true (resp. false)
     * @return false if switch status is read HI (resp. LO) if active_lo is true (resp. false)
     */
    bool is_switch_active();
    /**
     * @brief The previous state read during the previous period.
     *
     */
    bool previous_switch_active_state;
    /**
     * @brief The time during which all changes in the switch state is ignored
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
     * @brief when a button is pushed more than long_push_delay_us (in microseconds) a ControlEvent::LONG_PUSH is returned.
     *
     */
    uint long_push_delay_us;
    /**
     * @brief if the button is released after long_release_delay_us (in microseconds) a ControlEvent::RELEASED_AFTER_LONG_TIME is returned,
     * else a ControlEvent::RELEASED_AFTER_SHORT_TIME is released.
     *
     */
    uint long_release_delay_us;

public:
    /**
     * @brief Construct a new SwitchButton object
     *
     * @param gpio the microcontroller GPIO that read the switch status
     * @param conf the configuration data according StructSwitchButtonConfig
     */
    SwitchButton(uint gpio, StructSwitchButtonConfig conf = {});
    /**
     * @brief Destroy the SwitchButton object
     *
     */
    ~SwitchButton();
    /**
     * @brief return the value of the logical status of the button
     *
     */
    bool is_button_active();
    /**
     * @brief the periodic routine that process deboucing, press and release of the switch.
     *
     * @return ControlEvent
     */
    ControlEvent process_sample_event();
};

/**
 * @brief SwitchButtonWithIRQ status is processed by an Interrupt Service Routine.
 * It is derived from SwithButton, but debouncing, press and release are processed differently.
 *
 * SwitchButtonWithIRQ can be associated with UIController only if button belongs to a UI.
 *
 */
class SwitchButtonWithIRQ : public SwitchButton
{
private:
    /**
     * @brief A memory slot reserved to store the irq_event_mask.
     */
    uint32_t irq_event_mask_config;
    /**
     *@brief return the logical status of the switch. It process rising and falling edges of the interrupt, according to the active_lo status of the switch.
     *
     * @param current_event_mask
     * @return true if switch status is read LO (resp. HI) if active_lo is true (resp. false)
     * @return false if switch status is read HI (resp. LO) if active_lo is true (resp. false)
     */
    bool is_switch_pushed(uint32_t current_event_mask);

protected:
public:
    /**
     * @brief and function used to enable/disable interrupt during Interrupt Service Routine (ISR)
     *
     * @param enabled
     */
    void irq_enabled(bool enabled);
    /**
     * @brief Construct a new SwitchButtonWithIRQ object
     *
     * @param gpio The microcontroller GPIO connected to the switch
     * @param call_back tie ISR (interrupt Service Routine) that process IRQ event
     * @param conf the configuration value of the switch
     * @param event_mask_config the rising/falling edge configuratio of the irq
     */
    SwitchButtonWithIRQ(uint gpio, gpio_irq_callback_t call_back, StructSwitchButtonConfig conf = {},
                        uint32_t event_mask_config = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE);
    /**
     * @brief Destroy the SwitchButtonWithIRQ object
     *
     */
    ~SwitchButtonWithIRQ();
    /**
     * @brief Process IRQ event and return the resulting event.
     *
     * @param current_event_mask
     * @return ControlEvent
     */
    ControlEvent process_IRQ_event(uint32_t current_event_mask);
};

#endif // SWITCH_BUTTON_H
