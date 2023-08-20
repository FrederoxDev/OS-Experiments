#include "screen.h"

// Globals
int g_row = 0;
int g_col = 0;

/*
 * Converts a position on screen to an absolute offset
*/
uint16_t get_screen_offset(int col, int row) 
{
    return row * MAX_COLS + col;
}

/*
 * Sets a character at an absolute position
*/
void set_char_at_pos(char character, int col, int row, char attribute_byte) 
{
    unsigned char *video_mem = (unsigned char *)VIDEO_ADDRESS;
    int offset = get_screen_offset(col, row) * 2;

    video_mem[offset] = character;
    video_mem[offset + 1] = attribute_byte;
}

/*
 * Entirely blanks the screen and resets the cursor position
*/
void clear_screen() 
{
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            set_char_at_pos(' ', col, row, WHITE_ON_BLACK);
        }
    }

    g_col = 0;
    g_row = 0;
}

/*
 * Moves the cursor visual
*/
void update_cursor_pos() 
{
    uint16_t pos = get_screen_offset(g_col, g_row);

    outb(REG_SCREEN_CTRL, 0x0F);
    outb(REG_SCREEN_DATA, (uint8_t)(pos & 0xFF));
    outb(REG_SCREEN_CTRL, 0x0E);
    outb(REG_SCREEN_DATA, (uint8_t)((pos >> 8) & 0xFF));
}

/**
 * Writes a single character
*/
void write_char(char* character, char attribute_byte) 
{
    if (*character == '\n') 
    {
        g_col = 0;
        g_row++;
        return;
    }

    set_char_at_pos(*character, g_col++, g_row, attribute_byte);

    // Wrap at the end of the line
    if (g_col >= MAX_COLS) {
        g_col = 0;
        g_row++;
    }

    // Wrap at the bottom back to the top
    if (g_row >= MAX_ROWS) {
        g_row = 0;
        g_col = 0;
    }
}

/**
 * Writes a null terminating string
*/
void print(char* buffer, char attribute_byte) {
    while (*buffer != '\0') {
        write_char(buffer, attribute_byte);
        buffer++;
    }
}