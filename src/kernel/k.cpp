
# include <screen.hpp>
# include <sys/boot.h>
# include <sys/mem.hpp>
# include <string.hpp>
# include <bitmask.hpp>

smap_entry_t* smap = reinterpret_cast<smap_entry_t*>
  (reinterpret_cast<uintptr_t> (&__map_ent) + 4);

extern "C"
void k_main (void) {

  constexpr
  bitmask_t<ionia::string::FLAG> DEFAULT_FLAGS = {
    ionia::string::HEX, ionia::string::ZERO_EXTEND, ionia::string::CAPS
  };

  // Set up memory so the allocator doesn't get confused
  for (uint32_t i = 0; i < __map_ent; i++)
    if (smap[i].BaseL == 0x100000) {
      sys::MEM_BLOCK::MEM_START =
        reinterpret_cast<sys::MEM_BLOCK*> (smap[i].BaseL);

      sys::MEM_BLOCK::MEM_MAX =
        reinterpret_cast<sys::MEM_BLOCK*> (smap[i].BaseL + smap[i].LengthL);
        
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
  ionia::string temp;
  temp  << "MEMORY AVAILABLE: " << ionia::string::Flag (DEFAULT_FLAGS, 8)
        << (uint32_t)sys::MEM_BLOCK::MEM_MAX - (uint32_t)sys::MEM_BLOCK::MEM_START;
  root << temp;
  root.blit ();
  
  // Quit
  asm volatile ("cli\nhlt");
};
