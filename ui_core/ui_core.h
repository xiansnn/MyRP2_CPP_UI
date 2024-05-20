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

class UIController;

class UIDisplayDevice : public Framebuffer
{
private:
public:
    UIDisplayDevice(size_t width, size_t height, Framebuffer_format format = Framebuffer_format::MONO_VLSB, config_framebuffer_text_t txt_cnf = {.font = font_8x8});
    virtual ~UIDisplayDevice();
    virtual void show() = 0;
    virtual void show(Framebuffer *frame, uint8_t anchor_x, uint8_t anchor_y) = 0;
};

class UIModelObject
{
private:
    bool change_flag{true};
    ControlledObjectStatus status{ControlledObjectStatus::WAITING};
    UIController *current_controller{nullptr};

public:
    UIModelObject(/* args */);
    ~UIModelObject();
    bool has_changed();
    void set_change_flag();
    void clear_change_flag();
    void update_current_controller(UIController *_new_controller);
    void update_status(ControlledObjectStatus _new_status);
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
    UIControlledIncrementalValue(int _min_value = 0, int _max_value = 10, bool wrap = false, int increment = 1);
    ~UIControlledIncrementalValue();
    virtual void increment_value();
    virtual void decrement_value();
    void set_clipped_value(int _new_value);
};

class UIObjectManager : public UIControlledIncrementalValue
{
private:
    std::vector<UIModelObject*> managed_objects;
public:
    UIObjectManager(/* args */);
    ~UIObjectManager();
    void add_managed_object(UIModelObject* _new_object);
    void increment_focus();
    void decrement_focus();
    void make_managed_object_active();

};

class UIController
{
private:
    UIModelObject *current_controlled_object{nullptr};

public:
    UIController(/* args */);
    ~UIController();
    void update_current_controlled_object(UIModelObject *_new_controlled_object);
};

#endif // UI_CORE_H
