
# include <screen.hpp>
# include <sys/boot.h>
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
  ionia::memset<uint8_t> ((uint8_t*)__kernel_end, (uint8_t)0, 25);

  // Clear screen
  screen::cls ();

  for (uint32_t i = 0; i < __map_ent; i++) {
    ionia::string temp;
    temp
      << ionia::string::Flag (DEFAULT_FLAGS, 1) << '[' << i << "] "
      << ionia::string::Flag (DEFAULT_FLAGS, 8) << smap[i].BaseL << " : " << smap[i].LengthL
      << ionia::string::Flag (DEFAULT_FLAGS, 4) << " : " << smap[i].Type;
    screen::puts (temp, screen::Cursor (0, i));
  };
  
  // Quit
  asm volatile ("cli\nhlt");
};
