/* IDT.CPP - Interrupt Descriptor Table Functions
 * Southeastern Policy Institute, 2020
 */

# include <stdint.h>
# include <sys/idt.hpp>
# include <sys/port.hpp>
# include <algorithm.hpp>

static handler_t irq_routines[16];

static idt_entry_t* idt = nullptr;

static IDTR idtr;

extern "C"
void irq_handler (regs_t* r) {
  handler_t handler = irq_routines[r->int_no - 32];

  if (handler)
    handler (r);

  // Notify slave controller.
  if (r->int_no >= 40)
    sys::outb (0xA0, 0x20);

  // Notify master controller.
  sys::outb (0x20, 0x20);
};

static inline
void set_idt_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_hi = base >> 16;
  idt[num].base_lo = base & 0xFFFF;
  idt[num].flags = flags;
  idt[num].sel = sel;
};

void install_idt (void) {

  // Allocate space for the IDT
  if (!idt)
    idt = new idt_entry_t[256];

  // Set IDT pointer.
  idtr.limit = (sizeof (idt_entry_t) * 256) - 1;
  idtr.base = reinterpret_cast<uint32_t> (idt);

  // Clear IDT.
  ionia::memset<uint8_t> (reinterpret_cast<uint8_t*> (idt),
                          0U,
                          sizeof (idt_entry_t) * 256);

  // Install the ISR stubs.
  set_idt_gate (0,  (unsigned)isr0,  0x08, 0x8E);
  set_idt_gate (1,  (unsigned)isr1,  0x08, 0x8E);
  set_idt_gate (2,  (unsigned)isr2,  0x08, 0x8E);
  set_idt_gate (3,  (unsigned)isr3,  0x08, 0x8E);
  set_idt_gate (4,  (unsigned)isr4,  0x08, 0x8E);
  set_idt_gate (5,  (unsigned)isr5,  0x08, 0x8E);
  set_idt_gate (6,  (unsigned)isr6,  0x08, 0x8E);
  set_idt_gate (7,  (unsigned)isr7,  0x08, 0x8E);
  set_idt_gate (8,  (unsigned)isr8,  0x08, 0x8E);
  set_idt_gate (9,  (unsigned)isr9,  0x08, 0x8E);
  set_idt_gate (10, (unsigned)isr10, 0x08, 0x8E);
  set_idt_gate (11, (unsigned)isr11, 0x08, 0x8E);
  set_idt_gate (12, (unsigned)isr12, 0x08, 0x8E);
  set_idt_gate (13, (unsigned)isr13, 0x08, 0x8E);
  set_idt_gate (14, (unsigned)isr14, 0x08, 0x8E);
  set_idt_gate (15, (unsigned)isr15, 0x08, 0x8E);
  set_idt_gate (16, (unsigned)isr16, 0x08, 0x8E);
  set_idt_gate (17, (unsigned)isr17, 0x08, 0x8E);
  set_idt_gate (18, (unsigned)isr18, 0x08, 0x8E);
  set_idt_gate (19, (unsigned)isr19, 0x08, 0x8E);
  set_idt_gate (20, (unsigned)isr20, 0x08, 0x8E);
  set_idt_gate (21, (unsigned)isr21, 0x08, 0x8E);
  set_idt_gate (22, (unsigned)isr22, 0x08, 0x8E);
  set_idt_gate (23, (unsigned)isr23, 0x08, 0x8E);
  set_idt_gate (24, (unsigned)isr24, 0x08, 0x8E);
  set_idt_gate (25, (unsigned)isr25, 0x08, 0x8E);
  set_idt_gate (26, (unsigned)isr26, 0x08, 0x8E);
  set_idt_gate (27, (unsigned)isr27, 0x08, 0x8E);
  set_idt_gate (28, (unsigned)isr28, 0x08, 0x8E);
  set_idt_gate (29, (unsigned)isr29, 0x08, 0x8E);
  set_idt_gate (30, (unsigned)isr30, 0x08, 0x8E);
  set_idt_gate (31, (unsigned)isr31, 0x08, 0x8E);

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
  set_idt_gate (32, (unsigned)irq0,  0x08, 0x8E);
  set_idt_gate (33, (unsigned)irq1,  0x08, 0x8E);
  set_idt_gate (34, (unsigned)irq2,  0x08, 0x8E);
  set_idt_gate (35, (unsigned)irq3,  0x08, 0x8E);
  set_idt_gate (36, (unsigned)irq4,  0x08, 0x8E);
  set_idt_gate (37, (unsigned)irq5,  0x08, 0x8E);
  set_idt_gate (38, (unsigned)irq6,  0x08, 0x8E);
  set_idt_gate (39, (unsigned)irq7,  0x08, 0x8E);
  set_idt_gate (40, (unsigned)irq8,  0x08, 0x8E);
  set_idt_gate (41, (unsigned)irq9,  0x08, 0x8E);
  set_idt_gate (42, (unsigned)irq10, 0x08, 0x8E);
  set_idt_gate (43, (unsigned)irq11, 0x08, 0x8E);
  set_idt_gate (44, (unsigned)irq12, 0x08, 0x8E);
  set_idt_gate (45, (unsigned)irq13, 0x08, 0x8E);
  set_idt_gate (46, (unsigned)irq14, 0x08, 0x8E);
  set_idt_gate (47, (unsigned)irq15, 0x08, 0x8E);

};
