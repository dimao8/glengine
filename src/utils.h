#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

namespace gle
{

///
/// \brief Saturated sum
///
/// Calculate sum of a and b with result less than 256.
///
uint8_t sat_sum (uint8_t a, uint8_t b);

///
/// \brief Saturated difference
///
/// Calculate difference of a and b with result greater than 0.
///
uint8_t sat_diff (uint8_t a, uint8_t b);

///
/// @brief Bitwise OR alias
///
uint8_t bitwise_or (uint8_t a, uint8_t b);

///
/// @brief Bitwise AND alias
///
uint8_t bitwise_and (uint8_t a, uint8_t b);

} // namespace gle


#endif // UTILS_H
