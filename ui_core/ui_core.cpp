#include "ui_core.h"

UIDisplayDevice::UIDisplayDevice(size_t width, size_t height, Framebuffer_format format, config_framebuffer_text_t txt_cnf)
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
    if (this->current_controller != _new_controller)
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

void UIModelObject::set_change_flag()
{
    this->change_flag = true;
}

UIControlledIncrementalValue::UIControlledIncrementalValue(int _min_value, int _max_value, bool _is_wrapable, int _increment)
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

UIObjectManager::UIObjectManager()
    : UIControlledIncrementalValue(0, 0, true, 1)
{
}

UIObjectManager::~UIObjectManager()
{
}

void UIObjectManager::add_managed_object(UIModelObject *_new_object)
{
    this->managed_objects.push_back(_new_object);
    this->max_value = managed_objects.size() - 1;
}

void UIObjectManager::increment_focus()
{
    int previous_value = value;
    this->increment_value();
    if (value != previous_value)
    {
        this->managed_objects[previous_value]->update_status(ControlledObjectStatus::WAITING);
        this->managed_objects[this->value]->update_status(ControlledObjectStatus::HAS_FOCUS);
    }
}

void UIObjectManager::decrement_focus()
{
    int previous_value = value;
    this->decrement_value();
    if (value != previous_value)
    {
        this->managed_objects[previous_value]->update_status(ControlledObjectStatus::WAITING);
        this->managed_objects[this->value]->update_status(ControlledObjectStatus::HAS_FOCUS);
    }
}

void UIObjectManager::make_managed_object_active()
{
    this->managed_objects[this->value]->update_status(ControlledObjectStatus::IS_ACTIVE);
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
