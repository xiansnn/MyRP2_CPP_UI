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

/**
 * @brief Data structure that holds all configuration parameters used by textual primitives
 */
struct StructFramebufferText
{
    /**
     * @brief The font used. Current font are defined according to IBM CP437. The font files are derived from https://github.com/Harbys/pico-ssd1306 works.
     * They come is size 5x8, 8x8, 12x16 and 16x32.
     */
    const unsigned char *font{nullptr}; 
    /**
     * @brief  The number of space that ASCII character HT (aka TAB , "\t", 0x9) generates, default to 2
     */
    uint8_t tab_size{2};
    /**
     * @brief The foreground color, default to WHITE
     */
    FramebufferColor fg_color{FramebufferColor::WHITE};  
    /**
     * @brief The background color, defaul to BLACK
     */
    FramebufferColor bg_color{FramebufferColor::BLACK}; 
    /**
     * @brief Wrap flag : if true, text wrap to the next line when end of line is reached.
     */
    bool wrap{true};
    /**
     * @brief auto_next_char flag : if true each char steps one position after being written.
     */
    bool auto_next_char{true};
};

/**
 * @brief Framebuffer is the basic framework to handle texts and graphics on a digital display.
 *
 * This framebuffer implementation is derived from the mycropython API and more explanations can be found
 * there https://docs.micropython.org/en/latest/library/framebuf.html#module-framebuf.
 *
 * The current implementation supports only MONO_VLSB frame_format (monochrome display with vertically addressed pixel LSB being on top)
 *  and tested with OLED SSD1306.
 * 
 * The core of framebuffer is the pixel_buffer, a memory space that contains pixel values. This pixel_buffer is computed and initialized by the framebuffer constructor.
 * 
 * Optionnally, when framebuffer contains text, a text_buffer that contains characters is used. It is created ans initialized by
 *  init_text_buffer member.
 * The configuration of this buffer is defined by StructFramebufferText.
 * 
 *
 */
class Framebuffer
{
private:
    size_t pixel_buffer_size;
    size_t text_buffer_size;
    FramebufferFormat frame_format;
    uint8_t current_char_line{0};
    uint8_t current_char_column{0};
    StructFramebufferText frame_text_config{};

    void ellipse(uint8_t x_center, uint8_t y_center, uint8_t x_radius, uint8_t y_radius, bool fill, uint8_t quadrant, FramebufferColor c);
    void drawChar(const unsigned char *font, char c, uint8_t anchor_x, uint8_t anchor_y);
    void drawChar(char c, uint8_t char_column, uint8_t char_line);
    void pixel(int x, int y, FramebufferColor c = FramebufferColor::WHITE);
    void clear_line();
protected:
public:
    uint8_t *pixel_buffer;
    char *text_buffer;
    uint8_t frame_width;
    uint8_t frame_height;
    uint8_t max_line{0};
    uint8_t max_column{0};

    /**
     * @brief Construct a new Framebuffer object
     * 
     * @param frame_width   The number of pixel along the width of the frame. 
     * Usually defined by "x" starting at "0" on top upleft corner, running to the left and ending at frame_width-1 position.
     * @param frame_height   The number of pixel along the height of the frame. 
     * Usually defined by "y" starting at "0" on top upleft corner, running downward and ending at frame_height-1 position.
     * @param frame_format   The way the memory byte are translated by the dispaly driver device.
     */
    Framebuffer(size_t frame_width,
                size_t frame_height,
                FramebufferFormat frame_format = FramebufferFormat::MONO_VLSB);
    /**
     * @brief Destroy the Framebuffer object
     */
    ~Framebuffer();

    /**  graphic primitives*/
    void clear_pixel_buffer();
    void fill(FramebufferColor c);
    void hline(uint8_t x, uint8_t y, size_t w, FramebufferColor c = FramebufferColor::WHITE);
    void vline(uint8_t x, uint8_t y, size_t h, FramebufferColor c = FramebufferColor::WHITE);
    void line(int x1, int y1, int x2, int y2, FramebufferColor c = FramebufferColor::WHITE);
    void rect(uint8_t x, uint8_t y, size_t w, size_t h, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);
    void circle(int radius, int x_center, int y_center, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);

    /** textual primitives*/
    void init_text_buffer(StructFramebufferText device_config);
    void clear_text_buffer();
    void set_font(const unsigned char *font);
    void print_text();
    void print_text(const char *c_str);
    void print_char(char c);
    void next_line();
    void next_char();
};

#endif // FRAMEBUFFER_H