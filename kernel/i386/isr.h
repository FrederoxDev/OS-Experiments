#pragma once
#include <stdint.h>

typedef struct {
    // In the reverse order that they were pushed

    uint32_t ds;
    uint32_t edi, esi, ebp, kern_esp, ebx, edx, ecx, eax; 
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp, ss;

} __attribute__((packed)) Registers;

typedef void (*ISRHandler)(Registers* regs);

void i386_ISR_Initialize();
void i386_ISR_RegisterHandler(int interrupt);