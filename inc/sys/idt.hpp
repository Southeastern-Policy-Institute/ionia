/* IDT.H - Interrupt Descriptor Table Definitions
 * Southeastern Policy Institute, 2020
 */

# if !defined(_IDT_HPP_) && defined(__cplusplus)
#   define  _IDT_HPP_
#   include <stdint.h>

namespace sys {

  // For storage of processor state.
  typedef struct REGS {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
  } __attribute__ ((packed)) regs_t;

  /* Defines an IDT entry */
  typedef struct IDT_ENTRY {
      uint16_t  base_lo;
      uint16_t  sel;
      uint8_t   always0;
      uint8_t   flags;
      uint16_t  base_hi;
  } __attribute__ ((packed)) idt_entry_t;

  /* Pointer to IDT */
  struct IDTR {
      uint16_t  limit;
      uint32_t  base;
  } __attribute__ ((packed));

  /* Interrupt Handler Type */
  typedef void (*handler_t)(regs_t*);

  /* Void Function Type */
  typedef void (*void_func_t)(void);

  /* All of the various interrupts and service requests.
  * A more elegant solution than this is preferable. */
  extern "C" void_func_t
    isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,
    isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31,
    irq0,  irq1,  irq2,  irq3,  irq4,  irq5,  irq6,  irq7,
    irq8,  irq9,  irq10, irq11, irq12, irq13, irq14, irq15;

  /* Function to install the IDT */
  void install_idt (void);

  /* Function to install IRQ's
  * Located in src/idt/irq.asm */
  extern "C" __attribute__ ((regparm(2)))
  void install_irq (unsigned int, handler_t);

};

# endif /* _IDT_HPP_ */
