#include "test_controlled_value.h"
#include "test_manager.h"
#include "rotary_encoder.h"
#include "test_widget_on_serial_monitor.h"
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
    Test_Manager manager = Test_Manager();
    manager.update_current_controller(&encoder);

    TestObjectManagerWidget manager_widget = TestObjectManagerWidget();
    manager_widget.set_displayed_object(&manager);


    TestIncrementalValue value_0 = TestIncrementalValue("val0", 0, 5, true, 1);
    value_0.update_status(ControlledObjectStatus::HAS_FOCUS);
    manager.add_managed_model(&value_0);

    TestCursorWidgetWithIncrementalValue value_0_widget = TestCursorWidgetWithIncrementalValue();
    value_0_widget.set_displayed_object(&value_0);

    TestIncrementalValue value_1 = TestIncrementalValue("val1", 0, 10, false, 1);
    manager.add_managed_model(&value_1);

    TestCursorWidgetWithIncrementalValue value_1_widget = TestCursorWidgetWithIncrementalValue();
    value_1_widget.set_displayed_object(&value_1);

    while (true)
    {
        ControlEvent event = central_switch.process_sample_event();
        manager.process_control_event(event);
        manager_widget.refresh();
        value_0_widget.refresh();
        value_1_widget.refresh();
        sleep_ms(20);
    }

    return 0;
}

