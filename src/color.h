///
/// \file color.h
/// \brief Color class header
/// \author Khruschev Dmitry aka DimaO
/// \version 0.1
///
/// \copyright Copyright (C) 2023 Khruschev Dmitry aka DimaO
///
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
// USA
//

#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <glm/vec4.hpp>
#include <string>

namespace gle
{

enum class ColorType
{
  luminance,
  luminance_alpha,
  rgb,
  rgb_alpha
};

///
/// \brief Color class
///
class Color
{

private:
  glm::vec4 m_color_value;

public:
  Color () = delete;

  ///
  /// \brief Create color from floats
  /// \param [in] r -- Red channel (0; 1)
  /// \param [in] g -- Green channel (0; 1)
  /// \param [in] b -- Blue channel (0; 1)
  /// \param [in] a -- Alpha channel (0; 1)
  ///
  Color (float r, float g, float b, float a);

  ///
  /// \brief Create color from packed int
  /// \param [in] color -- Integer value with 4 channels
  ///
  Color (uint32_t color);

  ///
  /// \brief Copying constructor
  /// \param [in] -- Color value
  ///
  Color (const Color &color);

  virtual ~Color () {}

  const float *color_ptr () const;

  Color &operator= (const Color &color);

public:
  ///
  /// Get size of pixel with ColorType
  ///
  /// \param [in] ct -- Color type
  /// \return Return size in bytes of corresponding pixel
  ///
  static unsigned int color_size (ColorType ct);
};

}

#endif // COLOR_H
