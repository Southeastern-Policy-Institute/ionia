
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

  typedef enum class FLAGS {
    FLAG_0, FLAG_1, FLAG_2
  } flag_t;

  bitmask_t<flag_t> flags { FLAGS::FLAG_0, FLAGS::FLAG_2 };

  if (flags[FLAGS::FLAG_0])
    screen::puts ("FLAG_0 SET!", screen::Cursor (0, 10));
  else
    screen::puts ("FLAG_0 NOT SET!", screen::Cursor (0, 10));

  if (flags[FLAGS::FLAG_1])
    screen::puts ("FLAG_1 SET!", screen::Cursor (0, 11));
  else
    screen::puts ("FLAG_1 NOT SET!", screen::Cursor (0, 11));

  if (flags[FLAGS::FLAG_2])
    screen::puts ("FLAG_2 SET!", screen::Cursor (0, 12));
  else
    screen::puts ("FLAG_2 NOT SET!", screen::Cursor (0, 12));


  asm volatile ("cli\nhlt");
};
