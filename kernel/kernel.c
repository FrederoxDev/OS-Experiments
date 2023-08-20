#include "std/stdio.h"
#include "i386/idt.h"

void _start() {
    clrscr();
    printf("Successfully bootloaded Kernel!\n");

    i386_IDT_Initialize();
    printf("    - Initialized IDT\n");
}