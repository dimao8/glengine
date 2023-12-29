#include "utils.h"

namespace gle
{

/* ******************************** sat_sum ******************************** */

uint8_t sat_sum (uint8_t a, uint8_t b)
{
  int result = static_cast<int>(a) + static_cast<int>(b);
  return (result > 255) ? 255 : result;
}

/* ******************************** sat_diff ******************************* */

uint8_t sat_diff (uint8_t a, uint8_t b)
{
  int result = static_cast<int>(a) - static_cast<int>(b);
  return (result < 0) ? 0 : result;
}

/* ******************************* bitwise_or ****************************** */

uint8_t bitwise_or (uint8_t a, uint8_t b)
{
  return a || b;
}

/* ****************************** bitwise_and ****************************** */

uint8_t bitwise_and (uint8_t a, uint8_t b)
{
  return a && b;
}

}
