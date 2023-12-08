#include "dirs.h"
#include "logger.h"

#include <cstring>
#include <glib.h>

#if defined(_WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32

namespace gle
{

Dirs dirs;

/* ******************************* Dirs::Dirs ****************************** */

Dirs::Dirs ()
{
  std::string str;
  int i;

  const gchar *const *data_dirs = g_get_system_data_dirs ();
  i = 0;
  while (data_dirs[i] != nullptr)
    {
      if (std::strlen (data_dirs[i]) != 0)
        m_data_dirs.emplace_back (data_dirs[i]);
      i++;
    }
  str = g_get_user_data_dir ();
  if (!str.empty ())
    m_data_dirs.push_back (str);
  if (m_data_dirs.empty ())
    logger << SeverityLevel::warning
           << "Unable to get at least one user data directory" << std::endl;

  const gchar *const *config_dirs = g_get_system_config_dirs ();
  i = 0;
  while (config_dirs[i] != nullptr)
    {
      if (std::strlen (config_dirs[i]) != 0)
        m_config_dirs.emplace_back (config_dirs[i]);
      i++;
    }
  str = g_get_user_config_dir ();
  if (!str.empty ())
    m_config_dirs.push_back (str);
  if (m_config_dirs.empty ())
    logger << SeverityLevel::warning
           << "Unable to get at least one config directory" << std::endl;
}

/* ************************* Dirs::data_search_for ************************* */

bool
Dirs::data_search ()
{
  std::string str;

  // Init m_current_data_dir with <pwd>/share/<appname>
  m_current_data_dir = g_get_current_dir ();
#if defined(_WIN32)
  m_current_data_dir.push_back ('\\');
#else
  m_current_data_dir.push_back ('/');
#endif // _WIN32
  m_current_data_dir += "share";
  if (!m_appname.empty ())
    {
#if defined(_WIN32)
      m_current_data_dir.push_back ('\\');
#else
      m_current_data_dir.push_back ('/');
#endif // _WIN32
      m_current_data_dir += m_appname;
    }

  if (m_data_dirs.empty ())
    return false;

  // Search for data directories
  for (auto it : m_data_dirs)
    {
      str = it;
#if defined(_WIN32)
      str.push_back ('\\');
#else
      str.push_back ('/');
#endif // _WIN32
      if (!m_appname.empty ())
        str += m_appname; // TODO : Check for correct file name in filesystem
      if (g_file_test (str.c_str (), G_FILE_TEST_IS_DIR))
        {
          LOG_DEBUG (logger << SeverityLevel::info << "Folder ``" << str);
          LOG_DEBUG (logger << "\'\' is found" << std::endl);
          m_current_data_dir = str;
          return true;
        }
    }

  logger << SeverityLevel::warning << "Folder ``" << str
         << "\'\' was not found in any datadirs" << std::endl;
  return false;
}

/* ************************** Dirs::config_search ************************** */

bool
Dirs::config_search ()
{
  std::string str;

  // Init m_current_config_filename with <pwd>/<appname>.json
  m_current_config_filename = g_get_current_dir ();
#if defined(_WIN32)
  m_current_config_filename.push_back ('\\');
#else
  m_current_config_filename.push_back ('/');
#endif // _WIN32
  m_current_config_filename += m_appname + ".json";

  if (m_data_dirs.empty ())
    return false;

  // Search for data directories
  str = g_get_user_config_dir ();

  if (g_file_test (str.c_str (), G_FILE_TEST_IS_DIR))
    {
      LOG_DEBUG (logger << SeverityLevel::info << "Folder ``" << str);
      LOG_DEBUG (logger << "\'\'found" << std::endl);
#if defined(_WIN32)
      str.push_back ('\\');
#else
      str.push_back ('/');
#endif                 // _WIN32
      str += m_appname // TODO : Check for correct file name in filesystem
             + ".json";
      m_current_config_filename = str;
      return true;
    }

  logger << SeverityLevel::warning << "``" << m_current_config_filename
         << "\'\' not found in user configdir" << std::endl;
  return false;
}

/* **************************** Dirs::bin_search *************************** */

bool
Dirs::bin_search ()
{
  char buf[256];
  size_t sz = sizeof (buf);
#if defined(_WIN32)
  int bytes = GetModuleFileName (NULL, buf, sz);
#else
  int bytes = MIN (readlink ("/proc/self/exe", buf, sz), sz - 1);
#endif // _WIN32

  int i = bytes - 1;
  while (i != 0 && buf[i] != '/' && buf[i] != '\\')
    i++;
  if (buf[i] == '/' && buf[i] == '\\')
    i--;
  buf[i] = 0;

  m_bin_dir = buf;
  return true;
}

/* *********************** Dirs::set_application_name ********************** */

void
Dirs::set_application_name (const std::string &appname)
{
  m_appname = appname;
}

/* ***************************** Dirs::data_dir **************************** */

const std::string &
Dirs::data_dir () const
{
  return m_current_data_dir;
}

/* ************************* Dirs::user_config_file ************************ */

const std::string &
Dirs::user_config_file () const
{
  return m_current_config_filename;
}

/* ************************ Dirs::system_config_file *********************** */

const std::string &
Dirs::system_config_file () const
{
  return m_system_config_filename;
}

/* ***************************** Dirs::exe_dir ***************************** */

const std::string &
Dirs::exe_dir () const
{
  return m_bin_dir;
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const Dirs &dirs)
{
  if (!dirs.m_data_dirs.empty ())
    {
      stream << "Data dirs: ";
      for (auto i = 0; i < dirs.m_data_dirs.size (); i++)
        {
          stream << dirs.m_data_dirs[i];
          if (i != dirs.m_data_dirs.size () - 1)
            stream << ':';
        }
      stream << std::endl;
    }

  stream << "Current data dir: " << dirs.m_current_data_dir << std::endl;

  if (!dirs.m_config_dirs.empty ())
    {
      stream << "Config dirs: ";
      for (auto i = 0; i < dirs.m_config_dirs.size (); i++)
        {
          stream << dirs.m_config_dirs[i];
          if (i != dirs.m_config_dirs.size () - 1)
            stream << ':';
        }
      stream << std::endl;
    }
  stream << "User config file: " << dirs.m_current_config_filename
         << std::endl;
  stream << "System config file: " << dirs.m_system_config_filename
         << std::endl;

  stream << "Execute dir: " << dirs.m_bin_dir << std::endl;

  return stream;
}

}