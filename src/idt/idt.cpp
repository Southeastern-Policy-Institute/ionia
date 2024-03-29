/* IDT.CPP - Interrupt Descriptor Table Functions
 * Southeastern Policy Institute, 2023
 */

# include <stdint.h>
# include <sys/idt.hpp>
# include <sys/port.hpp>
# include <sys/algorithm.hpp>

static inline
void set_idt_gate ( sys::idt_entry_t* idt, uint8_t num, uint32_t base,
                    uint16_t sel, uint8_t flags)
{
  idt[num].base_hi = base >> 16;
  idt[num].base_lo = base & 0xFFFF;
  idt[num].flags = flags;
  idt[num].sel = sel;
};

void sys::install_idt (void) {

  static idt_entry_t* idt = nullptr;

  static IDTR idtr;

  static const void_func_t isr_table[] = {
    isr0,  isr1,  isr2,  isr3,  isr4,  isr5,  isr6,  isr7,
    isr8,  isr9,  isr10, isr11, isr12, isr13, isr14, isr15,
    isr16, isr17, isr18, isr19, isr20, isr21, isr22, isr23,
    isr24, isr25, isr26, isr27, isr28, isr29, isr30, isr31
  };

  static const void_func_t irq_table[] = {
    irq0,  irq1,  irq2,  irq3,  irq4,  irq5,  irq6,  irq7,
    irq8,  irq9,  irq10, irq11, irq12, irq13, irq14, irq15
  };

  // Allocate space for the IDT
  if (!idt)
    idt = new idt_entry_t[IDT_RECORD_COUNT];

  // Set IDT pointer.
  idtr.limit = IDT_RECORD_COUNT - 1;
  idtr.base = reinterpret_cast<uint32_t> (idt);

  // Clear IDT.
  sys::memset<uint8_t> (reinterpret_cast<uint8_t*> (idt),
                        0U,
                        sizeof (idt_entry_t) * IDT_RECORD_COUNT);

  // Install the ISR stubs.
  for (__SIZE_TYPE__ i = 0; i < 32; i++)
    set_idt_gate (idt, i, (unsigned)isr_table[i], 0x08, 0x8E);

  // Remap IRQ's
  sys::outb (0x20, 0x11);
  sys::outb (0xA0, 0x11);
  sys::outb (0x21, 0x20);
  sys::outb (0xA1, 0x28);
  sys::outb (0x21, 0x04);
  sys::outb (0xA1, 0x02);
  sys::outb (0x21, 0x01);
  sys::outb (0xA1, 0x01);
  sys::outb (0x21, 0x0);
  sys::outb (0xA1, 0x0);

  // Install the IRQ stub.
  for (__SIZE_TYPE__ i = 0; i < 16; i++)
    set_idt_gate (idt, i + 32, (unsigned)irq_table[i], 0x08, 0x8E);

  // Load IDT
  asm volatile ("lidt\t%0" : : "m" (idtr));

};
