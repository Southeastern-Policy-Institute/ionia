
# include <screen.hpp>
# include <sys/boot.hpp>
# include <sys/mem.hpp>
# include <string.hpp>
# include <bitmask.hpp>

ionia::string test_string {"TEST_STRING"};

extern "C"
void k_main (void) {

  // Set up memory so the allocator doesn't get confused
  for (uint32_t i = 0; i < __map_ent; i++)
    if (__smap[i].BaseL == 0x100000) {
      sys::MEM_BLOCK::MEM_START =
        reinterpret_cast<sys::MEM_BLOCK*> (__smap[i].BaseL);

      sys::MEM_BLOCK::MEM_MAX =
        reinterpret_cast<sys::MEM_BLOCK*> (__smap[i].BaseL + __smap[i].LengthL);
        
      ionia::memset<uint8_t> (
        reinterpret_cast<uint8_t*> (sys::MEM_BLOCK::MEM_START),
        (uint8_t)0,
        250
      );
    };

  // Create screen buffer
  ionia::Screen root;

  // Clear screen
  root.clear ();
  ionia::string* temp = new ionia::string ();
  *temp << "MEMORY AVAILABLE: " << ionia::string::Flag (8)
        << (uint32_t)sys::MEM_BLOCK::MEM_MAX - (uint32_t)sys::MEM_BLOCK::MEM_START;
  root << *temp;
  root.gotoxy (0, 1);
  delete temp;
  temp = new ionia::string ();
  *temp << "TEST STRING: " << ionia::string::Flag (1) << (uint32_t)__map_ent;
  root << *temp;
  root.blit ();
  
  // Quit
  asm volatile ("cli\nhlt");
};
