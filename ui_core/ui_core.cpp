#include "ui_core.h"

AbstractDisplayDevice::AbstractDisplayDevice(size_t width, size_t height, Framebuffer_format format, config_framebuffer_text_t txt_cnf) 
                                             : Framebuffer(width, height, format, txt_cnf)
{
}

AbstractDisplayDevice::~AbstractDisplayDevice()
{
}
