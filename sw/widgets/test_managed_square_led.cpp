/**
 * @file test_managed_square_led.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief Example of how to program several LEDcontrolled by a single rotary encoder
 * @version 0.1
 * @date 2024-08-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "widget_square_led.h"
#include "ssd1306.h"
#include "probe.h"
#include "rotary_encoder.h"

#define CENTRAL_SWITCH_GPIO 6
#define ENCODER_CLK_GPIO 26
#define ENCODER_DT_GPIO 21

#define TIME_OUT_us 3000000

/// @brief ########## Debug/Observer Probe for logic analyser section ##########
Probe pr_D4 = Probe(4);
Probe pr_D5 = Probe(5);
Probe pr_D1 = Probe(1);

/// @brief ########## configuration section ##########

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

/// @brief define central switch config
struct_SwitchButtonConfig cfg_central_switch{
    .debounce_delay_us = 5000,
    .long_release_delay_us = 1000000,
    .long_push_delay_us = 1000000,
    .active_lo = true};

/// @brief ########## rotary encoder behavior section ##########

/// @brief config of the rotary encoder clock signal
struct_SwitchButtonConfig cfg_encoder_clk{
    .debounce_delay_us = 5000};

void shared_irq_call_back(uint gpio, uint32_t event_mask);

/// @brief create encoder
RotaryEncoder encoder = RotaryEncoder(ENCODER_CLK_GPIO, ENCODER_DT_GPIO,
                                      shared_irq_call_back, cfg_encoder_clk);

/// @brief define the ISR associated with the clock signal of the rotary encoder
/// @param gpio The gpio number connected to the clock signal
/// @param event_mask the IRQ mask, default to GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE
void shared_irq_call_back(uint gpio, uint32_t event_mask)
{
    pr_D1.pulse_us(10);
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

/// @brief ########## implementation classes section ##########
/**
 * @brief test_managed_square_led_model : Example of final implementation of UIModelObject
 *
 */
class test_managed_square_led_model : public UIModelObject
{
protected:
public:
    /// @brief gives a name to the model. Useful to identify the active model via printf on the serial monitor.
    std::string name;
    /// @brief a bool value, visualised by the associated LED widget as on or off.
    bool my_bool_value = false;
    test_managed_square_led_model(std::string name);
    ~test_managed_square_led_model();
    /// @brief the implementation of the pure virtual member.
    /// @param _event the signal send by the controller
    void process_control_event(ControlEvent _event);
};

/**
 * @brief test_managed_square_led_widget : Example of final implementation of w_SquareLed
 *
 */
class test_managed_square_led_widget : public w_SquareLed
{
private:
    test_managed_square_led_model *actual_displayed_model = nullptr;

public:
    test_managed_square_led_widget(test_managed_square_led_model *actual_displayed_model,
                                   UIDisplayDevice *display_screen,
                                   size_t width,
                                   size_t height,
                                   uint8_t widget_anchor_x,
                                   uint8_t widget_anchor_y);
    ~test_managed_square_led_widget();
    void draw_refresh();
};

/**
 * @brief test_switch_button : Example of final implementation of SwitchButton and UIController
 *
 */
class test_switch_button : public SwitchButton, public UIController
{
private:
public:
    test_switch_button(uint gpio, struct_SwitchButtonConfig conf);
    ~test_switch_button();
};

test_switch_button::test_switch_button(uint gpio, struct_SwitchButtonConfig conf)
    : SwitchButton(gpio, conf), UIController()
{
}

/**
 * @brief test_Manager : Example of final implementation of UIObjectManager
 *
 */
class test_Manager : public UIObjectManager
{
private:
public:
    /**
     * @brief Construct a new test_Manager object
     *
     * @param _controller
     */
    test_Manager(UIController *_controller);
    /**
     * @brief Destroy the Test_Manager object
     *
     */
    ~test_Manager();
    /// @brief function that interprets the event send by the controller.
    /// @param _event
    void process_control_event(ControlEvent _event);
};

/**
 * @brief Example of main program of a managed SquareLED widget.
 *
 */
int main()
{
    pr_D4.hi(); // start logic probe 4
    /// main steps:
    stdio_init_all();
    /// 1- create I2C bus hw peripheral
    HW_I2C_Master master = HW_I2C_Master(cfg_i2c);
    /// 2- create the OLED display, clean up the screen and draw the border of the screen
    SSD1306 display = SSD1306(&master, cfg_ssd1306);
    pr_D5.hi();
    display.clear_pixel_buffer();
    display.rect(0, 0, 128, 64);
    display.show();
    pr_D5.lo();
    /// 3- create 3 test_managed_square_led_model  as displayed object for test_managed_square_led_widget
    test_managed_square_led_model test_model_1 = test_managed_square_led_model("TM1");
    test_managed_square_led_model test_model_2 = test_managed_square_led_model("TM2");
    test_managed_square_led_model test_model_3 = test_managed_square_led_model("TM3");
    /// 4- create 3 test_managed_square_led_widget
    test_managed_square_led_widget square_led_1 = test_managed_square_led_widget(&test_model_1, &display, 16, 16, 10, 24);
    test_managed_square_led_widget square_led_2 = test_managed_square_led_widget(&test_model_2, &display, 16, 16, 50, 24);
    test_managed_square_led_widget square_led_3 = test_managed_square_led_widget(&test_model_3, &display, 16, 16, 90, 24);
    /// 5- set led_is_blinking period of the square_led
    square_led_1.set_blink_us(200000);
    square_led_2.set_blink_us(200000);
    square_led_3.set_blink_us(200000);
    /// 6- create a test_switch_button
    test_switch_button central_switch = test_switch_button(CENTRAL_SWITCH_GPIO, cfg_central_switch);
    central_switch.update_current_controlled_object(&test_model_1);
    /// 7- create a test_Manager connected to the rotary encoder.
    test_Manager manager = test_Manager(&encoder);
    /// 8- populate manager with managed objects
    manager.add_managed_model(&test_model_1);
    manager.add_managed_model(&test_model_2);
    manager.add_managed_model(&test_model_3);
    pr_D4.lo(); // end logic probe 4

    while (true)
    /// 9- start infinite loop
    {
        pr_D5.hi(); // start logic probe 5
        /// - get central_switch event and give it to the manager .
        ControlEvent event = central_switch.process_sample_event();
        manager.process_control_event(event);
        /// - refresh the widgets
        square_led_1.draw_refresh();
        square_led_2.draw_refresh();
        square_led_3.draw_refresh();
        pr_D5.lo(); // end logic probe 5
        /// - sleep for 20ms
        sleep_ms(20);
    }

    return 0;
}

void test_managed_square_led_model::process_control_event(ControlEvent _event)
{
    /**
     * @brief only the event INCREMENT and DECREMENT are processed.
     * They both toggle the boolean my_bool_value of the test_managed_square_led_model, and set the change flag in order to trig the effective display.
     *
     */
    switch (_event)
    {
    case ControlEvent::INCREMENT:
    case ControlEvent::DECREMENT:
        my_bool_value = !my_bool_value;
        printf(" %s on_off=%d\n", this->name.c_str(), my_bool_value);
        set_change_flag();
        break;

    default:
        break;
    }
}

test_managed_square_led_widget::test_managed_square_led_widget(test_managed_square_led_model *actual_displayed_model,
                                                               UIDisplayDevice *display_screen,
                                                               size_t width,
                                                               size_t height,
                                                               uint8_t widget_anchor_x,
                                                               uint8_t widget_anchor_y)
    : w_SquareLed(display_screen, width, height, widget_anchor_x, widget_anchor_y)
{
    this->actual_displayed_model = actual_displayed_model;
    this->led_is_blinking = true;
    this->led_is_on = true;
}

test_managed_square_led_widget::~test_managed_square_led_widget()
{
}

/**
 * @brief This function implements a special draw_refresh that takes into account the on/off and led_is_blinking status of the model.
 *
 * It insures that the widget consumes processing time only when its on/off status has changed.
 * The logic of the visualisation :
 *  - if the displayed model has focus, the led is blinking.
 *  - if the model is active, the led stops blinking and follows the value of my_bool_value/
 *  - if the model is waiting, the led stops blinking and represents the value of my_bool_value,
 */
void test_managed_square_led_widget::draw_refresh()
{
    assert(this->actual_displayed_model != nullptr);
    {
        /// main step of the function
        /// - first process the status of the displayed object
        switch (this->actual_displayed_model->get_status())
        {
        case ControlledObjectStatus::HAS_FOCUS:
            this->blink_on();
            break;
        case ControlledObjectStatus::IS_ACTIVE:
            this->blink_off();
            break;
        case ControlledObjectStatus::IS_WAITING:
            this->blink_off();
            // draw_border();
            break;

        default:
            break;
        }
        /// - then widget_blink_refresh() if it is appropriate
        widget_blink_refresh();
        /// - and finally visualise  the change of value in the displayed model
        if (this->actual_displayed_model->has_changed())
        {
            if (this->actual_displayed_model->my_bool_value)
            {
                rect(widget_start_x, widget_start_y, widget_width, widget_height, true, FramebufferColor::WHITE);
            }
            else
            {
                rect(widget_start_x, widget_start_y, widget_width, widget_height, true, FramebufferColor::BLACK);
                draw_border();
            }

            this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
            this->actual_displayed_model->clear_change_flag();
        }
    }
}

test_Manager::test_Manager(UIController *_controller)
    : UIObjectManager()
{
    make_manager_active();
    update_current_controller(_controller);
}

test_managed_square_led_model::test_managed_square_led_model(std::string _name)
    : UIModelObject()
{
    this->name = _name;
}

test_managed_square_led_model::~test_managed_square_led_model()
{
}
/**
 * @brief this member executes the processing of the central switch button/
 *
 * - On the event RELEASED_AFTER_SHORT_TIME, the status IS_ACTIVE toggle between the manager and the model that HAS_FOCUS.
 * - the events INCREMENT or DECREMENT act the focus of the managed models.
 *
 * @param _event
 */
void test_Manager::process_control_event(ControlEvent _event)
{
    switch (_event)
    {
    case ControlEvent::RELEASED_AFTER_SHORT_TIME:
        if (current_active_model == this)
        {
            make_managed_object_active();
            printf("%s is active \n", ((test_managed_square_led_model *)this->current_active_model)->name.c_str());
        }
        else
        {
            make_manager_active();
            printf("manager is active, %s has focus \n", ((test_managed_square_led_model *)this->managed_models[this->value])->name.c_str());
        }
        break;
    case ControlEvent::INCREMENT:
        if (current_active_model == this)
        {
            increment_focus();
            printf("[inc] %s has focus\n", ((test_managed_square_led_model *)this->managed_models[this->value])->name.c_str());
        }
        else
            current_active_model->process_control_event(_event);
        break;
    case ControlEvent::DECREMENT:
        if (current_active_model == this)
        {
            decrement_focus();
            printf("[dec] %s has focus\n", ((test_managed_square_led_model *)this->managed_models[this->value])->name.c_str());
        }
        else
            current_active_model->process_control_event(_event);
        break;
    // case ControlEvent::TIME_OUT:
    //     for (auto &&i : this->managed_models)
    //     {
    //         i->update_status(ControlledObjectStatus::IS_WAITING);
    //     }
    //     break;
    default:
        break;
    }
    /// check time_out
    if (this->get_time_since_last_change() > TIME_OUT_us)
    {
        for (auto &&i : this->managed_models)
        {
            i->update_status(ControlledObjectStatus::IS_WAITING);
        }
    }
}
