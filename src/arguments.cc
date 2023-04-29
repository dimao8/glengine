/**
 * \file arguments.cc
 *
 * The Arguments class implementation file.
 */

#include <gle/arguments.h>

namespace gle
{

/* *************************** Argument::Argument ************************** */

Argument::Argument (const std::string &lname, char sname,
                    const std::string &comment, const std::string &value)
    : m_has_long (true), m_has_short (true), m_long_name (lname),
      m_short_name (sname), m_value (value), m_comment (comment)
{
}

/* *************************** Argument::Argument ************************** */

Argument::Argument (const Argument &arg)
    : m_has_long (arg.m_has_long), m_has_short (arg.m_has_short),
      m_long_name (arg.m_long_name), m_short_name (arg.m_short_name),
      m_value (arg.m_value), m_comment (arg.m_comment)
{
}

/* ************************** Argument::operator= ************************** */

Argument &
Argument::operator= (const Argument &arg)
{
  m_has_long = arg.m_has_long;
  m_has_short = arg.m_has_short;
  m_long_name = arg.m_long_name;
  m_short_name = arg.m_short_name;
  m_value = arg.m_value;

  return *this;
}

/* ************************** Argument::operator== ************************* */

bool
Argument::operator== (const Argument &arg)
{
  if (m_has_long)
    return m_long_name == arg.m_long_name;
  else if (m_has_short)
    return m_short_name == arg.m_short_name;
  else
    return false;
}

/* ************************ Argument::get_short_name *********************** */

std::string
Argument::get_short_name ()
{
  std::string s = "-";
  s.push_back (m_short_name);

  return s;
}

/* ************************ Argument::get_long_name ************************ */

std::string
Argument::get_long_name ()
{
  return std::string("--") + m_long_name;
}

/* ************************** Argument::get_value ************************** */

std::string
Argument::get_value ()
{
  return m_value;
}

/* ************************* Argument::get_comment ************************* */

std::string
Argument::get_comment ()
{
  return m_comment;
}

/* ************************ Argument::has_long_name ************************ */

bool
Argument::has_long_name ()
{
  return m_has_long;
}

/* ************************ Argument::has_short_name *********************** */

bool
Argument::has_short_name ()
{
  return m_has_short;
}

/* ************************** Argument::has_value ************************** */

bool
Argument::has_value ()
{
  return !m_value.empty ();
}

}