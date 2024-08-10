/**
 * @file test_widget_on_serial_monitor.cpp
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief This is the companion file of test_ui_core program
 * @version 0.1
 * @date 2024-05-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "t_widget_on_serial_monitor.h"
#include <sstream>

std::map<ControlledObjectStatus, std::string> status_to_string{
    {ControlledObjectStatus::IS_WAITING, "IS_WAITING"},
    {ControlledObjectStatus::HAS_FOCUS, "HAS_FOCUS"},
    {ControlledObjectStatus::IS_ACTIVE, "IS_ACTIVE"}};

test_CursorWidgetWithIncrementalValue::test_CursorWidgetWithIncrementalValue(test_IncrementalValue *_actual_displayed_object)
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
    this->set_displayed_model(_actual_displayed_object);
    this->actual_displayed_object = _actual_displayed_object;

    char_position_slope = (max_line_width - 1.) / (actual_displayed_object->get_max_value() - actual_displayed_object->get_min_value());
    char_position_offset = 1 - char_position_slope * actual_displayed_object->get_min_value();
}

test_CursorWidgetWithIncrementalValue::~test_CursorWidgetWithIncrementalValue()
{
}

void test_CursorWidgetWithIncrementalValue::draw_refresh()
{
    if (this->actual_displayed_object->has_changed())
    {
        /// draw()
        switch (actual_displayed_object->get_status())
        {
        case ControlledObjectStatus::IS_WAITING:
            printf("[%s] %s with value=%d\n",
                   actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
            break;
        case ControlledObjectStatus::HAS_FOCUS:
            printf("[%s] %s with value=%d\n",
                   actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
            break;
        case ControlledObjectStatus::IS_ACTIVE:
            printf("[%s] %s with value= %d %*c\n",
                   actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value(), value_to_char_position(), '|');
            break;
        default:
            break;
        }
        /// end draw()
        this->actual_displayed_object->clear_change_flag();
    }
}

int test_CursorWidgetWithIncrementalValue::value_to_char_position()
{
    return (char_position_slope * actual_displayed_object->get_value() + char_position_offset);
}

void test_CursorWidgetWithIncrementalValue::draw()
{
    // switch (actual_displayed_object->get_status())
    // {
    // case ControlledObjectStatus::IS_WAITING:
    //     printf("[%s] %s with value=%d\n",
    //            actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
    //     break;
    // case ControlledObjectStatus::HAS_FOCUS:
    //     printf("[%s] %s with value=%d\n",
    //            actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value());
    //     break;
    // case ControlledObjectStatus::IS_ACTIVE:
    //     printf("[%s] %s with value= %d %*c\n",
    //            actual_displayed_object->get_name().c_str(), status_to_string[actual_displayed_object->get_status()].c_str(), actual_displayed_object->get_value(), value_to_char_position(), '|');
    //     break;
    // default:
    //     break;
    // }
}

void test_ObjectManagerWidget::draw()
{
    // std::string text = "manager " + status_to_string[actual_displayed_object->get_status()] + " with value=" + std::to_string(actual_displayed_object->get_value()) + "\n";
    // printf(text.c_str());
}

test_ObjectManagerWidget::test_ObjectManagerWidget(test_Manager *_manager)
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
    this->set_displayed_model(_manager);
    this->actual_displayed_object = _manager;
}

test_ObjectManagerWidget::~test_ObjectManagerWidget()
{
}

void test_ObjectManagerWidget::draw_refresh()
{
    if (this->actual_displayed_object->has_changed())
    { /// draw()
        std::string text = "manager " + status_to_string[actual_displayed_object->get_status()] + " with value=" + std::to_string(actual_displayed_object->get_value()) + "\n";
        printf(text.c_str());
        /// end draw()
        this->actual_displayed_object->clear_change_flag();
    }
}

void test_SetOfWidget::draw_refresh()
{
    /// First: Scan all contained sub-widgets if any and call draw_refresh() member function of each of them.
    if (widgets.size() != 0)
    {
        for (auto &&w : widgets)
            w->draw_refresh();
    }

    /// Then: apply draw_refresh() on the containing widget if any changes require a screen redraw
    ///       and finally : clear model change flag
    if ((this->displayed_model != nullptr) and (this->displayed_model->has_changed()))
    {
        ///  draw();  nothing to draw for this class
        if (widget_with_border)
            draw_border();
        this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
        this->displayed_model->clear_change_flag();
    }
};

test_SetOfWidget::test_SetOfWidget()
    : UIWidget(nullptr, 128, 8, 0, 0, false)
{
}

test_SetOfWidget::~test_SetOfWidget()
{
}
