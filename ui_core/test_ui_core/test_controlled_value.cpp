#include "controlled_value.h"
#include "rotary_encoder.h"
#include "widget_print_console.h"
#include <map>
#include <string>

#define CENTRAL_SWITCH_GPIO 6
#define ENCODER_CLK_GPIO 26
#define ENCODER_DT_GPIO 21

StructSwitchButtonConfig cfg_central_switch{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_us = 1000000,
    .active_lo = true};

StructSwitchButtonConfig cfg_encoder_clk{
    .debounce_delay_us = 5000};

std::map<ControlEvent, std::string> translate_to_string{
    {ControlEvent::NOOP, "NOOP"},
    {ControlEvent::PUSH, "PUSH"},
    {ControlEvent::DOUBLE_PUSH, "DOUBLE_PUSH"},
    {ControlEvent::LONG_PUSH, "LONG_PUSH"},
    {ControlEvent::RELEASED_AFTER_LONG_TIME, "RELEASED_AFTER_LONG_TIME"},
    {ControlEvent::RELEASED_AFTER_SHORT_TIME, "RELEASED_AFTER_SHORT_TIME"},
    {ControlEvent::INCREMENT, "INCREMENT"},
    {ControlEvent::DECREMENT, "DECREMENT"},
    {ControlEvent::TIME_OUT, "TIME_OUT"}};

void shared_irq_call_back(uint gpio, uint32_t event_mask);
RotaryEncoder encoder = RotaryEncoder(ENCODER_CLK_GPIO, ENCODER_DT_GPIO,
                                      shared_irq_call_back, cfg_encoder_clk);

SwitchButton central_switch = SwitchButton(CENTRAL_SWITCH_GPIO, cfg_central_switch);

void shared_irq_call_back(uint gpio, uint32_t event_mask)
{
    switch (gpio)
    {
    case ENCODER_CLK_GPIO:
        encoder.interrupt_service_routine(event_mask);
        break;

    default:
        printf("unknown IRQ\n");
        break;
    };
}

int main()
{
    stdio_init_all();
    WTextSerialMonitor monitor = WTextSerialMonitor();
    ControlledValue value_1 = ControlledValue("val1", 0, 5, true, 1);
    ControlledValue value_2 = ControlledValue("val2", 0, 10, false, 1);
    ControlledValue current_controlled_value = value_1;
    current_controlled_value.update_current_controller(&encoder);
    monitor.set_displayed_object(&current_controlled_value);
    std::string monitor_text;
    while (true)
    {
        ControlEvent event = central_switch.process_sample_event();
        current_controlled_value.process_control_event(event);
        monitor_text = "monitor: " + current_controlled_value.get_name() + ":" + std::to_string(current_controlled_value.get_value()) + "\n";

        monitor.set_text_to_display(monitor_text);
        monitor.refresh();
        sleep_ms(20);
    }

    return 0;
}
