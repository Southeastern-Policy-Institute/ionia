/* RANDOM.CPP - Pseudo-random number generator.
 * Southeastern Policy Institute, 2020
 */

# include <stdlib.h>

static constexpr
const unsigned char RNGTable[] {
  58, 72, 31, 175, 86, 36, 57, 194, 204, 143, 35, 208, 124, 173, 161,
  34, 147, 49, 211, 123, 2, 232, 4, 100, 189, 134, 30, 224, 37, 18,
  187, 81, 242, 39, 135, 70, 97, 176, 110, 92, 130, 41, 106, 87, 153,
  129, 137, 202, 177, 88, 118, 199, 200, 182, 251, 236, 240, 62, 238, 237,
  207, 168, 29, 45, 17, 98, 193, 60, 20, 142, 229, 205, 146, 125, 249,
  13, 215, 246, 253, 241, 252, 126, 159, 12, 74, 89, 254, 99, 28, 244,
  163, 138, 85, 11, 166, 10, 165, 145, 160, 149, 154, 136, 167, 216, 150,
  6, 226, 116, 171, 56, 109, 75, 234, 54, 38, 120, 127, 121, 15, 94,
  217, 184, 233, 190, 84, 243, 141, 170, 197, 50, 42, 174, 71, 156, 43,
  48, 16, 220, 172, 83, 9, 82, 73, 235, 79, 152, 69, 102, 157, 247,
  248, 221, 201, 180, 113, 53, 77, 59, 186, 14, 188, 228, 196, 5, 52,
  117, 210, 191, 250, 27, 223, 185, 108, 93, 24, 61, 112, 209, 122, 1,
  162, 181, 65, 151, 195, 76, 67, 230, 218, 3, 206, 213, 212, 178, 155,
  55, 111, 7, 183, 44, 115, 132, 68, 80, 21, 103, 90, 64, 101, 46,
  63, 26, 219, 51, 227, 231, 158, 222, 133, 144, 140, 40, 169, 128, 19,
  23, 32, 47, 95, 239, 107, 33, 66, 164, 8, 114, 203, 22, 105, 198,
  214, 179, 255, 96, 131, 245, 148, 119, 139, 78, 104, 225, 25, 192, 91, 0
};

static
__UINT8_TYPE__ RNGAccumulatorA = 0;

static
__UINT8_TYPE__ RNGAccumulatorB = 128;

extern "C" __attribute__ ((nothrow))
__INT32_TYPE__ std::rand (void) {

  union {
    struct {
      __UINT8_TYPE__ a, b, c, d;
    } __attribute__ ((packed));
    __UINT32_TYPE__ abcd;
  } random_val {RNGTable [RNGAccumulatorA++], RNGTable [RNGAccumulatorB++],
                RNGTable [RNGAccumulatorB++], RNGTable [RNGAccumulatorA++]};

  RNGAccumulatorB *= 3;
  return random_val.abcd;

};

extern "C" __attribute__ ((regparm(1), nothrow))
void std::srand (__INT32_TYPE__ seed) {

  RNGAccumulatorA = seed & 0xFF;
  RNGAccumulatorB = seed >> 16;

};
