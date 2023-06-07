///
/// \file logger.cc
/// \brief Logger class implementation
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

#include <cstdarg>
#include <gle/logger.h>
#include <stdexcept>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

namespace gle
{

Logger logger;

/* ***************************** Logger::Logger **************************** */

Logger::Logger (const std::string &file_name)
{
  std::string fname;

  // Name of the file
  if (file_name.empty ())
    {
      fname = PACKAGE " " VERSION;
      fname += ".log";
    }
  else
    {
      fname = file_name;
    }

  // Open logger
  m_log_stream = fopen (fname.c_str (), "w");
  if (!m_log_stream)
    throw std::runtime_error ("fstream::open");
}

/* **************************** Logger::~Logger **************************** */

Logger::~Logger () { fclose (m_log_stream); }

/* ***************************** Logger::print ***************************** */

void
Logger::print (SeverityLevel sl, const std::string &format, ...)
{
  va_list va;

  switch (sl)
    {

    case SeverityLevel::info:
#ifndef NDEBUG
      fprintf (m_log_stream, "[I] ");
#else
      return;
#endif // NDEBUG
      break;

    case SeverityLevel::warning:
#ifndef NDEBUG
      fprintf (m_log_stream, "[W] ");
#else
      return;
#endif // NDEBUG
      break;

    case SeverityLevel::error:
      fprintf (m_log_stream, "[E] ");
      break;

    default:
      break;
    }

  va_start (va, format);
  vfprintf(m_log_stream, format.c_str(), va);
  va_end (va);
  fflush(m_log_stream);
}

}