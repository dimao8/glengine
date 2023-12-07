#include "sceneadapter.h"
#include "logger.h"

namespace gle
{

#define CHECK_BOOLEAN(x)                                                      \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_boolean ())                                                      \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect boolean but have "          \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

#define CHECK_NUMBER(x)                                                       \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_number ())                                                       \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect number but have "           \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

#define CHECK_STRING(x)                                                       \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_string ())                                                       \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect string but have "           \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

#define CHECK_NULL(x)                                                         \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_null ())                                                         \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect null but have "             \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

#define CHECK_OBJECT(x)                                                       \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_object ())                                                       \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect object but have "           \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

#define CHECK_ARRAY(x)                                                        \
  if (x == nullptr)                                                           \
    return false;                                                             \
  if (!x->is_array ())                                                        \
    {                                                                         \
      logger << SeverityLevel::warning << "Expect array but have "            \
             << std::endl                                                     \
             << *(x) << std::endl;                                            \
      m_scene_ptr->reset ();                                                  \
      return false;                                                           \
    }

/* *********************** SceneAdapter::SceneAdapter ********************** */

SceneAdapter::SceneAdapter (const std::shared_ptr<Scene> &scene)
{
  m_scene_ptr = scene;
}

/* ************************ SceneAdapter::from_gltf ************************ */

bool
SceneAdapter::from_gltf (const std::string &file_name)
{
  m_scene_ptr->m_info.clear ();

  litejson::JSONLoader loader (file_name);
  litejson::JSONValue *val = loader.get_root ();
  litejson::JSONValue *tmp;
  size_t n;

  if (val == nullptr)
    return false;

  // Extract info string and check for glTF2.0 format
  CHECK_OBJECT (val);
  val = val->as_object ("asset"); // Get asset object
  if (!val->is_valid ())
    {
      logger << SeverityLevel::warning << "There is no ``asset\'\' object"
             << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  CHECK_OBJECT (val);

  val = val->as_object ("version"); // version
  CHECK_STRING (val);
  m_scene_ptr->m_info += "version = ";
  m_scene_ptr->m_info += val->as_string ();
  m_scene_ptr->m_info += "\n";
  val = val->parent ();

  tmp = val->as_object ("copyright"); // copyright
  if (tmp != nullptr)
    {
      if (tmp->is_string ())
        {
          m_scene_ptr->m_info += "copyright = ";
          m_scene_ptr->m_info += tmp->as_string ();
          m_scene_ptr->m_info += "\n";
        }
    }

  tmp = val->as_object ("generator"); // generator
  if (tmp != nullptr)
    {
      if (tmp->is_string ())
        {
          m_scene_ptr->m_info += "generator = ";
          m_scene_ptr->m_info += tmp->as_string ();
          m_scene_ptr->m_info += "\n";
        }
    }

  tmp = val->as_object ("minVersion"); // minVersion
  if (tmp != nullptr)
    {
      if (tmp->is_string ())
        {
          m_scene_ptr->m_info += "minVersion = ";
          m_scene_ptr->m_info += tmp->as_string ();
          m_scene_ptr->m_info += "\n";
        }
    }

  // Extract buffers
  std::vector<gltf_buffer_desc_t> buffers;
  gltf_buffer_desc_t buf;
  val = loader.get_root ();
  val = val->as_object ("buffers");
  CHECK_ARRAY (val);

  n = val->array_size ();
  if (n == 0)
    {
      logger << SeverityLevel::warning << "``buffers\'\' array has no elements"
             << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  for (auto i = 0; i < n; i++)
    {
      val = val->as_array (i);
      CHECK_OBJECT (val);
      val = val->as_object ("uri"); // uri
      CHECK_STRING (val);
      buf.uri = val->as_string ();
      val = val->parent ();

      val = val->as_object ("byteLength"); // byteLength
      CHECK_NUMBER (val);
      buf.byte_length = val->as_integer ();
      val = val->parent ();

      tmp = val->as_object ("name"); // name (if exist)
      if (tmp != nullptr)
        {
          if (tmp->is_string ())
            buf.name = tmp->as_string ();
          else
            buf.name = "<unnamed>";
        }
      else
        buf.name = "<unnamed>";

      buffers.push_back (buf);

      logger << SeverityLevel::info << "Buffer #" << i << " found."
             << std::endl;
      logger << "\turi = " << buf.uri << std::endl;
      logger << "\tbyteLength = " << buf.byte_length << std::endl;
      logger << "\tname = " << buf.name << std::endl;
    }

  // Extract buffer views
  std::vector<gltf_buffer_view_desc_t> buffer_views;
  gltf_buffer_view_desc_t buffer_view;
  val = loader.get_root ();
  val = val->as_object ("bufferViews");
  CHECK_ARRAY (val);
  n = val->array_size ();
  if (n == 0)
    {
      logger << SeverityLevel::warning
             << "``bufferViews\'\' array has no elements" << std::endl;
      m_scene_ptr->reset ();
      return false;
    }

  for (auto i = 0; i < n; i++)
    {
      val = val->as_array (i);
      CHECK_OBJECT (val);
      val = val->as_object ("buffer"); // index
      CHECK_NUMBER (val);
      buffer_view.buffer_index = val->as_integer ();
      val = val->parent ();

      val = val->as_object ("byteLength"); // byteLength
      CHECK_NUMBER (val);
      buffer_view.byte_length = val->as_integer ();
      val = val->parent ();

      tmp = val->as_object ("byteOffset"); // byteOffset
      if (tmp != nullptr)
        {
          if (tmp->is_number ())
            buffer_view.byte_offset = tmp->as_integer ();
          else
            buffer_view.byte_offset = 0;
        }
      else
        buffer_view.byte_offset = 0;

      tmp = val->as_object ("byteStride"); // byteStride
      if (tmp != nullptr)
        {
          if (tmp->is_number ())
            buffer_view.byte_stride = tmp->as_integer ();
          else
            buffer_view.byte_stride = 0;
        }
      else
        buffer_view.byte_stride = 0;

      val = val->as_object ("target"); // target
      CHECK_NUMBER (val);
      buffer_view.target = val->as_integer ();
      if (buffer_view.target != GL_ARRAY_BUFFER
          && buffer_view.target != GL_ELEMENT_ARRAY_BUFFER)
        {
          logger << SeverityLevel::warning
                 << "``bufferViews[n].target\'\' can be only GL_ARRAY_BUFFER "
                    "(34962) or GL_ELEMENT_ARRAY_BUFFER (34963)"
                 << std::endl;
          m_scene_ptr->reset ();
          return false;
        }
      val = val->parent ();

      tmp = val->as_object ("name"); // name (if exist)
      if (tmp != nullptr)
        {
          if (tmp->is_string ())
            buffer_view.name = tmp->as_string ();
          else
            buffer_view.name = "<unnamed>";

          buffer_views.push_back (buffer_view);
        }
      val = val->parent ();

      logger << SeverityLevel::info << "Buffer View #" << i << " found."
             << std::endl;
      logger << "\tbuffer = " << buffer_view.buffer_index << std::endl;
      logger << "\tbyteLength = " << buffer_view.byte_length << std::endl;
      logger << "\tbyteOffset = " << buffer_view.byte_offset << std::endl;
      logger << "\tbyteStride = " << buffer_view.byte_stride << std::endl;
      logger << "\ttarget = ";
      switch (buffer_view.target)
        {

        case GL_ARRAY_BUFFER:
          logger << "GL_ARRAY_BUFFER";
          break;

        case GL_ELEMENT_ARRAY_BUFFER:
          logger << "GL_ELEMENT_ARRAY_BUFFER";
          break;
        }
      logger << std::endl;
      logger << "\tname = " << buffer_view.name << std::endl;
    }

  // Extract accessors

  return true;
}

}