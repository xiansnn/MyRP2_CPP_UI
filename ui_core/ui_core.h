#if !defined(UI_CORE_H)
#define UI_CORE_H

#include "pico/stdlib.h"
#include "framebuffer.h"
#include <vector>
#include <list>

class AbstractDisplayDevice : public Framebuffer
{
private:
public:
    AbstractDisplayDevice(size_t width, size_t height, Framebuffer_format format = Framebuffer_format::MONO_VLSB, config_framebuffer_text_t txt_cnf = {.font = font_8x8});
    virtual ~AbstractDisplayDevice();
    virtual void show() = 0;
    virtual void show(Framebuffer *frame, uint8_t anchor_x, uint8_t anchor_y) = 0;
};



#endif // UI_CORE_H
