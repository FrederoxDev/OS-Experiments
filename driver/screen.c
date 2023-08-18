#include <stdint.h>
#include "../kernel/low_level.c"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

/*
Converts a position on screen to an absolute offset
*/
uint16_t get_screen_offset(int col, int row) 
{
    return (row * MAX_COLS + col) * 2;
}

/*
Gets the row from an absolute offset
*/
uint16_t get_row(int offset) 
{
    return offset / MAX_COLS;
}

/**
 * Gets the column from an absolute offset
*/
uint16_t get_col(int offset)
{
    return offset % MAX_COLS;
}

/*
Hides the cursor
*/
void disable_cursor()
{
    outb(REG_SCREEN_CTRL, 0x0A);
    outb(REG_SCREEN_DATA, 0x20);
}

/*
Enables the cursor, with the start and end scanlines set
*/
void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) 
{
    outb(REG_SCREEN_CTRL, 0x0A);
    outb(REG_SCREEN_DATA, (inb(REG_SCREEN_DATA) & 0xC0) | cursor_start);

    outb(REG_SCREEN_CTRL, 0x0B);
    outb(REG_SCREEN_DATA, (inb(REG_SCREEN_DATA) & 0xE0) | cursor_end);
}

/*
Sets the cursor to the specified position
*/
void set_cursor_pos(int col, int row) 
{
    uint16_t pos = get_screen_offset(col, row) / 2;

    outb(REG_SCREEN_CTRL, 0x0F);
    outb(REG_SCREEN_DATA, (uint8_t)(pos & 0xFF));
    outb(REG_SCREEN_CTRL, 0x0E);
    outb(REG_SCREEN_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

/*
Gets the absolute position of the cursor
*/
uint16_t get_cursor_position() 
{
    uint16_t pos = 0;
    outb(REG_SCREEN_CTRL, 0x0F);
    pos |= inb(REG_SCREEN_DATA);

    outb(REG_SCREEN_CTRL, 0x0E);
    pos |= ((uint16_t)inb(REG_SCREEN_DATA)) << 8;
    
    return pos;
}

/*
Sets a character
*/
void set_char(char character, int col, int row, char attribute_byte) {
    unsigned char *video_mem = (unsigned char *)VIDEO_ADDRESS;
    int offset = get_screen_offset(col, row);

    video_mem[offset] = character;
    video_mem[offset + 1] = attribute_byte;
}

/*
Entirely blanks the screen and resets the cursor position
*/
void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            set_char(' ', col, row, WHITE_ON_BLACK);
        }
    }

    set_cursor_pos(0, 0);
}

/*
Prints text to terminal
*/
void print(char text[]) 
{
    uint16_t abs_pos = get_cursor_position();
    uint16_t col = get_col(abs_pos);
    uint16_t row = get_row(abs_pos);
    char *c = text;

    // Loop until null terminator
    while (*c != '\0') {
        // New lines
        if (*c == '\n') {
            col = 0;
            row++;
            c++;
            continue;
        }

        set_char(*c, col++, row, WHITE_ON_BLACK);
        if (col >= MAX_COLS) {
            col = 0;
            row++;
        }

        c++;
    }

    set_cursor_pos(col, row);
}