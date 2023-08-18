#include <stdint.h>
#include "../kernel/low_level.c"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
# define REG_SCREEN_CTRL 0x3D4
# define REG_SCREEN_DATA 0x3D5

int get_screen_offset(int col, int row) {
    return (row * MAX_COLS + col) * 2;
}

void set_char(char character, int col, int row, char attribute_byte) {
    unsigned char *video_mem = (unsigned char *)VIDEO_ADDRESS;
    int offset = get_screen_offset(col, row);

    video_mem[offset] = character;
    video_mem[offset + 1] = attribute_byte;
}

void print(char text[], int col, int row) {
    char *c = text;

    while (*c != '\0')
    {
        set_char(*c, col++, row, WHITE_ON_BLACK);
        if (col >= MAX_COLS) {
            col = 0;
            row++;
        }
        c++;
    }

    int cursor_offset = get_screen_offset(col, row) / 2;

    port_byte_out(0x3D4, 0x0F);
	port_byte_out(0x3D5, (uint8_t) (cursor_offset & 0xFF));
	port_byte_out(0x3D4, 0x0E);
	port_byte_out(0x3D5, (uint8_t) ((cursor_offset >> 8) & 0xFF));
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            set_char(' ', col, row, WHITE_ON_BLACK);
        }
    }
}