#ifndef SCENEADAPTER_H
#define SCENEADAPTER_H

#include "opengl.h"
#include "scene.h"

#include <litejson.h>
#include <memory>
#include <string>
#include <vector>
#include <array>

namespace gle
{

class SceneAdapter
{

private:

  std::shared_ptr<Scene> m_scene_ptr;

  ///
  /// \brief Warning user in log file and reset scene
  /// \param [in] warning -- Warning message
  ///
  void warn_and_reset (const std::string &warning);

  ///
  /// \brief Check whether val is pointer to the boolean value
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to the boolean JSON value
  ///
  bool check_boolean (litejson::JSONValue *val);

  ///
  /// \brief Check whether val is pointer to the numeric value
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to the numeric JSON value
  ///
  bool check_number (litejson::JSONValue *val);

  ///
  /// \brief Check whether val is pointer to the string value
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to the string JSON value
  ///
  bool check_string (litejson::JSONValue *val);

  ///
  /// \brief Check whether val is null
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to null
  ///
  bool check_null (litejson::JSONValue *val);

  ///
  /// \brief Check whether val is object
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to object
  ///
  bool check_object (litejson::JSONValue *val);

  ///
  /// \brief Check whether val is array
  /// \param [in] val -- JSON value pointer
  /// \return Return true if val is point to an array
  ///
  bool check_array (litejson::JSONValue *val);

  ///
  /// \brief Extract integer value
  /// \param [out] i -- Integer value
  /// \param [in] val -- JSON value
  /// \return Return true if value is valid integer
  ///
  bool extract_int (int &i, litejson::JSONValue *val);

  ///
  /// \brief Extract integer value with default
  /// \param [out] i  -- Integer value
  /// \param [in] val -- JSON value
  /// \param [in] def -- Default value
  /// \return Return true if value is valid integer or empty
  ///
  bool extract_int (int &i, litejson::JSONValue *val, int def);

  ///
  /// \brief Extract float value
  /// \param [out] f -- Integer value
  /// \param [in] val -- JSON value
  /// \return Return true if value is valid float
  ///
  bool extract_float (float &f, litejson::JSONValue *val);

  ///
  /// \brief Extract float value with default
  /// \param [out] f  -- Integer value
  /// \param [in] val -- JSON value
  /// \param [in] def -- Default value
  /// \return Return true if value is valid float or empty
  ///
  bool extract_float (float &f, litejson::JSONValue *val, float def);

  ///
  /// \brief Extract string value
  /// \param [out] str -- String value
  /// \param [in] val  -- JSON value
  /// \return Return true if value is valid string
  ///
  bool extract_string (std::string &str, litejson::JSONValue *val);

  ///
  /// \brief Extract string value with default
  /// \param [out] str -- String value
  /// \param [in] val  -- JSON value
  /// \param [in] def  -- Default value
  /// \return Return true if value is valid string or empty
  ///
  bool extract_string (std::string &str, litejson::JSONValue *val,
                       const std::string &def);

  ///
  /// \brief Extract boolean value
  /// \param [out] str -- Boolean value
  /// \param [in] val  -- JSON value
  /// \return Return true if value is valid string
  ///
  bool extract_boolean (bool &b, litejson::JSONValue *val);

  ///
  /// \brief Extract boolean value with default
  /// \param [out] str -- Boolean value
  /// \param [in] val  -- JSON value
  /// \param [in] def  -- Default value
  /// \return Return true if value is valid string or empty
  ///
  bool extract_boolean (bool &b, litejson::JSONValue *val, bool def);

public:
  SceneAdapter () = delete;
  SceneAdapter (const std::shared_ptr<Scene> &scene);

  ///
  /// \brief Load scene from glTF2.0.
  /// \param [out] scene    -- Scene container
  /// \param [in] file_name -- Name of the glTF file.
  /// \return Return result of the loading.
  ///
  /// Load Scene object from glTF2.0 and fix some nonconformities with axis.
  /// If scene can not be loaded (some issues, wrong structure, blocked file)
  /// the adapter reset scene to empty state and return false.
  ///
  bool from_gltf (const std::string &file_name);
};

}

#endif // SCENEADAPTER_H
