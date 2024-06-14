/**
 * @file ui_core.h
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if !defined(UI_CORE_H)
#define UI_CORE_H

#include "pico/stdlib.h"
#include "framebuffer.h"
#include <vector>
#include <map>
#include <string>

/**
 * @brief The list of predefined event that a Controller can send to the controlled object, leaving it the responsibility
 * to act as required by its specification.
 *
 */
enum class ControlEvent
{
    NOOP,
    PUSH,
    DOUBLE_PUSH, // TODO find a way to do "DOUBLE_PUSH"
    LONG_PUSH,
    RELEASED_AFTER_LONG_TIME,
    RELEASED_AFTER_SHORT_TIME,
    INCREMENT,
    DECREMENT,
    TIME_OUT // TODO find a way to do "TIME_OUT"
};

/**
 * @brief The list of status that a model can have.
 *
 */
enum class ControlledObjectStatus
{
    IS_WAITING, // nothing to do
    HAS_FOCUS, // the widget or object manager is pointing to this model
    IS_ACTIVE // the user has selected (clicked) on this model. CtrolEvent are then passed to this model in order to be processed.
};

/**
 * @brief Can be useful for keep memory of widget configuration and share it.
 *  The structure reflects the memebers of UIWidget class
 *
 */
struct StructWidgetConfig
{
    size_t width{128};
    size_t height{8};
    bool with_border{true};
    bool with_label{true};
    uint8_t anchor_x{0};
    uint8_t anchor_y{0};
    const unsigned char *font{nullptr};
};

class UIController;

/**
 * @brief This is the abstract class to handle all generic behavior of physical display devices (e.g. OLED screen SSD1306).
 * It derived from Framebuffer. This allows to draw text and graphics directly into the display framebuffer 
 * thanks to Framebuffet class text and graphic primitives indepently from any kind of widget
 *
 */
class UIDisplayDevice : public Framebuffer
{
private:
public:
    /**
     * @brief Construct a new UIDisplayDevice object
     *
     * @param width The width of physical screen, in pixel.
     * @param height The height of physical screen, in pixel.
     * @param format The framebuffer format ... see Framebuffer class FramebufferFormat enumeration
     * @param txt_cnf A structure of datga that reflect the framebuffer member related to text primitives
     */
    UIDisplayDevice(size_t width, size_t height, FramebufferFormat format = FramebufferFormat::MONO_VLSB, StructFramebufferText txt_cnf = {.font = font_8x8});
    /**
     * @brief Destroy the UIDisplayDevice object
     * 
     */
    virtual ~UIDisplayDevice();
    /**
     * @brief This is an pure virtual member function that all final derived class must implement.
     * It transfers the framebuffer buffer to the entire display screen buffer.
     *
     */
    virtual void show() = 0;
    /**
     * @brief This is an pure virtual member function that all final derived class must implement.
     * It transfers the framebuffer buffer to the a part of display screen buffer starting at the (anchor_x, anchor_y) coordinates of the screen , expressed in pixel.
     *
     * @param frame a pointer to the frame to be displayed
     * @param anchor_x the x (horizontal)starting position of the frame within the display screen, (in pixel)
     * @param anchor_y the y (vertical) starting position of the frame within the display screen, (in pixel)
     */
    virtual void show(Framebuffer *frame, uint8_t anchor_x, uint8_t anchor_y) = 0;
};

/**
 * @brief This is the Model abstract class of Model_View_Control design pattern.
 * It handles change_flag, a semaphore used to indicate that a screen refresh is required.
 * the controller or any other entities that modify the model must set the change_flag 
 * and the widget in charge of its screen representation must clear the chang_flag
 *
 */
class UIModelObject
{
private:
    /**
     * @brief The semaphore used to trigger the actual drawing of the widget on the screen.
     *
     */
    bool change_flag{true};
    /**
     * @brief The status of the model, indicating if it is waiting, active or just ahs focus (pointed by the object manager)
     *
     */
    ControlledObjectStatus status{ControlledObjectStatus::IS_WAITING};
    /**
     * @brief A point er to the controller of this model.
     *
     */
    UIController *current_controller{nullptr};

protected:
public:
    /**
     * @brief Construct the UIModelObject object
     *
     */
    UIModelObject(/* args */);
    /**
     * @brief Destroy the UIModelObject object
     * 
     */
    ~UIModelObject();
    /**
     * @brief
     *
     * @return true means the redraw is required
     * @return false means the model is unchanged
     */
    bool has_changed();
    /**
     * @brief Set the change flag object to true
     *
     */
    void set_change_flag();
    /**
     * @brief Set the change flag object to false
     *
     */
    void clear_change_flag();
    /**
     * @brief Propose a _new_status for the model. If this _new_status is different from the present one, 
     * then the change is effective and the change_flag is set to true.
     *
     * @param _new_status
     */
    void update_status(ControlledObjectStatus _new_status);
    /**
     * @brief 
     *
     * @param _new_controller
     */
    void update_current_controller(UIController *_new_controller);
    /**
     * @brief Get the status object
     *
     * @return ControlledObjectStatus
     */
    ControlledObjectStatus get_status();
    /**
     * @brief
     *
     * @param _event
     */
    virtual void process_control_event(ControlEvent _event) = 0;
};

/**
 * @brief
 *
 */
class UIControlledIncrementalValue : public UIModelObject
{
private:
protected:
    /**
     * @brief
     *
     */
    int value;
    /**
     * @brief
     *
     */
    int max_value;
    /**
     * @brief 
     * 
     */
    int min_value;
    /**
     * @brief
     *
     */
    int increment;
    /**
     * @brief
     *
     */
    bool is_wrappable;

public:
    /**
     * @brief Construct a new UIControlledIncrementalValue object
     *
     * @param _min_value
     * @param _max_value
     * @param _is_wrapable
     * @param increment
     */
    UIControlledIncrementalValue(int _min_value = 0, int _max_value = 10, bool _is_wrapable = false, int increment = 1);
    /**
     * @brief Destroy the UIControlledIncrementalValue object
     * 
     */
    ~UIControlledIncrementalValue();
    /**
     * @brief 
     * 
     */
    virtual void increment_value();
    /**
     * @brief 
     * 
     */
    virtual void decrement_value();
    /**
     * @brief Set the clipped value object
     * 
     * @param _new_value 
     */
    void set_clipped_value(int _new_value);
    /**
     * @brief Get the value object
     * 
     * @return int 
     */
    int get_value();
    /**
     * @brief Get the min value object
     * 
     * @return int 
     */
    int get_min_value();
    /**
     * @brief Get the max value object
     * 
     * @return int 
     */
    int get_max_value();
};

/**
 * @brief 
 * 
 */
class UIObjectManager : public UIControlledIncrementalValue
{
protected:
    /**
     * @brief 
     * 
     */
    std::vector<UIModelObject *> managed_models;
    /**
     * @brief 
     * 
     */
    UIModelObject *current_active_model;
    /**
     * @brief 
     * 
     */
    void make_managed_object_active();
    /**
     * @brief 
     * 
     */
    void make_manager_active();
    /**
     * @brief 
     * 
     */
    virtual void increment_focus();
    /**
     * @brief 
     * 
     */
    virtual void decrement_focus();

public:
    /**
     * @brief 
     * 
     */
    UIObjectManager(/* args */);
    /**
     * @brief Destroy the UIObjectManager object
     * 
     */
    ~UIObjectManager();
    /**
     * @brief 
     * 
     * @param _new_model 
     */
    void add_managed_model(UIModelObject *_new_model);
};

/**
 * @brief 
 * 
 */
class UIController
{
protected:
    /**
     * @brief 
     * 
     */
    UIModelObject *current_controlled_object{nullptr};

public:
/**
 * @brief 
 * 
 */
    UIController(/* args */);
    /**
     * @brief Destroy the UIController object
     * 
     */
    ~UIController();
    /**
     * @brief 
     * 
     * @param _new_controlled_object 
     */
    void update_current_controlled_object(UIModelObject *_new_controlled_object);
};

/**
 * @brief 
 * 
 */
class UIWidget : public Framebuffer
{
private:
    /**
     * @brief 
     * 
     */
    UIDisplayDevice *display_screen{nullptr};
    /**
     * @brief 
     * 
     */
    UIModelObject * displayed_model{nullptr};
    /**
     * @brief 
     * 
     */
    bool widget_with_border{true};
    /**
     * @brief 
     * 
     */
    uint8_t widget_anchor_x;
    /**
     * @brief 
     * 
     */
    uint8_t widget_anchor_y;
    /**
     * @brief 
     * 
     */

protected:
    /**
     * @brief 
     * 
     */
    std::vector<UIWidget *> widgets;
    /**
     * @brief 
     * 
     */
    size_t widget_width{128};
    /**
     * @brief 
     * 
     */
    size_t widget_height{8};
    /**
     * @brief 
     * 
     */
    uint8_t widget_start_x;
    /**
     * @brief 
     * 
     */
    uint8_t widget_start_y;
    /**
     * @brief 
     * 
     */
    uint8_t widget_border_width;
    /**
     * @brief Set the displayed model object
     * 
     * @param _new_displayed_model 
     */
    virtual void set_displayed_model(UIModelObject *_new_displayed_model);
    /**
     * @brief Set the display screen object
     * 
     * @param _new_display_device 
     */
    void set_display_screen(UIDisplayDevice *_new_display_device);
    /**
     * @brief 
     * 
     */
    void draw_border();
    /**
     * @brief 
     * 
     */
    virtual void draw() = 0;

public:
    /**
     * @brief 
     * 
     * @param _blink_period 
     * @return FramebufferColor 
     */
    static FramebufferColor blinking_us(uint32_t _blink_period);
    /**
     * @brief Construct a new UIWidget object
     * 
     * @param _display_screen 
     * @param _frame_width 
     * @param _frame_height 
     * @param _widget_anchor_x 
     * @param _widget_anchor_y 
     * @param _widget_with_border 
     * @param _widget_border_width 
     * @param _framebuffer_format 
     * @param _framebuffer_txt_cnf 
     */
    UIWidget(UIDisplayDevice *_display_screen, size_t _frame_width, size_t _frame_height,
             uint8_t _widget_anchor_x, uint8_t _widget_anchor_y, bool _widget_with_border, uint8_t _widget_border_width = 1,
             FramebufferFormat _framebuffer_format = FramebufferFormat::MONO_VLSB, StructFramebufferText _framebuffer_txt_cnf = {.font = font_8x8});
    /**
     * @brief Destroy the UIWidget object
     * 
     */
    ~UIWidget();
    /**
     * @brief 
     * 
     * @param _sub_widget 
     */
    void add_widget(UIWidget *_sub_widget);
    /**
     * @brief WARNING : this function can be redefined. When several widget display one Model, only le last one must clear_change_flag()
     * 
     */
    virtual void refresh();
};

#endif // UI_CORE_H
