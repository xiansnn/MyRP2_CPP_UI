#include "ui_core.h"

UIDisplayDevice::UIDisplayDevice(size_t width, size_t height, Framebuffer_format format, config_framebuffer_text_t txt_cnf) 
                                             : Framebuffer(width, height, format, txt_cnf)
{
}

UIDisplayDevice::~UIDisplayDevice()
{
}
