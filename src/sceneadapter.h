#ifndef SCENEADAPTER_H
#define SCENEADAPTER_H

#include "opengl.h"
#include "scene.h"

#include <litejson.h>
#include <memory>
#include <string>
#include <vector>

namespace gle
{

class SceneAdapter
{

private:
  struct gltf_buffer_desc_t
  {
    std::string uri;
    int byte_length;
    std::string name;
  };

  struct gltf_buffer_view_desc_t
  {
    int buffer_index;
    int byte_offset;
    int byte_length;
    int byte_stride;
    int target;
    std::string name;
  };

  struct gltf_accessor_sparce_index_desc_t
  {
    int buffer_view;
    int byte_offset;
    int component_type;
  };

  struct gltf_accessor_sparce_value_desc_t
  {
    int buffer_view;
    int byte_offset;
  };

  struct gltf_accessor_sparse_desc_t
  {
    int count;
    gltf_accessor_sparce_index_desc_t indices;
    gltf_accessor_sparce_value_desc_t values;
  };

  struct gltf_accessor_desc_t
  {
    int buffer_view;
    int byte_offset;
    int component_type;
    bool normalized;
    int count;
    std::string type;
    std::vector<float> max;
    std::vector<float> min;
    gltf_accessor_sparse_desc_t sparse;
    std::string name;
  };

  struct gltf_attributes_desc_t
  {
    int position;
    int normal;
    int tangent;
    std::vector<int> texcoord;
    std::vector<int> color;
    std::vector<int> joints;
    std::vector<int> weights;
  };

  struct gltf_target_desc_t
  {
    int position;
    int normal;
    int tangent;
    std::vector<int> texcoord;
    std::vector<int> color;
  };

  struct gltf_primitive_desc_t
  {
    gltf_attributes_desc_t attributes;
    int indices;
    int material;
    int mode;
    std::vector<gltf_target_desc_t> targets;
  };

  struct gltf_mesh_desc_t
  {
    std::vector<gltf_primitive_desc_t> primitives;
    std::vector<float> weights;
    std::string name;
  };

  struct gltf_image_desc_t
  {
    std::string uri;
    std::string mime_type;
    int buffer_view;
    std::string name;
  };

  struct gltf_samplers_desc_t
  {
    int min_filter;
    int mag_filter;
    int wrap_s;
    int wrap_t;
    std::string name;
  };

  struct gltf_textures_desc_t
  {
    int sampler;
    int source;
    std::string name;
  };

  struct gltf_textureinfo_desc_t
  {
    int index;
    int tex_coord;
  };

  struct gltf_pbr_metallic_roughness_desc_t
  {
    float base_color_factor[4];
    gltf_textureinfo_desc_t base_color_texture;
    float metallic_factor;
    float roughness_factor;
    gltf_textureinfo_desc_t metallic_roughness_texture;
  };

  struct gltf_normal_textureinfo_desc_t
  {
    int index;
    int tex_coord;
    float scale;
  };

  struct gltf_occlusion_desc_t
  {
    int index;
    int tex_coord;
    float strength;
  };

  struct gltf_material_desc_t
  {
    gltf_pbr_metallic_roughness_desc_t pbr_metallic_roughness;
    gltf_normal_textureinfo_desc_t normal_texture;
    gltf_occlusion_desc_t occlusion_texture;
    gltf_textureinfo_desc_t emissive_texture;
    float emissive_factor[3];
    std::string alpha_mode;
    float alpha_cutoff;
    bool double_sided;
  };

  struct gltf_orthographic_camera_desc_t
  {
    float xmag;
    float ymag;
    float zfar;
    float znear;
  };

  struct gltf_perspective_camera_desc_t
  {
    float aspect_ratio;
    float yfov;
    float zfar;
    float znear;
  };

  struct gltf_camera_desc_t
  {
    gltf_orthographic_camera_desc_t orthographic;
    gltf_perspective_camera_desc_t perspective;
    std::string type;
    std::string name;
  };

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
