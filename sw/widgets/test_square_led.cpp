/**
 * @file test_square_led.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget_square_led.h"
#include "ssd1306.h"
#include "probe.h"
#include "switch_button.h"

Probe pr_D4 = Probe(4);
Probe pr_D5 = Probe(5);

/// @brief define central switch config
struct_SwitchButtonConfig cfg_central_switch{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_us = 1000000,
    .active_lo = true};
#define CENTRAL_SWITCH_GPIO 6

/// @brief  define i2c config
struct_ConfigMasterI2C cfg_i2c{
    .i2c = i2c0,
    .sda_pin = 8,
    .scl_pin = 9,
    .baud_rate = I2C_FAST_MODE};
/// @brief define SSD1306 display config
struct_ConfigSSD1306 cfg_ssd1306{
    .i2c_address = 0x3C,
    .vertical_offset = 0,
    .scan_SEG_inverse_direction = true,
    .scan_COM_inverse_direction = true,
    .contrast = 128,
    .frequency_divider = 1,
    .frequency_factor = 0};

class test_square_led_model : public UIModelObject
{
private:


public:
    bool blinking_object = true;
    bool on_off_object = true;
    test_square_led_model();
    ~test_square_led_model();
    void process_control_event(ControlEvent _event);
};

/**
 * @brief
 *
 * @return int
 */
int main()
{
    stdio_init_all();
    /// create I2C bus hw peripheral and display
    HW_I2C_Master master = HW_I2C_Master(cfg_i2c);
    SSD1306 display = SSD1306(&master, cfg_ssd1306);
    /// create blinking_led led1 led 2 as w_SquareLed
    w_SquareLed blinking_led = w_SquareLed(&display, 8, 8, 20, 32);
    w_SquareLed led1 = w_SquareLed(&display, 8, 8, 60, 32);
    w_SquareLed led2 = w_SquareLed(&display, 8, 8, 100, 32);
    /// create blinking_model model1 model2 as displayed object for blinking_led led1 led2
    test_square_led_model blinking_model = test_square_led_model();
    test_square_led_model model1 = test_square_led_model();
    test_square_led_model model2 = test_square_led_model();
    blinking_led.set_display_screen(&display);
    led1.set_display_screen(&display);
    led2.set_display_screen(&display);
    blinking_led.set_displayed_model(&blinking_model);
    led1.set_displayed_model(&model1);
    led2.set_displayed_model(&model2);
    /// create a switchbutton
    SwitchButton central_switch = SwitchButton(CENTRAL_SWITCH_GPIO, cfg_central_switch);

    blinking_led.set_blink(1000000);
    led1.light_on();
    led2.light_off();

    pr_D4.hi();
    display.clear_full_screen();
    display.rect(0, 0, 128, 64);
    display.show();
    pr_D4.lo();

    while (true)
    {
        ControlEvent event = central_switch.process_sample_event();
        pr_D5.hi();
        blinking_led.draw_refresh();
        blinking_model.set_change_flag();
        led1.draw_refresh();
        led2.draw_refresh();
        pr_D5.lo();

        sleep_ms(20);
    }

    return 0;
}

test_square_led_model::test_square_led_model()
    : UIModelObject()
{
}

test_square_led_model::~test_square_led_model()
{
}

void test_square_led_model::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    case ControlEvent::PUSH:
        on_off_object = !on_off_object;
        set_change_flag();
        break;
    case ControlEvent::LONG_PUSH:
        blinking_object = !blinking_object;
        set_change_flag();
        break;

    default:
        break;
    }
}
