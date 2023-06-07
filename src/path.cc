///
/// \file path.cc
/// \brief Path utility functions
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

#include "path.h"

namespace gle
{

/* ******************************* Path::Path ****************************** */

Path::Path (const std::string &s)
    : m_driver (""), m_folders (), m_file_name ("")
{
  parse_path (s);
}

/* ******************************* Path::Path ****************************** */

Path::Path (const Path &p)
    : m_driver (p.m_driver), m_folders (p.m_folders), m_file_name (p.m_file_name)
{
  //
}

/* **************************** Path::is_parsed **************************** */

bool
Path::is_parsed ()
{
  return !(m_driver.empty () && m_file_name.empty () && m_folders.empty ());
}

/* **************************** Path::parse_path *************************** */

bool
Path::parse_path (const std::string &location)
{
  // FIXME : Can use RegExp

  std::string str;

  auto it = location.begin ();

  // Check drive
  if (*it == '/') // Root
    {
      it++;
    }
  else // drive
    {
      while (it != location.end () && *it != ':')
        str.push_back (*it);
      if (*it != ':')
        return false;
      it++;
      if (*it != '/')
        return false;
    }

  // Get folders
  while (true)
    {
      str.clear ();
      while (it != location.end () && *it != '/' && *it != '.')
        {
          str.push_back (*it);
          it++;
        }
      if (*it == '/')
        {
          m_folders.push_back (str);
          it++;
        }
      else if (*it == '.')
        {
          while (it != location.end ())
            {
              str.push_back (*it);
              it++;
            }

          m_file_name = str;
          return true;
        }
      else
        return false;
    }
  return true;
}

/* *************************** Path::is_internal *************************** */

bool
Path::is_internal (const std::string &location)
{
  return m_driver == "data";
}

/* *************************** Path::is_resource *************************** */

bool
Path::is_resource (const std::string &location)
{
  return m_driver == "resource";
}

/* ***************************** Path::is_file ***************************** */

bool
Path::is_file (const std::string &location)
{
  return !m_file_name.empty ();
}

/* *************************** Path::is_directory ************************** */

bool
Path::is_directory (const std::string &location)
{
  return m_file_name.empty ();
}

}
