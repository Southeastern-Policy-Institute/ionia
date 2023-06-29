

# include <sys/boot.hpp>
# include <sys/mem.hpp>
# include <sys/idt.hpp>
# include <sys/algorithm.hpp>
# include <sys/string.hpp>
# include <sys/screen/panel.hpp>
# include <sys/screen/screen.hpp>
# include <stdlib.h>

extern "C"
void k_main (void) {

  using namespace sys;

  // Set up memory so the allocator doesn't get confused
  for (uint32_t i = 0; i < __map_ent; i++)
    if (__smap[i].BaseL == 0x100000) {
      sys::__mem_max =
        reinterpret_cast<sys::MEM_BLOCK*> (__smap[i].BaseL + __smap[i].LengthL);
        
      sys::memset<uint8_t> (
        reinterpret_cast<uint8_t*> (sys::__mem_start),
        (uint8_t)0,
        250
      );
    };

  // Install IDT
  install_idt ();

  // Enable interrupts
  asm volatile ("sti");

  // Create screen buffer
  sys::screen::Panel<sys::screen::WIDTH, sys::screen::HEIGHT> root;

  // Clear screen
  root.clear ();
  sys::string* temp = new sys::string ();
  *temp << "MEMORY AVAILABLE: " << sys::string::Flag (8)
        << (uint32_t)sys::__mem_max - (uint32_t)sys::__mem_start;
  root << *temp;
  root.gotoxy (0, 1);
  delete temp;
  static const char* strTestNumber = "1337";
  uint32_t intTestNumber = std::atoi (strTestNumber);
  temp = new sys::string ();
  *temp << "TEST NUMBER: " << sys::string::Flag (1, bitmask_t<sys::string::FLAG> (sys::string::ZERO_EXTEND, sys::string::CAPS)) << intTestNumber;
  root << *temp;
  sys::screen::blit (root, 0, 0);

  // Quit
  asm volatile ("cli\nhlt");
};
