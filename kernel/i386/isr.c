#include "isr.h"
#include "idt.h"
#include "gdt.h"
#include "../std/stdio.h"
#include "isr_gen.h"
#include <stddef.h>
#include "../low_level.h"

static const char* const g_Exceptions[] = {
    "Divide by zero error",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception ",
    "",
    "",
    "",
    "",
    "",
    "",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    ""
};

ISRHandler g_ISHandlers[256];

void i386_ISR_Initialize() {
    i386_ISR_InitializeGates();
    
    for (int i = 0; i < 256; i++) {
        i386_IDT_EnableGate(i);
    }
}

void __attribute__((cdecl)) i386_ISR_Handler(Registers* regs) 
{
    if (g_ISHandlers[regs->interrupt] != NULL) 
    {
        g_ISHandlers[regs->interrupt](regs);
    }

    else if (regs->interrupt >= 32)
    {
        printf("Unhandled interrupt %d!\n", regs->interrupt);
    }

    else 
    {
        printf("Unhandled exception: %d, cause: '%s'\n", regs->interrupt, g_Exceptions[regs->interrupt]);

        printf("    eax=%x  ebx=%x  ecx=%x  edx=%x  esi=%x  edi=%x\n", 
            regs->eax, regs->ebx, regs->ecx, regs->edx, regs->esi, regs->edi
        );

        printf("    esp=%x  ebp=%x  eip=%x  eflags=%x  cs=%x  ds=%x  ss=%x\n", 
            regs->esp, regs->ebp, regs->eip, regs->eflags, regs->cs, regs->ds, regs->ss
        );

        printf("    interrupt=%x  errorcode=%x\n", regs->interrupt, regs->error);

        printf("Kernel PANIC\n");
        i386_Panic();
    }
}