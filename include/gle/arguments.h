///
/// \file arguments.h
/// \brief Argument class implementation
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

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <string>

namespace gle
{

/**
 * \brief The command line argument class
 *
 * According to the [Coding Standards](https://www.gnu.org/prep/standards/),
 * there is two forms of the arguments: short arguments and long arguments.
 *
 * Short argument has form of <code>-x<sp>[val]</code> . It starts from dash
 * symbol, than one lowercase latin symbol. After symbol there can be one or
 * more spaces, or spaces can be omitted. After space there is an optional
 * value part.
 *
 * \code -h
 * -p./src
 * -p ./src \endcode
 *
 * The long version must have form of <code>--xxxxx[=][val]</code>. It must
 * be started from two dashes, then the argument name goes. If the value must
 * be set, there is equal symbol (=) followed by value string.
 *
 * \code --help
 * --path=./src \endcode
 *
 * Argument class
 */
class Argument
{

private:
  bool m_has_short;  /// This field has \c true value if argument has short
                     /// version
  bool m_has_long;   /// This field has \c true value if argument has long
                     /// version
  char m_short_name; /// Short argument name
  std::string m_long_name; /// Long argument name
  std::string
      m_value; /// Argument value. Can be empty string if no value has been set
  std::string m_comment; /// Argument comment

public:
  Argument () = delete;

  /**
   * Create argument with both short and long versions
   *
   * \param [in] lname -- Long name of the argument
   * \param [in] sname -- Short name of the argument
   * \param [in] value -- Value of the argument. Set this arg to empty string
   *                    if there is no value
   */
  Argument (const std::string &lname, char sname,
            const std::string &comment = "", const std::string &value = "");

  /**
   * \brief Copy constructor
   */
  Argument (const Argument &arg);

  /**
   * \brief Assignment operator
   */
  Argument &operator= (const Argument &arg);

  /**
   * \brief Equal operator
   */
  bool operator== (const Argument &arg);

  // Getters and setters
public:
  std::string get_short_name ();
  std::string get_long_name ();
  std::string get_value ();
  std::string get_comment ();

  bool has_long_name ();
  bool has_short_name ();
  bool has_value ();
};

}

#endif // ARGUMENTS_H
