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

#include "logger.h"
#include "translate.h"

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

  std::streambuf *buf;
  m_ofs.open (fname);
  if (!m_ofs)
    {
      std::cout << _ ("Can not open file ``") << fname
                << _ ("\'\' for writing") << std::endl;
      buf = std::cout.rdbuf ();
    }
  else
    {
      buf = m_ofs.rdbuf ();
    }

  rdbuf (buf);
}

/* ***************************** Logger::Logger **************************** */

Logger::Logger (std::ostream & os)
{
  std::streambuf *buf = os.rdbuf ();
  rdbuf (buf);
}

/* **************************** Logger::~Logger **************************** */

Logger::~Logger ()
{
  *this << SeverityLevel::info << _ ("Close log stream") << std::endl;
}

/* ******************************* operator<< ****************************** */

Logger &
operator<< (Logger &log, SeverityLevel lev)
{
  switch (lev)
    {
    case SeverityLevel::error:
      log << "[E] ";
      break;

    case SeverityLevel::info:
      log << "[I] ";
      break;

    case SeverityLevel::warning:
      log << "[W] ";
      break;
    }

  return log;
}

}