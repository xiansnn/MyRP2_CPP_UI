/**
 * @file framebuffer.h
 * @author xiansnn (xiansnn@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-30
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if !defined(FRAMEBUFFER_H)
#define FRAMEBUFFER_H

#include <string>

#define SSD1306_ASCII_FULL
#define FONT_WIDTH 0
#define FONT_HEIGHT 1
#include "5x8_font.h"
#include "8x8_font.h"
#include "12x16_font.h"
#include "16x32_font.h"
#define BACKSPACE '\b'
#define HORIZONTAL_TAB '\t'
#define LINE_FEED '\n'
#define VERTICAL_TAB '\v'
#define FORM_FEED '\f'
#define CARRIAGE_RETURN '\r'

enum class FramebufferFormat
{
    MONO_VLSB,
    MONO_HLSB,
    MONO_HMSB,
    RGB565
};

enum class FramebufferColor
{
    BLACK = 0,
    WHITE = 1
};

struct StructFramebufferText
{
    const unsigned char *font{nullptr};
    uint8_t tab_size{2};
    FramebufferColor fg_color{FramebufferColor::WHITE};
    FramebufferColor bg_color{FramebufferColor::BLACK};
    bool wrap{true};
    bool auto_next_char{true};
};

class Framebuffer
{
private:
    size_t pixel_buffer_size;
    size_t text_buffer_size;
    FramebufferFormat frame_format;
    uint8_t current_char_line{0};
    uint8_t current_char_column{0};

    void ellipse(uint8_t x_center, uint8_t y_center, uint8_t x_radius, uint8_t y_radius, bool fill, uint8_t quadrant, FramebufferColor c);
    void drawChar(const unsigned char *font, char c, uint8_t anchor_x, uint8_t anchor_y);
    void drawChar(char c, uint8_t char_column, uint8_t char_line);
    void pixel(int x, int y, FramebufferColor c = FramebufferColor::WHITE);
    void clear_line();

public:
    uint8_t *pixel_buffer;
    char *text_buffer;
    StructFramebufferText frame_text_config{};
    uint8_t frame_width;
    uint8_t frame_height;
    uint8_t max_line{0};
    uint8_t max_column{0};

    Framebuffer(size_t width, size_t height,
                FramebufferFormat format = FramebufferFormat::MONO_VLSB, StructFramebufferText txt_cnf = {.font = font_8x8}); // TODO inverser ordre format et txt_cnf
    ~Framebuffer();

    /* graphic primitives*/
    void clear_pixel_buffer();
    void fill(FramebufferColor c);
    void hline(uint8_t x, uint8_t y, size_t w, FramebufferColor c = FramebufferColor::WHITE);
    void vline(uint8_t x, uint8_t y, size_t h, FramebufferColor c = FramebufferColor::WHITE);
    void line(int x1, int y1, int x2, int y2, FramebufferColor c = FramebufferColor::WHITE);
    void rect(uint8_t x, uint8_t y, size_t w, size_t h, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);
    void circle(int radius, int x_center, int y_center, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);

    /* textual primitives*/
    void clear_text_buffer();
    void set_text_config(StructFramebufferText device_config);
    void set_font(const unsigned char *font);
    void print_text();
    void print_text(const char *c_str);
    void print_char(char c);
    void next_line();
    void next_char();
};

#endif // FRAMEBUFFER_H