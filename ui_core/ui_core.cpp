#include "ui_core.h"

UIDisplayDevice::UIDisplayDevice(size_t width, size_t height, FramebufferFormat format, StructFramebufferText txt_cnf)
    : Framebuffer(width, height, format, txt_cnf)
{
}

UIDisplayDevice::~UIDisplayDevice()
{
}

UIModelObject::UIModelObject()
{
}

UIModelObject::~UIModelObject()
{
}

bool UIModelObject::has_changed()
{
    return this->change_flag;
}

void UIModelObject::clear_change_flag()
{
    this->change_flag = false;
}

void UIModelObject::update_current_controller(UIController *_new_controller)
{
    if (this->current_controller != _new_controller) // to avoid deadlock with recursive callback
    {
        this->current_controller = _new_controller;
        this->current_controller->update_current_controlled_object(this);
    }
}

void UIModelObject::update_status(ControlledObjectStatus _new_status)
{
    if (this->status != _new_status)
    {
        this->status = _new_status;
        set_change_flag();
    }
}

ControlledObjectStatus UIModelObject::get_status()
{
    return this->status;
}

void UIModelObject::set_change_flag()
{
    this->change_flag = true;
}

UIControlledIncrementalValue::UIControlledIncrementalValue(int _min_value, int _max_value, bool _is_wrapable, int _increment)
    : UIModelObject()
{
    this->value = 0;
    this->min_value = _min_value;
    this->max_value = _max_value;
    this->is_wrappable = _is_wrapable;
    this->increment = _increment;
}

UIControlledIncrementalValue::~UIControlledIncrementalValue()
{
}

void UIControlledIncrementalValue::increment_value()
{
    int previous_value = value;
    value += increment;
    if (value > max_value)
        value = (is_wrappable) ? min_value : max_value;
    if (value != previous_value)
        set_change_flag();
}

void UIControlledIncrementalValue::decrement_value()
{
    int previous_value = value;
    value -= increment;
    if (value < min_value)
        value = (is_wrappable) ? max_value : min_value;
    if (value != previous_value)
        set_change_flag();
}

void UIControlledIncrementalValue::set_clipped_value(int _new_value)
{
    int previous_value = value;
    value = std::min(max_value, std::max(min_value, _new_value));
    if (value != previous_value)
        set_change_flag();
}

int UIControlledIncrementalValue::get_value()
{
    return this->value;
}

int UIControlledIncrementalValue::get_min_value()
{
    return min_value;
}

int UIControlledIncrementalValue::get_max_value()
{
    return max_value;
}

UIObjectManager::UIObjectManager()
    : UIControlledIncrementalValue(0, 0, true, 1)
{
    update_status(ControlledObjectStatus::IS_ACTIVE);
    current_active_model = this;
}

UIObjectManager::~UIObjectManager()
{
}

void UIObjectManager::add_managed_model(UIModelObject *_new_model)
{
    this->managed_models.push_back(_new_model);
    this->max_value = managed_models.size() - 1;
}

void UIObjectManager::increment_focus()
{
    int previous_value = value;
    this->increment_value();
    if (value != previous_value) // action takes place only when the value changes
    {
        this->managed_models[previous_value]->update_status(ControlledObjectStatus::IS_WAITING);
        this->managed_models[this->value]->update_status(ControlledObjectStatus::HAS_FOCUS);
    }
}

void UIObjectManager::decrement_focus()
{
    int previous_value = value;
    this->decrement_value();
    if (value != previous_value) // action takes place only when the value changes
    {
        this->managed_models[previous_value]->update_status(ControlledObjectStatus::IS_WAITING);
        this->managed_models[this->value]->update_status(ControlledObjectStatus::HAS_FOCUS);
    }
}

void UIObjectManager::make_managed_object_active()
{
    this->current_active_model = this->managed_models[this->value];
    this->current_active_model->update_status(ControlledObjectStatus::IS_ACTIVE);
    update_status(ControlledObjectStatus::IS_WAITING);
}

void UIObjectManager::make_manager_active()
{
    if (managed_models.size() != 0)
    {
        current_active_model->update_status(ControlledObjectStatus::HAS_FOCUS);
        for (auto &&model : managed_models)
            model->set_change_flag();
    }
    current_active_model = this;
    update_status(ControlledObjectStatus::IS_ACTIVE);
}

UIController::UIController()
{
}

UIController::~UIController()
{
}

void UIController::update_current_controlled_object(UIModelObject *_new_controlled_object)
{
    if (this->current_controlled_object != _new_controlled_object)
    {
        this->current_controlled_object = _new_controlled_object;
        this->current_controlled_object->update_current_controller(this);
    }
}

void UIWidget::draw_border()
{
    rect(0, 0, frame_width, frame_height);
}

FramebufferColor UIWidget::blinking_us(uint32_t _blink_period)
{
    return ((time_us_32() / _blink_period) % 2) ? FramebufferColor::WHITE : FramebufferColor::BLACK;
}

UIWidget::UIWidget(UIDisplayDevice *_display_screen, size_t _frame_width, size_t _frame_height, uint8_t _widget_anchor_x, uint8_t _widget_anchor_y, bool _widget_with_border,
                   uint8_t _widget_border_width, FramebufferFormat _framebuffer_format, StructFramebufferText _framebuffer_txt_cnf)
    : Framebuffer(_frame_width, _frame_height, _framebuffer_format, _framebuffer_txt_cnf)
{
    this->display_screen = _display_screen;
    this->widget_anchor_x = _widget_anchor_x;
    this->widget_anchor_y = _widget_anchor_y;
    this->widget_with_border = _widget_with_border;
    this->widget_border_width = (widget_with_border) ? _widget_border_width : 0;

    widget_start_x = widget_border_width;
    widget_start_y = widget_border_width;
    widget_width = frame_width - 2 * widget_border_width;
    widget_height = frame_height - 2 * widget_border_width;
}

UIWidget::~UIWidget()
{
}

void UIWidget::set_displayed_model(UIModelObject *_new_displayed_model)
{
    this->displayed_model = _new_displayed_model;
}

void UIWidget::set_display_screen(UIDisplayDevice *_new_display_device)
{
    this->display_screen = _new_display_device;
}

void UIWidget::add_widget(UIWidget *_sub_widget)
{
    this->widgets.push_back(_sub_widget);
}

void UIWidget::refresh()
{
    /**
     * @brief First: Scan all contained sub-widgets if any and call refresh() member function of each of them.
     * 
     */
    if (widgets.size() != 0)
    {
        for (auto &&w : widgets)
            w->refresh();
    }
    /**
     * @brief Then: apply refresh() on the containing widget if any changes require a screen redraw
     * and finally : clear model change flag
     * 
     */
    if ((this->displayed_model != nullptr) and (this->displayed_model->has_changed()))
    {
        draw();
        if (widget_with_border)
            draw_border();
        this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
        this->displayed_model->clear_change_flag(); 
    }
}
