/* EXCEPTION.CPP - Exception Handling Functions
 * Southeastern Policy Institute, 2023
 */

# include <stdint.h>
# include <sys/idt.hpp>
# include <sys/string.hpp>

using namespace sys;

extern "C"
void exception (regs_t* r) {

  static const tchar_t* exception_strings[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
    exception_strings[19],
  };

  if (r->int_no < 32) {
    // ERROR MESSAGE GOES HERE
    asm volatile ("cli\nhlt");
  };

};

