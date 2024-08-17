/**
 * @file test_square_led.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief an example of usage of w_SquareLED. 
 * The LED is blinking.
 * A long press on the switch stop the blinking and let the control of the LED ON/OF with a shot press.
 * A long press returns to the blinking mode.
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
Probe pr_D1 = Probe(1);

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
protected:
public:
    bool blinking_status = true;
    bool a_bool_value = true;
    test_square_led_model();
    ~test_square_led_model();
    void process_control_event(ControlEvent _event);
};

class test_square_led_widget : public w_SquareLed
{
private:
    test_square_led_model *actual_displayed_model;

public:
    test_square_led_widget(test_square_led_model *actual_displayed_model,
                           UIDisplayDevice *display_screen,
                           size_t width,
                           size_t height,
                           uint8_t widget_anchor_x,
                           uint8_t widget_anchor_y);
    ~test_square_led_widget();
    void draw_refresh();
};

/**
 * @brief this is an example of device that inherits from UIController
 *
 */
class test_switch_button : public SwitchButton, public UIController
{
private:
    /* data */
public:
    test_switch_button(uint gpio, struct_SwitchButtonConfig conf);
    ~test_switch_button();
};

test_switch_button::test_switch_button(uint gpio, struct_SwitchButtonConfig conf)
    : SwitchButton(gpio, conf), UIController()
{
}

test_switch_button::~test_switch_button()
{
}

/**
 * @brief test and example program of  SquareLED widget.
 *
 * @return int
 */
int main()
{
    /// main steps:
    stdio_init_all();
    ///  1- create I2C bus hw peripheral and display
    HW_I2C_Master master = HW_I2C_Master(cfg_i2c);
    SSD1306 display = SSD1306(&master, cfg_ssd1306);
    /// 2- create test_common_model  as displayed object for blinking_led square_led
    test_square_led_model test_common_model = test_square_led_model();
    /// 3- create square_led as test_square_led_widget
    test_square_led_widget square_led = test_square_led_widget(&test_common_model, &display, 16, 16, 60, 32);
    /// 4- create a switchbutton
    test_switch_button central_switch = test_switch_button(CENTRAL_SWITCH_GPIO, cfg_central_switch);
    central_switch.update_current_controlled_object(&test_common_model);

    /// 5- set is_blinking period of the square_led
    square_led.set_blink_us(500000);

    /// 6- clean up the screen and draw the border of the screen
    pr_D4.hi();
    display.clear_full_screen();
    display.rect(0, 0, 128, 64);
    display.show();
    pr_D4.lo();

    while (true)
    /// 7- start infinite loop

    {
        /// - get UI switch button event and process it.
        ControlEvent event = ((test_switch_button *)test_common_model.get_current_controller())->process_sample_event();
        test_common_model.process_control_event(event);
        /**
         * NOTICE:There is a simpler way to get event. We can also forget UIController and use directly SwitchButton in
         * the following way:
         * \code
         * ControlEvent event = central_switch.process_sample_event();
         * test_common_model.process_control_event(event);
         * \endcode
         *  This avoid the burden of casting UIController and can be used when there is not special need to have UIModelObject aware about wich is displaying its data.
         *
         */

        pr_D5.hi();
        /// - refresh the widget
        square_led.draw_refresh();
        pr_D5.lo();
        /// - sleep for 20ms
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
    case ControlEvent::RELEASED_AFTER_SHORT_TIME:
        a_bool_value = !a_bool_value;
        printf("on_off=%d\n", a_bool_value);
        set_change_flag();
        break;
    case ControlEvent::LONG_PUSH:
        blinking_status = !blinking_status;
        printf("blink=%d\n", blinking_status);
        set_change_flag();
        break;

    default:
        break;
    }
}

/**
 * @brief Construct a new test square led widget::test square led widget object
 *
 * @param actual_displayed_model
 * @param display_screen
 * @param width
 * @param height
 * @param widget_anchor_x
 * @param widget_anchor_y
 */
test_square_led_widget::test_square_led_widget(test_square_led_model *actual_displayed_model,
                                               UIDisplayDevice *display_screen,
                                               size_t width,
                                               size_t height,
                                               uint8_t widget_anchor_x,
                                               uint8_t widget_anchor_y)
    : w_SquareLed(display_screen, width, height, widget_anchor_x, widget_anchor_y)
{
    this->actual_displayed_model = actual_displayed_model;
}

test_square_led_widget::~test_square_led_widget()
{
}

/**
 * @brief This function implements a special draw_refresh that takes into account the on/off and is_blinking status of the model.
 *
 * It insures that the widget consumes processing time only when its on/off status has changed.
 *
 */
void test_square_led_widget::draw_refresh()
{
    {
        if (this->actual_displayed_model->blinking_status)
        {
            bool first = on_first_semi_period(blink_period);
            pr_D1.copy(first);

            if (first and !is_lit)
            {
                this->light_on();
                rect(0, 0, frame_width, frame_height, true, FramebufferColor::WHITE);
                this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
            }
            if (!first and is_lit)
            {
                this->light_off();
                rect(0, 0, frame_width, frame_height, true, FramebufferColor::BLACK);
                draw_border();
                this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
            }
        }
        if ((this->actual_displayed_model != nullptr) and (this->actual_displayed_model->has_changed())) // check if something changed
        {
            /// check if the model a_bool_value is different from the widget lit_status
            if ((actual_displayed_model->a_bool_value) and (!is_lit))
            {
                this->light_on();
                rect(0, 0, frame_width, frame_height, true, FramebufferColor::WHITE);
            }
            if ((!actual_displayed_model->a_bool_value) and (is_lit))
            {
                this->light_off();
                rect(0, 0, frame_width, frame_height, true, FramebufferColor::BLACK);
                draw_border();
            }
            this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
            this->actual_displayed_model->clear_change_flag();
        }
    }
}
