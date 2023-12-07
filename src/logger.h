///
/// \file logger.h
/// \brief Logger class header
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

#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <iostream>
#include <fstream>
#include <string>

#ifdef NDEBUG
#define LOG_DEBUG(x)
#else
#define LOG_DEBUG(x) x
#endif // NDEBUG

namespace gle
{

/**
 * \brief Severity level type
 */
enum class SeverityLevel
{
  none,    /// Do not add severity level
  info,    /// Add [I] at the start of the line
  warning, /// Add [W] at the start of the line
  error    /// Add [E] at the start of the line
};

/**
 * The Logger class
 */
class Logger : public std::ostream
{

private:

  std::ofstream m_ofs;

public:
  /**
   * Create logger from file. If file_name is empty, generate name with name
   * of the program and current date.
   *
   * \param [in] file_name -- Name of the log-file
   */
  explicit Logger (const std::string & file_name = "");
  
  explicit Logger (std::ostream & os);

  /**
   * Close logger stream.
   */
  virtual ~Logger ();

  /// Input operators
  friend Logger &operator<< (Logger & log, SeverityLevel lev);
};

extern Logger logger;

}

#endif // LOGGER_H
