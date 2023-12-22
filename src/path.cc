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
#include "logger.h"

#include <gio/gio.h>

namespace gle
{

/* ******************************* Path::Path ****************************** */

Path::Path (const std::string &s) : m_drive (""), m_folders ()
{
  parse_path (s);
}

/* ******************************* Path::Path ****************************** */

Path::Path (const Path &p)
    : m_drive (p.m_drive), m_folders (p.m_folders), m_local (p.m_local)
{
  //
}

/* **************************** Path::parse_path *************************** */

bool
Path::parse_path (const std::string &location)
{
  // TODO : Add win32 path extract

  std::string str;

  m_folders.clear ();

  auto it = location.begin ();

  m_local = !(*it == '\\' || *it == '/');

  // Get folders
  while (true)
    {
      str.clear ();
      while (it != location.end () && *it != '/' && *it != '\\')
        {
          str.push_back (*it);
          it++;
        }
      if (*it == '/' || *it == '\\')
        {
          m_folders.push_back (str);
          it++;
        }
      else if (!str.empty ())
        {
          m_folders.push_back (str);
        }
      else
        break;
    }

  update_string ();

  return !m_folders.empty ();
}

/* ************************** Path::update_string ************************** */

void
Path::update_string ()
{
  m_string_path.clear ();

  for (auto it : m_folders)
    {
#if defined(_WIN32)
      m_string_path += "\\";
#elif defined(__linux__)
      m_string_path += "/";
#endif // __linux__
      m_string_path += it;
    }

  #ifdef __linux__
  if (m_local && (m_string_path[0] == '\\' || m_string_path[0] == '/'))
    m_string_path.erase (m_string_path.begin ());
#endif // __linux__
}

/* **************************** Path::to_string **************************** */

const std::string &
Path::to_string ()
{
  return m_string_path;
}

/* ****************************** Path::append ***************************** */

void
Path::append (const std::string &folder)
{
  m_folders.push_back (folder);
  update_string ();
}

/* ***************************** Path::is_file ***************************** */

bool
Path::is_file ()
{
  return g_file_test (
      m_string_path.c_str (),
      static_cast<GFileTest> (G_FILE_TEST_IS_REGULAR | G_FILE_TEST_EXISTS));
}

/* *************************** Path::is_directory ************************** */

bool
Path::is_directory ()
{
  return g_file_test (
      m_string_path.c_str (),
      static_cast<GFileTest> (G_FILE_TEST_IS_DIR | G_FILE_TEST_EXISTS));
}

/* *********************** Path::folder_from_filename ********************** */

Path
Path::folder_from_filename (const std::string &filename)
{
  std::string str = filename;
  auto it = str.end ();
  while (it != str.begin ())
    {
      if (*it == '\\' || *it == '/')
        {
          str.erase (it, str.end ());
          return Path (str);
        }
      else
        {
          it--;
        }
    }

  return Path (str);
}

}
