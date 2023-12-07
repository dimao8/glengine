#ifndef SCENEADAPTER_H
#define SCENEADAPTER_H

#include "scene.h"
#include "opengl.h"

#include <litejson.h>
#include <memory>
#include <string>

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
    GLenum target;
    std::string name;
  };

  struct gltf_accessor_sparse_desc_t
  {

  };

  struct gltf_accessor_desc_t
  {
    int buffer_view;
    int byte_offset;
    GLenum component_type;
    bool normalized;
    int count;
    std::string type;
    int max;
    int min;
    gltf_accessor_sparse_desc_t sparse;
    std::string name;
  };

  std::shared_ptr<Scene> m_scene_ptr;

public:

  SceneAdapter () = delete;
  SceneAdapter (const std::shared_ptr<Scene> & scene);

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
  bool from_gltf (const std::string & file_name);

};

}

#endif // SCENEADAPTER_H
