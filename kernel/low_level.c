/*
Reads a byte from a specified port
*/
unsigned char port_byte_in(unsigned short port) {
    // "=a" ( result ) means : put AL register in variable RESULT when finished
    // "d" ( port ) means : load EDX with port
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}   