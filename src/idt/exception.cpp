/* EXCEPTION.CPP - Exception Handling Functions
 * Southeastern Policy Institute, 2020
 */

# include <stdint.h>
# include <sys/idt.hpp>
# include <ionia.hpp>
# include <screen.hpp>

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
    ionia::Screen exception_message_screen;
    ionia::string temp;
    exception_message_screen.clear ();
    temp << "EXCEPTION [" << r->int_no << "] " << exception_strings[r->int_no];
    exception_message_screen.gotoxy (2, 1);
    exception_message_screen << temp;
    exception_message_screen.blit ();
    asm volatile ("cli\nhlt");
  };

};

