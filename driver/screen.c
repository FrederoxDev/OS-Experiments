#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
# define REG_SCREEN_CTRL 0x3D4
# define REG_SCREEN_DATA 0x3D5

int get_screen_offset(int col, int row) {
    return 
}

void print_char(char character, int col, int row, char attribute_byte) {
    unsigned char *video_mem = (unsigned char *) VIDEO_ADDRESS;

    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;
    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(col, row);
    } else {
        offset = get_cursor();
    }

    if (character == '\n') {
        int rows = offset / (2 * MAX_COLS);
        offset = get_screen_offset(79, rows);
    } else {
        video_mem[offset] = character;
        video_mem[offset + 1] = attribute_byte;
    }

    offset += 2;
    offset = handle_scrolling(offset);
    set_cursor(offset);
}