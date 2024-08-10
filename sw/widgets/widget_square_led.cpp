#include "widget_square_led.h"

w_SquareLed::w_SquareLed(UIDisplayDevice *display_screen,
                         size_t width, size_t height,
                         uint8_t widget_anchor_x, uint8_t widget_anchor_y,
                         FramebufferColor color, FramebufferFormat framebuffer_format)
    : UIWidget(display_screen, width, height, widget_anchor_x, widget_anchor_y, true, 1, framebuffer_format)
{
}

w_SquareLed::~w_SquareLed()
{
}

void w_SquareLed::light_on()
{
    this->lit = true;
}

void w_SquareLed::light_off()
{
    this->lit = false;
}

void w_SquareLed::set_blink(uint32_t _blink_period)
{
    this->blinking = true;
    this->blink_period = _blink_period;
}

void w_SquareLed::blink_off()
{
    this->blinking = false;
}

void w_SquareLed::draw_refresh() // TODO revoir un draw_refresh et un draw optimisant squareled et basé sur un model approprié

{
    if ((this->displayed_model != nullptr) and (this->displayed_model->has_changed()))
    { 
        /// draw()
        if (this->lit)
        {
            if (this->blinking)
            {
                rect(0, 0, frame_width, frame_height, true, blinking_us(this->blink_period));
                // no need to call draw_border() as long as widget_with_border is true.
            }
            else
            {
                rect(0, 0, frame_width, frame_height, true, FramebufferColor::WHITE);
            }
        }
        else
        {
            rect(0, 0, frame_width, frame_height, true, FramebufferColor::BLACK);
            // no need to call draw_border() as long as widget_with_border is true.
        }
        /// end draw()
        if (widget_with_border)
            draw_border();
        this->display_screen->show(this, this->widget_anchor_x, this->widget_anchor_y);
        this->displayed_model->clear_change_flag();
    }
}
