#include <cstdarg>
#include <logger.h>
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
}

}