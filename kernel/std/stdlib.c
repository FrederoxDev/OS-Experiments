#include "stdlib.h"

char* reverse(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}

/**
 * Integer To Ascii
*/
char* itoa(int input, char *buffer, int radix) 
{
    int i = 0;
    int isNegative = 0;

    // Handle 0 explicitly
    if (input == 0) {
        buffer[i++] = '0';
        buffer[i] = '\0';
        return buffer;
    }

    // Handle negative numbers if base is 10
    if (input < 0 && radix == 10) {
        isNegative = 1;
        input = -input;
    }

    // Convert into a string
    while(input != 0) {
        int remainder = input % radix;
        buffer[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        input = input / radix;
    }

    // Handle negatives
    if (isNegative) buffer[i++] = '-';

    // Null terminate
    buffer[i] = '\0';
    reverse(buffer, i);

    return buffer;
}