#include "controlled_value.h"
#include "rotary_encoder.h"
#include "widget_print_serial_monitor.h"
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
    WTextSerialMonitor serial_monitor_console = WTextSerialMonitor();
    WCursorOnSerialMonitor cursor_on_console = WCursorOnSerialMonitor();
    ControlledValue value_1 = ControlledValue("val1", 0, 5, true, 1);
    ControlledValue value_2 = ControlledValue("val2", 0, 10, false, 1);
    ControlledValue current_controlled_value = value_2;
    current_controlled_value.update_status(ControlledObjectStatus::IS_ACTIVE);
    current_controlled_value.update_current_controller(&encoder);
    serial_monitor_console.set_displayed_object(&current_controlled_value);
    cursor_on_console.set_displayed_object(&current_controlled_value);
    while (true)
    {
        ControlEvent event = central_switch.process_sample_event();
        current_controlled_value.process_control_event(event);
        serial_monitor_console.refresh(); // FIXME pb qd 2 widget affiche la meme donnée : la premiere clear change flag
        cursor_on_console.refresh();
        sleep_ms(20);
    }

    return 0;
}
