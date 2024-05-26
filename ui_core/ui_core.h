#if !defined(UI_CORE_H)
#define UI_CORE_H

#include "pico/stdlib.h"
#include "framebuffer.h"
#include <vector>
#include <list>

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

enum class ControlledObjectStatus
{
    WAITING,
    HAS_FOCUS,
    IS_ACTIVE
};

/// @brief can be useful for keep memory of widget configuration
struct StructWidgetConfig
{
    size_t width{128};
    size_t height{8};
    bool with_border{true};
    bool with_label{true};
    uint8_t anchor_x{0};
    uint8_t anchor_y{0};
    // uint8_t start_x;
    // uint8_t start_y;
    const unsigned char *font{nullptr};
};

class UIController;

class UIDisplayDevice : public Framebuffer
{
private:
public:
    UIDisplayDevice(size_t width, size_t height, FramebufferFormat format = FramebufferFormat::MONO_VLSB, StructFramebufferText txt_cnf = {.font = font_8x8});
    virtual ~UIDisplayDevice();
    virtual void show() = 0;
    virtual void show(Framebuffer *frame, uint8_t anchor_x, uint8_t anchor_y) = 0;
};

class UIModelObject
{
private:
    bool change_flag{true};
    ControlledObjectStatus status{ControlledObjectStatus::WAITING};

protected:
    UIController *current_controller{nullptr};

public:
    UIModelObject(/* args */);
    ~UIModelObject();
    bool has_changed();
    void set_change_flag();
    void clear_change_flag();
    void update_current_controller(UIController *_new_controller);
    void update_status(ControlledObjectStatus _new_status);
    ControlledObjectStatus get_status();
    virtual void process_control_event(ControlEvent _event) = 0;
};

class UIControlledIncrementalValue : public UIModelObject
{
private:
protected:
    int value;
    int min_value;
    int max_value;
    int increment;
    bool is_wrappable;

public:
    UIControlledIncrementalValue(int _min_value = 0, int _max_value = 10, bool _is_wrapable = false, int increment = 1);
    ~UIControlledIncrementalValue();
    virtual void increment_value();
    virtual void decrement_value();
    void set_clipped_value(int _new_value);
    int get_value();
};

class UIObjectManager : public UIControlledIncrementalValue
{
private:
    std::vector<UIModelObject *> managed_objects;

public:
    UIObjectManager(/* args */);
    ~UIObjectManager();
    void add_managed_object(UIModelObject *_new_object);
    void increment_focus();
    void decrement_focus();
    void make_managed_object_active();
};

class UIController
{
protected:
    UIModelObject *current_controlled_object{nullptr};

public:
    UIController(/* args */);
    ~UIController();
    void update_current_controlled_object(UIModelObject *_new_controlled_object);
};

class UIWidget : public Framebuffer
{
private:
    UIDisplayDevice *display_screen{nullptr};
    bool widget_with_border{true};
    uint8_t widget_anchor_x;
    uint8_t widget_anchor_y;
    std::vector<UIWidget *> widgets;

protected:
    size_t widget_width{128};
    size_t widget_height{8};
    uint8_t widget_start_x;
    uint8_t widget_start_y;
    uint8_t widget_border_width;
    UIModelObject *displayed_object{nullptr};
    void draw_border();
    virtual void draw() = 0;

public:
    static FramebufferColor blinking_us(uint32_t _blink_period);
    UIWidget(UIDisplayDevice *_display_screen, size_t _frame_width, size_t _frame_height,
             uint8_t _widget_anchor_x, uint8_t _widget_anchor_y, bool _widget_with_border, uint8_t _widget_border_width = 1,
             FramebufferFormat _framebuffer_format = FramebufferFormat::MONO_VLSB, StructFramebufferText _framebuffer_txt_cnf = {.font = font_8x8});
    ~UIWidget();
    void set_displayed_object(UIModelObject *_new_displayed_object);
    void set_display_screen(UIDisplayDevice *_new_display_device);
    void add_widget(UIWidget *_sub_widget);
    virtual void refresh();
    // virtual void draw_active() = 0; // TODO  a verifier si utile pour les instances de widget
    // virtual void draw_focus() = 0; // TODO  a verifier si utile pour les instances de widget
};

#endif // UI_CORE_H
