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

enum class Framebuffer_format
{
    MONO_VLSB,
    MONO_HLSB,
    MONO_HMSB,
    RGB565
};

enum class Framebuffer_color
{
    BLACK = 0,
    WHITE = 1
};

typedef struct struct_text_frame
{
    const unsigned char *font{nullptr};
    uint8_t tab_size{2};
    Framebuffer_color fg_color{Framebuffer_color::WHITE};
    Framebuffer_color bg_color{Framebuffer_color::BLACK};
    bool wrap{true};
    bool auto_next_char{true};
} config_framebuffer_text_t;

class Framebuffer
{
private:
    size_t pixel_buffer_size;
    size_t text_buffer_size;
    Framebuffer_format frame_format;
    uint8_t current_char_line{0};
    uint8_t current_char_column{0};

    void ellipse(uint8_t x_center, uint8_t y_center, uint8_t x_radius, uint8_t y_radius, bool fill, uint8_t quadrant, Framebuffer_color c);
    void drawChar(const unsigned char *font, char c, uint8_t anchor_x, uint8_t anchor_y);
    void drawChar(char c, uint8_t char_column, uint8_t char_line);
    void pixel(int x, int y, Framebuffer_color c = Framebuffer_color::WHITE);
    void clear_line();

public:
    uint8_t *pixel_buffer;
    char *text_buffer;
    config_framebuffer_text_t frame_text_config{};
    uint8_t frame_width;
    uint8_t frame_height;
    uint8_t max_line{0};
    uint8_t max_column{0};

    Framebuffer(size_t width, size_t height, 
    Framebuffer_format format = Framebuffer_format::MONO_VLSB, config_framebuffer_text_t txt_cnf = {.font = font_8x8});//TODO inverser ordre format et txt_cnf
    ~Framebuffer();

    /* graphic primitives*/
    void clear_pixel_buffer();
    void fill(Framebuffer_color c);
    void hline(uint8_t x, uint8_t y, size_t w, Framebuffer_color c = Framebuffer_color::WHITE);
    void vline(uint8_t x, uint8_t y, size_t h, Framebuffer_color c = Framebuffer_color::WHITE);
    void line(int x1, int y1, int x2, int y2, Framebuffer_color c = Framebuffer_color::WHITE);
    void rect(uint8_t x, uint8_t y, size_t w, size_t h, bool fill = false, Framebuffer_color c = Framebuffer_color::WHITE);
    void circle(int radius, int x_center, int y_center, bool fill = false, Framebuffer_color c = Framebuffer_color::WHITE);

    /* textual primitives*/
    void clear_text_buffer();
    void set_text_config(config_framebuffer_text_t device_config);
    void set_font(const unsigned char *font);
    void print_text();
    void print_text(const char *c_str);
    void print_char(char c);
    void next_line();
    void next_char();
};


#endif // FRAMEBUFFER_H