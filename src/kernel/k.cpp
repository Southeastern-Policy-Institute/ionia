
# include <screen.hpp>
# include <sys/boot.h>
# include <string.hpp>
# include <bitmask.hpp>

extern "C" const char* itoa (int32_t num, uint32_t base);
extern "C" __SIZE_TYPE__ sprintf (char* str, const char* format, ...);

smap_entry_t* smap = reinterpret_cast<smap_entry_t*> (
  reinterpret_cast<uintptr_t> (&__map_ent) + 4
);

extern "C" void k_main (void) {
  volatile uint16_t* root = reinterpret_cast<volatile uint16_t*> (0xB8000);
  //asm volatile ("sti");
  for (uint32_t i = 0; i < 80*25; i++) {
    root[i] = screen::schar_t (' ');
  };

  ionia::memset<uint8_t> ((uint8_t*)__kernel_end, (uint8_t)0, 25);
  
  ionia::string test_string_0 { 'T', 'E', 'S', 'T', '_', '0', ' ' };
  ionia::string test_string_1 { "TEST_1 " };
  test_string_0 << test_string_1 << "TEST_2";
  screen::puts (test_string_0, screen::Cursor (0,0));

  asm volatile ("cli\nhlt");
};
