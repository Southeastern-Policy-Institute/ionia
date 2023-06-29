

# include <sys/boot.hpp>
# include <sys/mem.hpp>
# include <sys/idt.hpp>
# include <sys/algorithm.hpp>
# include <sys/string.hpp>
# include <sys/screen/screen>
# include <stdlib.h>

extern "C"
void k_main (void) {

  using namespace sys;

  // Set up memory so the allocator doesn't get confused
  for (uint32_t i = 0; i < __map_ent; i++)
    if (__smap[i].BaseL == 0x100000) {
      __mem_max = reinterpret_cast<MEM_BLOCK*>
        (__smap[i].BaseL + __smap[i].LengthL);
        
      memset<uint8_t> (
        reinterpret_cast<uint8_t*> (__mem_start),
        (uint8_t)0,
        250
      );
    };

  // Install IDT
  install_idt ();

  // Enable interrupts
  asm volatile ("sti");


  // Create screen buffer
  screen::Panel<screen::WIDTH, screen::HEIGHT> root;
  screen::Panel<30, 5> test_panel (screen::COLOR::BLACK, screen::COLOR::LIGHT_BLUE);

  // Clear screen
  root.clear ();
  string* temp = new string ();
  *temp << "MEMORY AVAILABLE: " << string::Flag (8)
        << (uint32_t)__mem_max - (uint32_t)__mem_start;
  test_panel << *temp;
  test_panel.gotoxy (0, 1);
  delete temp;
  static const char* strTestNumber = "1337";
  uint32_t intTestNumber = std::atoi (strTestNumber);
  temp = new string ();
  *temp << "TEST NUMBER: " << string::Flag (1, bitmask_t<string::FLAG> (string::ZERO_EXTEND, string::CAPS)) << intTestNumber;
  test_panel << *temp;
  delete temp;
  screen::blit (root, 0, 0);
  screen::blit (test_panel, 5, 5);

  // Quit
  asm volatile ("cli\nhlt");
};
