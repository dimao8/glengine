#ifndef DIRS_H
#define DIRS_H

#include <ostream>
#include <string>
#include <vector>

namespace gle
{

class Dirs
{

private:
  ///
  /// \brief List of the directories, where data folder can be found
  ///
  std::vector<std::string> m_data_dirs;

  ///
  /// \brief List of the directories, where configuration can be found
  ///
  std::vector<std::string> m_config_dirs;
  std::string m_bin_dir;
  std::string m_appname;

  std::string m_current_data_dir;
  std::string m_current_config_filename;
  std::string m_system_config_filename;

public:
  ///
  /// \brief Create and init Dirs object
  ///
  Dirs ();

  ///
  /// \brief Set name of the application
  /// \param [in] appname -- Name of the application
  ///
  /// This function is used to set application name. Application name is used
  /// to search data and configuration. Call this function after Application
  /// class constructed.
  ///
  void set_application_name (const std::string &appname);

  ///
  /// \brief Search for data folder
  /// \param file_name 
  /// \return 
  ///
  bool data_search ();
  bool config_search ();
  bool bin_search ();

  const std::string &data_dir () const;
  const std::string &user_config_file () const;
  const std::string &system_config_file () const;
  const std::string &exe_dir () const;

public:
  friend std::ostream &operator<< (std::ostream &stream, const Dirs &dirs);
};

extern Dirs dirs;

}

#endif // DIRS_H