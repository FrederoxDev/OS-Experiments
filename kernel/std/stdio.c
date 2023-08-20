#include "stdio.h"

void printf(char* format, ...) 
{
    va_list args;
    va_start(args, format);
    char* c = format;

    // Begin printing to the terminal
    while (*c != '\0') {
        if (*c == '%') {
            c++;

            // Characters
            if (*c == 'c') {
                char* value = va_arg(args, char*);
                print(value, WHITE_ON_BLACK);
            }

            // String
            if (*c == 's') {
                char* string = va_arg(args, char*);
                print(string, WHITE_ON_BLACK);
            }

            // Signed integers
            if (*c == 'd' || *c == 'i') {
                int number = va_arg(args, int);
                char buffer[20];

                itoa(number, buffer, 10);
                print(buffer, WHITE_ON_BLACK);
            }

            // Hexadecimal
            if (*c == 'x') {
                int number = va_arg(args, int);
                char buffer[20];
                
                itoa(number, buffer, 16);
                print(buffer, WHITE_ON_BLACK);
            }

            c++;
            continue;
        }

        write_char(c, WHITE_ON_BLACK);
        c++;
    }

    va_end(args);
    update_cursor_pos();
}

void clrscr() {
    clear_screen();
    update_cursor_pos();
}