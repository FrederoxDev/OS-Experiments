#pragma once
#include <stdint.h>
#include "../low_level.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

/*
 * Converts a position on screen to an absolute offset
*/
uint16_t get_screen_offset(int col, int row);

/*
 * Sets a character at an absolute position
*/
void set_char_at_pos(char character, int col, int row, char attribute_byte);

/*
 * Entirely blanks the screen and resets the cursor position
*/
void clear_screen();

/*
 * Moves the cursor visual
*/
void update_cursor_pos();

/**
 * Writes a single character
*/
void write_char(char* character, char attribute_byte);

/**
 * Writes a null terminating string
*/
void print(char* buffer, char attribute_byte);