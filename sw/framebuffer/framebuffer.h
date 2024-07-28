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
     * \image html framebuffer.png 
     */
    Framebuffer(size_t frame_width,
                size_t frame_height,
                FramebufferFormat frame_format = FramebufferFormat::MONO_VLSB);
    /**
     * @brief Destroy the Framebuffer object
     */
    ~Framebuffer();

    /**
     * @brief Fill the pixel_buffer with "0" (BLACK). Reset also character position to (0,0).
     */
    void clear_pixel_buffer();
    /**
     * @brief Write all framebuffer memory with "0" (or "1") if color c is BLACK (resp. WHITE).
     * 
     * Only format MONO_VLSB is implemented.
     * 
     * @param c FramebufferColor
     */
    void fill(FramebufferColor c);
    /**
     * @brief  Draw a c color horizontal line, starting at frame position (x,y), on w number of pixel.
     * 
     * @param x   horizontal start of line 
     * @param y   vertical start of line
     * @param w   length of the line in number of pixel
     * @param c   color of the line, default to WHITE
     */
    void hline(uint8_t x, uint8_t y, size_t w, FramebufferColor c = FramebufferColor::WHITE);
    /**
     * @brief  Draw a c color vertical line, starting at frame position (x,y), on w number of pixel.
     * 
     * @param x   horizontal start of line 
     * @param y   vertical start of line
     * @param h   length of the line in number of pixel
     * @param c   color of the line, default to WHITE
     */
    void vline(uint8_t x, uint8_t y, size_t h, FramebufferColor c = FramebufferColor::WHITE);
    /**
     * @brief   Draw a c color line, starting at frame position (x1,y1), ending at frame position (x2,y2)
     * 
     * @param x1   horizontal start of line
     * @param y1   vertical start of line
     * @param x2   horizontal end of line
     * @param y2   vertical end of line
     * @param c   color of the line, default to WHITE
     */
    void line(int x1, int y1, int x2, int y2, FramebufferColor c = FramebufferColor::WHITE);
    /**
     * @brief   Draw a rectangle, starting at frame position (x,y), w wide and h high
     * 
     * @param x   horizontal start of the rectangle
     * @param y   vertical start of the rectangle
     * @param w   number of pixel of the rectangle width 
     * @param h   number of pixel of the rectangle height
     * @param fill if true, the rectangle is filled with color c
     * @param c color of the border of the rectangle, default to WHITE
     */
    void rect(uint8_t x, uint8_t y, size_t w, size_t h, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);
    /**
     * @brief draw a cercle of size radius, centered at (x_center, y_center)
     * 
     * @param radius   radius, in pixel, of the circle
     * @param x_center   horizontal position of the center of the cercle
     * @param y_center   vertical position of the center on the cercle
     * @param fill   if true, the circle is filled with color c
     * @param c   color of the border of the circle, default to WHITE
     */
    void circle(int radius, int x_center, int y_center, bool fill = false, FramebufferColor c = FramebufferColor::WHITE);

    /**
     * @brief   Initialize the textual features of framebuffer, according to the configuration data structure frame_text_config
     * 
     * @param   frame_text_config 
     */
    void init_text_buffer(StructFramebufferText frame_text_config);
    /**
     * @brief   Set text buffer memory to "0" and set character line and column to 0
     */
    void clear_text_buffer();
    /**
     * @brief Update the reference to the font, recompute max number of line, column, the new text buffer size, delete the previous one if any and create a new buffer.
     * 
     * @param font 
     */
    void set_font(const unsigned char *font);
    /**
     * @brief copy the internal framebuffer text buffer to the device buffer.
     */
    void print_text();
    /**
     * @brief copy the string c_str to the device buffer.
     * 
     * @param c_str A C_style character string.
     */
    void print_text(const char *c_str);
    /**
     * @brief copy the c character to the current line and column character position.
     * 
     * Text wrapping is done if wrap flag is true.
     * Character position steps forward according to auto_next_char flag.
     * 
     * Some special characters are processed:
     * 
     *  - "LINE_FEED"       (\\n 0x0A) : line position steps forward, column position is set to 0.
     * 
     *  - "BACKSPACE"       (\\b  0x08) : column position steps backward, a space (" ") character is overwritten.
     * 
     *  - "FORM_FEED"       (\\f  0x0C) : the text buffer is cleared.
     * 
     *  - "CARRIAGE_RETURN" (\\r  0x0D) : column position is set to 0.
     * 
     *  - "HORIZONTAL_TAB"  (\\t  0x09) : " " characters are added according to tab_size configuration value.
     * @param c 
     */
    void print_char(char c);
    /**
     * @brief character line position steps forward
     */
    void next_line();
    /**
     * @brief character column position steps forward
     */
    void next_char();
};

#endif // FRAMEBUFFER_H