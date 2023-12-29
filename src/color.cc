///
/// \file color.cc
/// \brief Color class implementation
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

#include "color.h"
#include "opengl.h"

#include <glm/gtc/round.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace gle
{

/* ****************************** Color::Color ***************************** */

Color::Color (float r, float g, float b, float a)
    : m_color_value (glm::clamp (glm::vec4 (r, g, b, a),
                                 glm::vec4 (0.0, 0.0, 0.0, 0.0),
                                 glm::vec4 (1.0, 1.0, 1.0, 1.0)))
{
  //
}

/* ****************************** Color::Color ***************************** */

Color::Color (uint32_t color)
{
  float cl[4];
  cl[0] = static_cast<float> (color & 0xFF) / 255.0f;
  cl[1] = static_cast<float> ((color >> 8) & 0xFF) / 255.0f;
  cl[2] = static_cast<float> ((color >> 16) & 0xFF) / 255.0f;
  cl[3] = static_cast<float> ((color >> 24) & 0xFF) / 255.0f;

  m_color_value = glm::vec4 (cl[0], cl[1], cl[2], cl[3]);
}

/* ****************************** Color::Color ***************************** */

Color::Color (const Color &color) { m_color_value = color.m_color_value; }

/* **************************** Color::color_ptr *************************** */

const float *
Color::color_ptr () const
{
  return glm::value_ptr<float> (m_color_value);
}

/* **************************** Color::operator= *************************** */

Color &
Color::operator= (const Color &color)
{
  m_color_value = color.m_color_value;
  return *this;
}

/* *************************** Color::color_size *************************** */

unsigned int
Color::color_size (ColorType ct)
{
  switch (ct)
    {

    case ColorType::luminance:
      return 1;

    case ColorType::luminance_alpha:
      return 2;

    case ColorType::rgb:
      return 3;

    case ColorType::rgb_alpha:
      return 4;

    default:
      return 0;
    }
}

/* ************************** Color::color_type_gl ************************* */

unsigned int
Color::color_type_gl (ColorType ct)
{
  switch (ct)
    {

    case ColorType::luminance:
      return GL_R;

    case ColorType::luminance_alpha:
      return GL_RG;

    case ColorType::rgb:
      return GL_RGB;

    case ColorType::rgb_alpha:
      return GL_RGBA;

    default:
      return GL_RGB;
    }
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const Color &color)
{
  stream << "{" << color.m_color_value[0] << ", " << color.m_color_value[1]
         << ", " << color.m_color_value[2] << ", " << color.m_color_value[3]
         << "}";
  return stream;
}

}