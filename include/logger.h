#ifndef LOGGER_H
#define LOGGER_H

#include <cstdio>
#include <string>

#ifndef NDEBUG
#define LOG_PRINT(x, y, ...) \
  if (x == SeverityLevel::warning || x == SeverityLevel::error) \
    gle::logger.print(SeverityLevel::none, "%s:%i at %s\n", __FILE__, __LINE__, __func__); \
  gle::logger.print(x, y, ##__VA_ARGS__)
#else
#define LOG_PRINT(x, y, ...) \
  gle::logger.print(x, y, ##__VA_ARGS__)
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
class Logger
{

private:
  FILE *m_log_stream; /// Logger stream

public:
  /**
   * Create logger from file. If file_name is empty, generate name with name
   * of the program and current date.
   *
   * \param [in] file_name -- Name of the log-file
   */
  explicit Logger (const std::string &file_name = "");

  /**
   * Close logger stream.
   */
  virtual ~Logger ();

  /**
   * \brief Formatted output to the log file.
   *
   * \param [in] sl -- Severity level. Can be one of SeverityLevel values
   * \param [in] format -- Format string just like in printf
   */
  void print (SeverityLevel sl, const std::string &format, ...);
};

extern Logger logger;

}

#endif // LOGGER_H
