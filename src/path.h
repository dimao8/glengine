///
/// \file path.h
/// \brief Directory handle function prototypes
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

#ifndef PATH_H
#define PATH_H

#include <string>
#include <vector>

namespace gle
{

///
/// \brief Parsed path structure
///
/// Extract driver, list of the folders and file name.
///
/// Driver is a prefix, separated from other path with ``://''. It is extract
/// without ``://'' sequence adn store to the driver \c field. If no driver is
/// exist, the driver \c field will contain empty string.
///
/// List of folders contain list of sequential directory tree moves, including
/// one dot (means this folder) and two dots (means parent folder). Every
/// single move is stored in one string in the list. Separation must be
/// determined by slash. If last entry is a file name, it is not saved to list.
///
/// File name (if exist) is stored in \c file_name field. If path has no file,
/// an empty string is stored to the \c file_name field.
///
class Path
{
private:
  std::string m_driver;               /// Driver name
  std::vector<std::string> m_folders; /// Folder list
  std::string m_file_name; /// Name of the file (if path ends with file name)

  ///
  /// \brief Parse path string
  /// \param [in] location -- Path to parse
  /// \param [out] parsed -- Path structure
  /// \return Return result of parsing
  ///
  bool parse_path (const std::string &location);

public:
  Path () = delete;
  Path (const std::string &s);
  Path (const Path &p);

  ///
  /// \brief Return \c true if path was successfully parsed
  ///
  bool is_parsed();

  ///
  /// \brief Check if location is located at application folder
  /// \param [in] location -- Path to check
  /// \return Return \c true if path is in application folder
  ///
  /// There is special paths to simplify crossplatform code. If path starts
  /// with \c data:// , the files in this path are search from application
  /// folder. The application path always starts at directory, where
  /// application bin folder is located.
  ///
  bool is_internal (const std::string &location);

  ///
  /// \brief Check if location is located at virtual resource folder
  /// \param [in] location -- Path to check
  /// \return Return \c true if path is resource
  ///
  /// Some data can be stored as resource. The resource is the file that store
  /// in compressed form in dynamic library or application executable file.
  /// Any resource file can be extracted by prepend path with \c resource://
  ///
  bool is_resource (const std::string &location);

  ///
  /// \brief Check if location points to the regular file
  /// \param [in] location -- Path to check
  /// \return Return \c true if path is regular file
  ///
  /// If path points to the regular file (i.e. simple file on the disk, not an
  /// serial port, device, printer or other virtual file), function returns
  /// \c true
  ///
  bool is_file (const std::string &location);

  ///
  /// \brief Check if location points to the folder
  /// \param [in] location -- Path to check
  /// \return Return \c true if path is folder
  ///
  /// If path points to the folder, the function returns \c true
  ///
  bool is_directory (const std::string &location);
};

} // namespace gle

#endif // PATH_H
