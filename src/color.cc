#include <gle/color.h>

namespace gle
{

/* ******************************* color_size ****************************** */

unsigned int
color_size (ColorType ct)
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

}