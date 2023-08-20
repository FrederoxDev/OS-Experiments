#include "std/stdio.h"
#include "i386/idt.h"
#include "i386/isr.h"

void _start() {
    clrscr();
    printf("Successfully bootloaded Kernel!\n");

    i386_IDT_Initialize();
    printf("    - Initialized IDT\n");

    i386_ISR_Initialize();
    printf("    - Initialized ISR\n");

    printf("\n");
    
    // Cause a divide by 0 error
    asm volatile (
        "mov $0, %%eax\n\t"
        "div %%eax\n\t"
        "ret\n\t"
        :
        :
        : "eax"
    );
}