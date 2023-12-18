#include "sceneadapter.h"
#include "logger.h"

#ifdef _WIN32
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

namespace gle
{

/* ********************** SceneAdapter::warn_and_reset ********************* */

void
SceneAdapter::warn_and_reset (const std::string &warning)
{
  logger << SeverityLevel::warning << warning << std::endl;
  m_scene_ptr->reset ();
}

/* ********************** SceneAdapter::check_boolean ********************** */

bool
SceneAdapter::check_boolean (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_boolean ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect boolean but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* *********************** SceneAdapter::check_number ********************** */

bool
SceneAdapter::check_number (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_number ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect number but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* *********************** SceneAdapter::check_string ********************** */

bool
SceneAdapter::check_string (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_string ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect string but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* ************************ SceneAdapter::check_null *********************** */

bool
SceneAdapter::check_null (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_null ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect null but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* *********************** SceneAdapter::check_object ********************** */

bool
SceneAdapter::check_object (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_object ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect object but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* *********************** SceneAdapter::check_array *********************** */

bool
SceneAdapter::check_array (litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  if (!val->is_array ())
    {
      logger << SeverityLevel::warning << "glTF error (" << val->line ()
             << ") Expect array but have " << std::endl
             << *val << std::endl;
      m_scene_ptr->reset ();
      return false;
    }
  return true;
}

/* *********************** SceneAdapter::extract_int *********************** */

bool
SceneAdapter::extract_int (int &i, litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  else if (val->is_number ())
    {
      i = val->as_integer ();
      return true;
    }
  else
    return false;
}

/* ******************* SceneAdapter::extract_int_default ******************* */

bool
SceneAdapter::extract_int (int &i, litejson::JSONValue *val, int def)
{
  if (val == nullptr)
    {
      i = def;
      return true;
    }
  else if (val->is_number ())
    {
      i = val->as_integer ();
      return true;
    }
  else
    return false;
}

/* ********************** SceneAdapter::extract_float ********************** */

bool
SceneAdapter::extract_float (float &f, litejson::JSONValue *val)
{
  if (val == nullptr)
    return false;
  else if (val->is_number ())
    {
      f = val->as_integer ();
      return true;
    }
  else
    return false;
}

/* ****************** SceneAdapter::extract_float_default ****************** */

bool
SceneAdapter::extract_float (float &f, litejson::JSONValue *val, float def)
{
  if (val == nullptr)
    {
      f = def;
      return true;
    }
  else if (val->is_number ())
    {
      f = val->as_integer ();
      return true;
    }
  else
    return false;
}

/* ********************* SceneAdapter::extract_string ********************** */

bool
SceneAdapter::extract_string (std::string &str, litejson::JSONValue *val)
{
  if (val == nullptr)
    {
      return false;
    }
  else if (val->is_string ())
    {
      str = val->as_string ();
      return true;
    }
  else
    return false;
}

/* ***************** SceneAdapter::extract_string_default ****************** */

bool
SceneAdapter::extract_string (std::string &str, litejson::JSONValue *val,
                              const std::string &def)
{
  if (val == nullptr)
    {
      str = def;
      return true;
    }
  else if (val->is_string ())
    {
      str = val->as_string ();
      return true;
    }
  else
    return false;
}

/* ********************* SceneAdapter::extract_boolean ********************* */

bool
SceneAdapter::extract_boolean (bool &b, litejson::JSONValue *val)
{
  if (val == nullptr)
    {
      return false;
    }
  else if (val->is_boolean ())
    {
      b = val->as_boolean ();
      return true;
    }
  else
    return false;
}

/* **************** SceneAdapter::extract_boolean_default ****************** */

bool
SceneAdapter::extract_boolean (bool &b, litejson::JSONValue *val, bool def)
{
  if (val == nullptr)
    {
      b = def;
      return true;
    }
  else if (val->is_boolean ())
    {
      b = val->as_boolean ();
      return true;
    }
  else
    return false;
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
  size_t n, m;
  std::string str;
  int integer;

  if (val == nullptr)
    return false;

  // Extract info string and check for glTF2.0 format
  if (!check_object (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  val = val->as_object ("asset"); // Get asset object
  if (!check_object (val))
    {
      m_scene_ptr->reset ();
      return false;
    }

  tmp = val->as_object ("version"); // version
  if (!extract_string (str, tmp))
    {
      warn_and_reset ("glTF 2.0 file must have asset.version string field");
      return false;
    }
  m_scene_ptr->m_info.push_back (std::string ("version = ") + str);

  tmp = val->as_object ("copyright"); // copyright
  if (extract_string (str, tmp))
    m_scene_ptr->m_info.push_back (std::string ("copyright = ") + str);

  tmp = val->as_object ("generator"); // generator
  if (extract_string (str, tmp))
    m_scene_ptr->m_info.push_back (std::string ("generator = ") + str);

  tmp = val->as_object ("minVersion"); // minVersion
  if (extract_string (str, tmp))
    m_scene_ptr->m_info.push_back (std::string ("minVersion = ") + str);

  // Extract buffers
  std::vector<gltf_buffer_desc_t> buffers;
  gltf_buffer_desc_t buf;
  val = loader.get_root ();
  val = val->as_object ("buffers");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return true;
    }

  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``buffers\'\' array has no elements");
      return false;
    }
  for (auto i = 0; i < n; i++)
    {
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      // TODO : Check for base64 data if no buffer uri is exists
      tmp = val->as_object ("uri"); // uri
      if (!extract_string (buf.uri, tmp))
        {
          warn_and_reset (
              "Use of builtin binary data is not supported for now");
          return false;
        }

      tmp = val->as_object ("byteLength"); // byteLength
      if (!extract_int (buf.byte_length, tmp))
        {
          warn_and_reset ("buffers[n].byteLength must be a number");
          return false;
        }

      tmp = val->as_object ("name"); // name
      if (!extract_string (buf.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("buffers[n].name must be a string");
          return false;
        }

      buffers.push_back (buf);

      // Print data
      logger << SeverityLevel::info << "Buffer #" << i << " found."
             << std::endl;
      if (!buf.uri.empty ())
        logger << "\turi = " << buf.uri << std::endl;
      logger << "\tbyteLength = " << buf.byte_length << std::endl;
      logger << "\tname = " << buf.name << std::endl;
    }

  // Extract buffer views
  std::vector<gltf_buffer_view_desc_t> buffer_views;
  gltf_buffer_view_desc_t buffer_view;
  val = loader.get_root ();
  val = val->as_object ("bufferViews");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``bufferViews\'\' array has no elements");
      return false;
    }

  for (auto i = 0; i < n; i++)
    {
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      tmp = val->as_object ("buffer"); // index
      if (!extract_int (buffer_view.buffer_index, tmp))
        {
          warn_and_reset ("bufferViews[n].buffer must be a number");
          return false;
        }

      tmp = val->as_object ("byteLength"); // byteLength
      if (!extract_int (buffer_view.byte_length, tmp))
        {
          warn_and_reset ("bufferViews[n].byteLength must be a number");
          return false;
        }

      tmp = val->as_object ("byteOffset"); // byteOffset
      if (!extract_int (buffer_view.byte_offset, tmp, 0))
        {
          warn_and_reset ("bufferViews[n].byteOffset must be a number");
          return false;
        }

      tmp = val->as_object ("byteStride"); // byteStride
      if (!extract_int (buffer_view.byte_stride, tmp, -1))
        {
          warn_and_reset ("bufferViews[n].byteStride must be a number");
          return false;
        }

      tmp = val->as_object ("target"); // target
      if (!extract_int (buffer_view.target, tmp, -1))
        {
          warn_and_reset ("bufferViews[n].target must be numeric value");
          return false;
        }
      if (buffer_view.target >= 0 && buffer_view.target != GL_ARRAY_BUFFER
          && buffer_view.target != GL_ELEMENT_ARRAY_BUFFER)
        {
          warn_and_reset (
              "``bufferViews[n].target\'\' can be only GL_ARRAY_BUFFER "
              "(34962), GL_ELEMENT_ARRAY_BUFFER (34963) or negative if no "
              "target presents");
          return false;
        }

      tmp = val->as_object ("name"); // name
      if (!extract_string (buffer_view.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("bufferViews[n].name must be a string");
          return false;
        }
      buffer_views.push_back (buffer_view);
      val = val->parent ();

      // Print data
      logger << SeverityLevel::info << "Buffer View #" << i << " found."
             << std::endl;
      logger << "\tbuffer = " << buffer_view.buffer_index << std::endl;
      logger << "\tbyteLength = " << buffer_view.byte_length << std::endl;
      logger << "\tbyteOffset = " << buffer_view.byte_offset << std::endl;
      if (buffer_view.byte_stride >= 0)
        logger << "\tbyteStride = " << buffer_view.byte_stride << std::endl;
      if (buffer_view.target > 0)
        {
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
        }
      logger << "\tname = " << buffer_view.name << std::endl;
    }

  // Extract accessors
  std::vector<gltf_accessor_desc_t> accessors;
  gltf_accessor_desc_t accessor;
  val = loader.get_root ();
  val = val->as_object ("accessors");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``accessors\'\' array has no elements");
      return false;
    }

  for (auto i = 0; i < n; i++)
    {
      accessor.sparse.count = 0;

      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      // TODO : Change checking to optional when ``sparse'' section will be
      // used
      tmp = val->as_object ("bufferView"); // bufferView
      if (!extract_int (accessor.buffer_view, tmp))
        {
          logger << SeverityLevel::warning
                 << "bufferView must exist because of missing ``sparse'' "
                    "section in this version"
                 << std::endl;
          m_scene_ptr->reset ();
          return false;
        }

      tmp = val->as_object ("byteOffset"); // byteOffset
      if (!extract_int (accessor.byte_offset, tmp, 0))
        {
          warn_and_reset ("accessors[n].byteOffset must be a number");
          return false;
        }

      tmp = val->as_object ("componentType"); // componentType
      if (!extract_int (accessor.component_type, tmp))
        {
          warn_and_reset ("accessors[n].componentType must be a number");
          return false;
        }
      if (accessor.component_type != GL_BYTE
          && accessor.component_type != GL_UNSIGNED_BYTE
          && accessor.component_type != GL_SHORT
          && accessor.component_type != GL_UNSIGNED_SHORT
          && accessor.component_type != GL_UNSIGNED_INT
          && accessor.component_type != GL_FLOAT)
        {
          warn_and_reset (
              "accessors[n].componentType can be only GL_BYTE (5120), "
              "GL_UNSIGNED_BYTE (5121), GL_SHORT (5122), GL_UNSIGNED_SHORT "
              "(5123), GL_UNSIGNED_INT (5125) or GL_FLOAT (5126)");
          return false;
        }

      tmp = val->as_object ("normalized"); // normalized
      if (!extract_boolean (accessor.normalized, tmp, false))
        {
          warn_and_reset ("accessors[n].normalized must be a boolean");
          return false;
        }

      tmp = val->as_object ("count"); // count
      if (!extract_int (accessor.count, tmp))
        {
          warn_and_reset ("accessors[n].count must be numeric value");
          return false;
        }

      tmp = val->as_object ("type"); // type
      if (!extract_string (accessor.type, tmp))
        {
          warn_and_reset ("accessors[n].type must be a string");
          return false;
        }
      if (accessor.type != "SCALAR" && accessor.type != "VEC2"
          && accessor.type != "VEC3" && accessor.type != "VEC4"
          && accessor.type != "MAT2" && accessor.type != "MAT3"
          && accessor.type != "MAT4")
        {
          warn_and_reset (
              "accessors[n].type can be only ``SCALAR\'\', ``VEC2\'\', "
              "``VEC3\'\', ``VEC4\'\', ``MAT2\'\', ``MAT3\'\' or ``MAT4\'\'");
          return false;
        }
      tmp = val->as_object ("min"); // min
      if (tmp != nullptr)
        {
          if (tmp->is_array ())
            {
              m = tmp->array_size ();
              for (auto j = 0; j < m; j++)
                {
                  tmp = tmp->as_array (j);
                  if (tmp->is_number ())
                    {
                      accessor.min.push_back (tmp->as_float ());
                      tmp = tmp->parent ();
                    }
                  else
                    {
                      warn_and_reset (
                          "accessors[n].min array can contain only numbers");
                      return false;
                    }
                }
            }
          else
            {
              warn_and_reset ("accessors[n].min must be an array");
              return false;
            }
        }
      else
        {
          accessor.min.clear ();
        }
      tmp = val->as_object ("max"); // max
      if (tmp != nullptr)
        {
          if (tmp->is_array ())
            {
              m = tmp->array_size ();
              for (auto j = 0; j < m; j++)
                {
                  tmp = tmp->as_array (j);
                  if (tmp->is_number ())
                    {
                      accessor.max.push_back (tmp->as_float ());
                      tmp = tmp->parent ();
                    }
                  else
                    {
                      warn_and_reset (
                          "accessors[n].max array can contain only numbers");
                      return false;
                    }
                }
            }
          else
            {
              warn_and_reset ("accessors[n].max must be an array");
              return false;
            }
        }
      else
        {
          accessor.max.clear ();
        }
      // TODO : parse ``sparse'' field
      tmp = val->as_object ("name"); // name (if exist)
      if (!extract_string (accessor.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("accessors[n].name must be a string");
          return false;
        }
      accessors.push_back (accessor);
      val = val->parent ();

      // Print data
      logger << SeverityLevel::info << "Accessor #" << i << " found."
             << std::endl;
      logger << "\tbufferView = " << accessors[i].buffer_view << std::endl;
      logger << "\tbyteOffset = " << accessors[i].byte_offset << std::endl;
      logger << "\tcomponentType = ";
      switch (accessors[i].component_type)
        {
        case GL_BYTE:
          logger << "GL_BYTE";
          break;

        case GL_UNSIGNED_BYTE:
          logger << "GL_UNSIGNED_BYTE";
          break;

        case GL_SHORT:
          logger << "GL_SHORT";
          break;

        case GL_UNSIGNED_SHORT:
          logger << "GL_UNSIGNED_SHORT";
          break;

        case GL_UNSIGNED_INT:
          logger << "GL_UNSIGNED_INT";
          break;

        case GL_FLOAT:
          logger << "GL_FLOAT";
          break;
        }
      logger << std::endl;
      logger << "\tnormalized = "
             << (accessors[i].normalized ? "true" : "false") << std::endl;
      logger << "\tcount = " << accessors[i].count << std::endl;
      if (!accessors[i].min.empty ())
        {
          logger << "\tmin = [";
          for (auto j = 0; j < accessors[i].min.size (); j++)
            {
              logger << accessors[i].min[j];
              if (j != accessors[i].min.size () - 1)
                logger << ", ";
            }
          logger << "]" << std::endl;
        }
      if (!accessors[i].max.empty ())
        {
          logger << "\tmax = [";
          for (auto j = 0; j < accessors[i].max.size (); j++)
            {
              logger << accessors[i].max[j];
              if (j != accessors[i].max.size () - 1)
                logger << ", ";
            }
          logger << "]" << std::endl;
        }
      if (accessors[i].sparse.count > 0)
        {
          logger << "\tsparce =" << std::endl;
          logger << "\t\tcount = " << accessors[i].sparse.count << std::endl;
          logger << "\t\tindices = " << std::endl;
          if (accessors[i].buffer_view >= 0)
            logger << "\t\t\tbufferView = "
                   << accessors[i].sparse.indices.buffer_view << std::endl;
          logger << "\t\t\tbyteOffset = "
                 << accessors[i].sparse.indices.byte_offset << std::endl;
          logger << "\t\t\tcomponentType = ";
          switch (accessors[i].sparse.indices.component_type)
            {
            case GL_UNSIGNED_BYTE:
              logger << "GL_UNSIGNED_BYTE";
              break;

            case GL_UNSIGNED_SHORT:
              logger << "GL_UNSIGNED_SHORT";
              break;

            case GL_UNSIGNED_INT:
              logger << "GL_UNSIGNED_INT";
              break;
            }
          logger << std::endl;
          logger << "\t\tvalues = " << std::endl;
          logger << "\t\t\tbufferView = "
                 << accessors[i].sparse.values.buffer_view << std::endl;
          logger << "\t\t\tbyteOffset = "
                 << accessors[i].sparse.values.byte_offset << std::endl;
        }
      logger << "\ttype = " << accessors[i].type << std::endl;
      logger << "\tname = " << accessors[i].name << std::endl;
    }

  // Extract meshes
  std::vector<gltf_mesh_desc_t> meshes;
  gltf_mesh_desc_t mesh;
  gltf_primitive_desc_t primitive;
  // gltf_target_desc_t target;

  val = loader.get_root ();
  val = val->as_object ("meshes");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``meshes\'\' array has no elements");
      return false;
    }

  for (auto i = 0; i < n; i++)
    {
      primitive.attributes.color.clear ();
      primitive.attributes.texcoord.clear ();
      primitive.attributes.joints.clear ();
      primitive.attributes.weights.clear ();
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      val = val->as_object ("primitives");
      if (!check_array (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      mesh.primitives.clear ();
      for (auto j = 0; j < val->array_size (); j++)
        {
          val = val->as_array (j);
          if (!check_object (val))
            {
              m_scene_ptr->reset ();
              return false;
            }
          val = val->as_object ("attributes");
          if (!check_object (val))
            {
              m_scene_ptr->reset ();
              return false;
            }
          tmp = val->as_object ("POSITION"); // POSITION
          if (!extract_int (primitive.attributes.position, tmp, -1))
            {
              warn_and_reset ("``meshes[n].primitives[m].attributes."
                              "POSITION\'\' must be a number");
              return false;
            }

          tmp = val->as_object ("NORMAL"); // NORMAL
          if (!extract_int (primitive.attributes.normal, tmp, -1))
            {
              warn_and_reset ("``meshes[n].primitives[m].attributes."
                              "NORMAL\'\' must be a number");
              return false;
            }

          tmp = val->as_object ("TANGENT"); // TANGENT
          if (!extract_int (primitive.attributes.tangent, tmp, -1))
            {
              warn_and_reset ("``meshes[n].primitives[m].attributes."
                              "TANGENT\'\' must be a number");
              return false;
            }

          for (auto k = 0; k < 16; k++) // TEXCOORD_n
            {
              str = "TEXCOORD_";
              str += std::to_string (k);
              tmp = val->as_object (str);
              if (!extract_int (integer, tmp, -1))
                break;
              else
                primitive.attributes.texcoord.push_back (integer);
            }

          for (auto k = 0; k < 16; k++) // COLOR_n
            {
              str = "COLOR_";
              str += std::to_string (k);
              tmp = val->as_object (str);
              if (!extract_int (integer, tmp, -1))
                break;
              else
                primitive.attributes.color.push_back (integer);
            }

          for (auto k = 0; k < 16; k++) // JOINTS_n
            {
              str = "JOINTS_";
              str += std::to_string (k);
              tmp = val->as_object (str);
              if (!extract_int (integer, tmp, -1))
                break;
              else
                primitive.attributes.joints.push_back (integer);
            }

          for (auto k = 0; k < 16; k++) // WEIGHTS_n
            {
              str = "WEIGHTS_";
              str += std::to_string (k);
              tmp = val->as_object (str);
              if (!extract_int (integer, tmp, -1))
                break;
              else
                primitive.attributes.weights.push_back (integer);
            }
          val = val->parent ();

          tmp = val->as_object ("indices"); // indices
          if (!extract_int (primitive.indices, tmp, -1))
            {
              warn_and_reset ("``meshes[n].primitives[m].indices\'\' "
                              "must be a number");
              return false;
            }

          tmp = val->as_object ("material"); // material
          if (!extract_int (primitive.material, tmp, -1))
            {
              warn_and_reset ("``meshes[n].primitives[m]."
                              "material\'\' must be a number");
              return false;
            }

          tmp = val->as_object ("mode"); // mode
          if (!extract_int (primitive.mode, tmp, GL_TRIANGLES))
            {
              warn_and_reset ("``meshes[n].primitives[m]."
                              "mode\'\' must be a number");
              return false;
            }
          if (primitive.mode != GL_POINTS && primitive.mode != GL_LINES
              && primitive.mode != GL_LINE_STRIP
              && primitive.mode != GL_LINE_LOOP
              && primitive.mode != GL_TRIANGLES
              && primitive.mode != GL_TRIANGLE_STRIP
              && primitive.mode != GL_TRIANGLE_FAN)
            {
              warn_and_reset ("``meshes[n].primitives[m].mode\'\' can be only "
                              "GL_POINTS (0), GL_LINES (1), GL_LINE_LOOP(2), "
                              "GL_LINE_STRIP (3), GL_TRIANGLES (4), "
                              "GL_TRIANGLE_STRIP (5) or GL_TRIANGLE_FAN (6)");
              return false;
            }
          mesh.primitives.push_back (primitive);
          val = val->parent ();
        }

      val = val->parent ();
      val = val->parent ();
      meshes.push_back (mesh);

      // Print data
      logger << SeverityLevel::info << "Mesh #" << i << " found." << std::endl;
      logger << "\tprimitives =" << std::endl;
      for (int j = 0; j < meshes[i].primitives.size (); j++)
        {
          logger << "\t\tattributes =" << std::endl;
          if (meshes[i].primitives[j].attributes.position >= 0)
            logger << "\t\t\tPOSITION = "
                   << meshes[i].primitives[j].attributes.position << std::endl;
          if (meshes[i].primitives[j].attributes.normal >= 0)
            logger << "\t\t\tNORMAL = "
                   << meshes[i].primitives[j].attributes.normal << std::endl;
          if (meshes[i].primitives[j].attributes.tangent >= 0)
            logger << "\t\t\tTANGENT = "
                   << meshes[i].primitives[j].attributes.tangent << std::endl;
          if (meshes[i].primitives[j].attributes.texcoord.size () > 0)
            {
              for (auto k = 0;
                   k < meshes[i].primitives[j].attributes.texcoord.size ();
                   k++)
                {
                  if (meshes[i].primitives[j].attributes.texcoord[k] >= 0)
                    {
                      logger << "\t\t\tTEXCOORD_" << k << " = "
                             << meshes[i].primitives[j].attributes.texcoord[k]
                             << std::endl;
                    }
                }
            }
          if (meshes[i].primitives[j].attributes.color.size () > 0)
            {
              for (auto k = 0;
                   k < meshes[i].primitives[j].attributes.color.size (); k++)
                {
                  if (meshes[i].primitives[j].attributes.color[k] >= 0)
                    {
                      logger << "\t\t\tCOLOR_" << k << " = "
                             << meshes[i].primitives[j].attributes.color[k]
                             << std::endl;
                    }
                }
            }
          if (meshes[i].primitives[j].attributes.joints.size () > 0)
            {
              for (auto k = 0;
                   k < meshes[i].primitives[j].attributes.joints.size (); k++)
                {
                  if (meshes[i].primitives[j].attributes.joints[k] >= 0)
                    {
                      logger << "\t\t\tJOINTS_" << k << " = "
                             << meshes[i].primitives[j].attributes.joints[k]
                             << std::endl;
                    }
                }
            }
          if (meshes[i].primitives[j].attributes.weights.size () > 0)
            {
              for (auto k = 0;
                   k < meshes[i].primitives[j].attributes.weights.size (); k++)
                {
                  if (meshes[i].primitives[j].attributes.weights[k] >= 0)
                    {
                      logger << "\t\t\tWEIGHTS_" << k << " = "
                             << meshes[i].primitives[j].attributes.weights[k]
                             << std::endl;
                    }
                }
            }
          if (meshes[i].primitives[j].indices >= 0)
            logger << "\t\tindices = " << meshes[i].primitives[j].indices
                   << std::endl;
          if (meshes[i].primitives[j].material >= 0)
            logger << "\t\tmaterial = " << meshes[i].primitives[j].material
                   << std::endl;
          logger << "\t\tmode = ";
          switch (meshes[i].primitives[j].mode)
            {
            case GL_POINTS:
              logger << "GL_POINTS";
              break;

            case GL_LINES:
              logger << "GL_LINES";
              break;

            case GL_LINE_LOOP:
              logger << "GL_LINE_LOOP";
              break;

            case GL_LINE_STRIP:
              logger << "GL_LINE_STRIP";
              break;

            case GL_TRIANGLES:
              logger << "GL_TRIANGLES";
              break;

            case GL_TRIANGLE_STRIP:
              logger << "GL_TRIANGLE_STRIP";
              break;

            case GL_TRIANGLE_FAN:
              logger << "GL_TRIANGLE_FAN";
              break;
            }
          logger << std::endl;

          if (meshes[i].primitives[j].targets.size () > 0)
            {
              logger << "\t\ttargets = [";
              logger << std::endl;
              for (auto k = 0; k < meshes[i].primitives[j].targets.size ();
                   k++)
                {
                  if (meshes[i].primitives[j].targets[k].position >= 0)
                    logger << "\t\t\tPOSITION = "
                           << meshes[i].primitives[j].targets[k].position
                           << std::endl;
                  if (meshes[i].primitives[j].targets[k].normal >= 0)
                    logger << "\t\t\tNORMAL = "
                           << meshes[i].primitives[j].targets[k].normal
                           << std::endl;
                  if (meshes[i].primitives[j].targets[k].tangent >= 0)
                    logger << "\t\t\tTANGENT = "
                           << meshes[i].primitives[j].targets[k].tangent
                           << std::endl;
                  if (meshes[i].primitives[j].targets[k].texcoord.size () > 0)
                    {
                      for (auto k = 0; k < meshes[i]
                                               .primitives[j]
                                               .targets[k]
                                               .texcoord.size ();
                           k++)
                        {
                          if (meshes[i].primitives[j].targets[k].texcoord[k]
                              >= 0)
                            {
                              logger << "\t\t\tTEXCOORD_" << k << " = "
                                     << meshes[i]
                                            .primitives[j]
                                            .targets[k]
                                            .texcoord[k]
                                     << std::endl;
                            }
                        }
                    }
                  if (meshes[i].primitives[j].targets[k].color.size () > 0)
                    {
                      for (auto k = 0;
                           k
                           < meshes[i].primitives[j].targets[k].color.size ();
                           k++)
                        {
                          if (meshes[i].primitives[j].targets[k].color[k] >= 0)
                            {
                              logger << "\t\t\tCOLOR_" << k << " = "
                                     << meshes[i]
                                            .primitives[j]
                                            .targets[k]
                                            .color[k]
                                     << std::endl;
                            }
                        }
                    }
                }
              logger << "]" << std::endl;
            }
        }
      if (meshes[i].weights.size () > 0)
        {
          logger << "\tweights = [";
          for (int j = 0; j < meshes[i].weights.size (); j++)
            {
              logger << meshes[i].weights[j];
              if (j != meshes[i].weights.size () - 1)
                logger << ", ";
            }
          logger << "]" << std::endl;
        }
    }

  // Extract images
  std::vector<gltf_image_desc_t> images;
  gltf_image_desc_t image;
  val = loader.get_root ();
  val = val->as_object ("images");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``images\'\' array has no elements");
      return false;
    }

  for (int i = 0; i < n; i++)
    {
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      tmp = val->as_object ("uri"); // uri
      if (!extract_string (image.uri, tmp, ""))
        {
          warn_and_reset ("``images[n].uri\'\' must be a string");
          return false;
        }

      tmp = val->as_object ("bufferView");
      if (!extract_int (image.buffer_view, tmp, -1))
        {
          warn_and_reset ("``images\'\' can not contain both "
                          "``uri\'\' and ``bufferView\'\' field");
          return false;
        }
      if (image.uri.empty () == (image.buffer_view < 0))
        {
          warn_and_reset (
              "Only images[n].uri or non-negative images[n].bufferView can "
              "exist in a single image section, not both");
          return false;
        }
      if (image.buffer_view >= 0)
        {
          tmp = val->as_object ("mimeType");
          if (!extract_string (image.mime_type, tmp))
            {
              warn_and_reset ("There must be a valid mime type, if "
                              "images[n].bufferView is non-negative");
              return false;
            }
        }
      else
        {
          tmp = val->as_object ("mimeType");
          if (!extract_string (image.mime_type, tmp, ""))
            {
              warn_and_reset ("There must be a valid mime type, if "
                              "images[n].bufferView is non-negative");
              return false;
            }
        }

      tmp = val->as_object ("name"); // name (if exist)
      if (!extract_string (image.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("image.name must be a string");
          return false;
        }
      val = val->parent ();
      images.push_back (image);

      // Print data
      logger << SeverityLevel::info << "Image #" << i << " found."
             << std::endl;
      if (!images[i].uri.empty ())
        logger << "\turi = " << images[i].uri << std::endl;
      if (!images[i].mime_type.empty ())
        logger << "\tmimeType = " << images[i].mime_type << std::endl;
      if (images[i].buffer_view >= 0)
        logger << "\tbufferView = " << images[i].buffer_view << std::endl;
      logger << "\tname = " << images[i].name << std::endl;
    }

  // Extract samplers
  std::vector<gltf_samplers_desc_t> samplers;
  gltf_samplers_desc_t sampler;
  val = loader.get_root ();
  val = val->as_object ("samplers");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``samplers\'\' array has no elements");
      return false;
    }

  for (int i = 0; i < n; i++)
    {
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      tmp = val->as_object ("minFilter"); // minFilter
      if (!extract_int (sampler.min_filter, tmp, -1))
        {
          warn_and_reset ("``samplers[n].minFilter\'\' must be a number");
          return false;
        }
      if (sampler.min_filter >= 0 && sampler.min_filter != GL_NEAREST
          && sampler.min_filter != GL_LINEAR)
        {
          // TODO : Add MIPMAP
          warn_and_reset ("``samplers[n].minFilter\'\' can be only GL_NEAREST "
                          "(9728) or GL_LINEAR (9729)");
          logger << SeverityLevel::info
                 << "MIPMAP filters is not supported yet" << std::endl;
          return false;
        }

      tmp = val->as_object ("magFilter"); // magFilter
      if (!extract_int (sampler.mag_filter, tmp, -1))
        {
          warn_and_reset ("``samplers[n].magFilter\'\' must be a number");
          return false;
        }
      if (sampler.mag_filter >= 0 && sampler.mag_filter != GL_NEAREST
          && sampler.mag_filter != GL_LINEAR)
        {
          warn_and_reset ("``samplers[n].magFilter\'\' can be only GL_NEAREST "
                          "(9728) or GL_LINEAR (9729)");
          return false;
        }

      tmp = val->as_object ("wrapS"); // wrapS
      if (!extract_int (sampler.wrap_s, tmp, GL_REPEAT))
        {
          warn_and_reset ("``samplers[n].wrapS\'\' must be a number");
          return false;
        }
      if (sampler.wrap_s != GL_CLAMP_TO_EDGE
          && sampler.wrap_s != GL_MIRRORED_REPEAT
          && sampler.wrap_s != GL_REPEAT)
        {
          warn_and_reset (
              "``samplers[n].wrapS\'\' can be only GL_CLAMP_TO_EDGE (33071), "
              "GL_MIRRRORED_REPEAT (33648) or GL_REPEAT (10497)");
          return false;
        }

      tmp = val->as_object ("wrapT"); // wrapT
      if (!extract_int (sampler.wrap_t, tmp, GL_REPEAT))
        {
          warn_and_reset ("``samplers[n].wrapT\'\' must be a number");
          return false;
        }
      if (sampler.wrap_t != GL_CLAMP_TO_EDGE
          && sampler.wrap_t != GL_MIRRORED_REPEAT
          && sampler.wrap_t != GL_REPEAT)
        {
          warn_and_reset (
              "``samplers[n].wrapT\'\' can be only GL_CLAMP_TO_EDGE (33071), "
              "GL_MIRRRORED_REPEAT (33648) or GL_REPEAT (10497)");
          return false;
        }

      tmp = val->as_object ("name"); // name
      if (!extract_string (sampler.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("``samplers[n].name\'\' must be a string");
          return false;
        }

      val = val->parent ();
      samplers.push_back (sampler);

      // Print data
      logger << SeverityLevel::info << "Sampler #" << i << " found."
             << std::endl;
      if (samplers[i].min_filter >= 0)
        {
          logger << "\tminFilter = ";
          switch (samplers[i].min_filter)
            {
            case GL_NEAREST:
              logger << "GL_NEAREST";
              break;

            case GL_LINEAR:
              logger << "GL_LINEAR";
              break;

            case GL_NEAREST_MIPMAP_NEAREST:
              logger << "GL_NEAREST_MIPMAP_NEAREST";
              break;

            case GL_LINEAR_MIPMAP_NEAREST:
              logger << "GL_LINEAR_MIPMAP_NEAREST";
              break;

            case GL_NEAREST_MIPMAP_LINEAR:
              logger << "GL_NEAREST_MIPMAP_LINEAR";
              break;

            case GL_LINEAR_MIPMAP_LINEAR:
              logger << "GL_LINEAR_MIPMAP_LINEAR";
              break;
            }
          logger << std::endl;
        }
      if (samplers[i].mag_filter >= 0)
        {
          logger << "\tmagFilter = ";
          switch (samplers[i].mag_filter)
            {
            case GL_NEAREST:
              logger << "GL_NEAREST";
              break;

            case GL_LINEAR:
              logger << "GL_LINEAR";
              break;
            }
          logger << std::endl;
        }
      logger << "\twrapS = ";
      switch (samplers[i].wrap_s)
        {
        case GL_CLAMP_TO_EDGE:
          logger << "GL_CLAMP_TO_EDGE";
          break;

        case GL_MIRRORED_REPEAT:
          logger << "GL_MIRRORED_REPEAT";
          break;

        case GL_REPEAT:
          logger << "GL_REPEAT";
          break;
        }
      logger << std::endl;
      logger << "\twrapT = ";
      switch (samplers[i].wrap_t)
        {
        case GL_CLAMP_TO_EDGE:
          logger << "GL_CLAMP_TO_EDGE";
          break;

        case GL_MIRRORED_REPEAT:
          logger << "GL_MIRRORED_REPEAT";
          break;

        case GL_REPEAT:
          logger << "GL_REPEAT";
          break;
        }
      logger << std::endl;
      if (!samplers[i].name.empty ())
        logger << "\tname = " << samplers[i].name << std::endl;
    }

  // Extract textures
  std::vector<gltf_textures_desc_t> textures;
  gltf_textures_desc_t texture;
  val = loader.get_root ();
  val = val->as_object ("textures");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``textures\'\' array has no elements");
      return false;
    }

  for (int i = 0; i < n; i++)
    {
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }
      tmp = val->as_object ("sampler"); // sampler
      if (!extract_int (texture.sampler, tmp, -1))
        {
          warn_and_reset ("``textures[n].sampler\'\' must be a number");
          return false;
        }

      tmp = val->as_object ("source"); // source
      if (!extract_int (texture.source, tmp, -1))
        {
          warn_and_reset ("``textures[n].source\'\' must be a number");
          return false;
        }

      tmp = val->as_object ("name"); // name
      if (!extract_string (texture.name, tmp, "<unnamed>"))
        {
          warn_and_reset ("``textures[n].name\'\' must be a string");
          return false;
        }

      val = val->parent ();
      textures.push_back (texture);

      // Print data
      logger << SeverityLevel::info << "Texture #" << i << " found."
             << std::endl;
      if (textures[i].sampler >= 0)
        logger << "\tsampler = " << textures[i].sampler << std::endl;
      if (textures[i].source >= 0)
        logger << "\tsource = " << textures[i].source << std::endl;
      if (!textures[i].name.empty ())
        logger << "\tname = " << textures[i].name << std::endl;
    }

  // Extract material
  std::vector<gltf_material_desc_t> materials;
  gltf_material_desc_t material;
  val = loader.get_root ();
  val = val->as_object ("materials");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``materials\'\' array has no elements");
      return false;
    }

  for (int i = 0; i < n; i++)
    {
      material.pbr_metallic_roughness.base_color_factor[0] = 1;
      material.pbr_metallic_roughness.base_color_factor[1] = 1;
      material.pbr_metallic_roughness.base_color_factor[2] = 1;
      material.pbr_metallic_roughness.base_color_factor[3] = 1;
      material.emissive_factor[0] = 0;
      material.emissive_factor[1] = 0;
      material.emissive_factor[2] = 0;
      material.pbr_metallic_roughness.base_color_texture.index = -1;
      material.pbr_metallic_roughness.metallic_roughness_texture.index = -1;
      material.normal_texture.index = -1;
      material.occlusion_texture.index = -1;
      material.emissive_texture.index = -1;

      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }

      tmp = val->as_object ("pbrMetallicRoughness");
      if (tmp != nullptr)
        {
          if (check_object (tmp))
            {
              val = tmp;
              tmp = val->as_object ("baseColorFactor"); // baseColorFactor
              if (tmp != nullptr)
                {
                  if (!tmp->is_array ())
                    {
                      warn_and_reset (
                          "materials[n].pbrMetallicRoughness.baseColorFactor "
                          "must be numeric array with 4 components");
                      return false;
                    }
                  else if (tmp->array_size () != 4)
                    {
                      warn_and_reset (
                          "materials[n].pbrMetallicRoughness.baseColorFactor "
                          "must be numeric array with 4 components");
                      return false;
                    }
                  else
                    {
                      for (auto j = 0; j < 4; j++)
                        {
                          if (!extract_float (material.pbr_metallic_roughness
                                                  .base_color_factor[i],
                                              tmp->as_array (i), 1))
                            {
                              warn_and_reset (
                                  "materials[n].pbrMetallicRoughness."
                                  "baseColorFactor must be numeric array with "
                                  "4 components");
                              return false;
                            }
                        }
                    }
                }

              tmp = val->as_object ("baseColorTexture");
              if (tmp != nullptr)
                {
                  val = tmp;
                  tmp = val->as_object ("index"); // index
                  if (!extract_int (material.pbr_metallic_roughness
                                        .base_color_texture.index,
                                    tmp))
                    {
                      warn_and_reset (
                          "``materials[n].pbrMetallicRoughness."
                          "baseColorTexture.index\'\' must be a number");
                      return false;
                    }

                  tmp = val->as_object ("texCoord"); // texCoord
                  if (!extract_int (material.pbr_metallic_roughness
                                        .base_color_texture.tex_coord,
                                    tmp, 0))
                    {
                      warn_and_reset (
                          "``materials[n].pbrMetallicRoughness."
                          "baseColorTexture.texCoord\'\' must be a number");
                      return false;
                    }

                  val = val->parent ();
                }

              tmp = val->as_object ("metallicFactor"); // metallicFactor
              if (!extract_float (
                      material.pbr_metallic_roughness.metallic_factor, tmp, 1))
                {
                  warn_and_reset ("``materials[n].pbrMetallicRoughness."
                                  "metallicFactor\'\' must be a number");
                  return false;
                }

              tmp = val->as_object ("roughnessFactor"); // roughnessFactor
              if (!extract_float (
                      material.pbr_metallic_roughness.roughness_factor, tmp,
                      1))
                {
                  warn_and_reset ("``materials[n].pbrMetallicRoughness."
                                  "roughnessFactor\'\' must be a number");
                  return false;
                }
              tmp = val->as_object ("metallicRoughnessTexture");
              if (check_object (tmp))
                {
                  val = tmp;
                  tmp = val->as_object ("index");
                  if (!extract_int (material.pbr_metallic_roughness
                                        .metallic_roughness_texture.index,
                                    tmp))
                    {
                      warn_and_reset ("``materials[n].pbrMetallicRoughness."
                                      "metallicRoughnessTexture.index\'\' "
                                      "must be a number");
                      return false;
                    }

                  tmp = val->as_object ("texCoord");
                  if (!extract_int (material.pbr_metallic_roughness
                                        .metallic_roughness_texture.tex_coord,
                                    tmp))
                    {
                      warn_and_reset ("``materials[n].pbrMetallicRoughness."
                                      "metallicRoughnessTexture.texCoord\'\' "
                                      "must be a number");
                      return false;
                    }

                  val = val->parent ();
                }

              val = val->parent ();
            }
          else
            {
              warn_and_reset (
                  "materials[n].pbrMetallicRoughness must be an object");
              return false;
            }
        }

      tmp = val->as_object ("normalTexture");
      if (check_object (tmp))
        {
          val = tmp;
          tmp = val->as_object ("index");
          if (!extract_int (material.normal_texture.index, tmp))
            {
              warn_and_reset (
                  "``materials[n].normalTexture.index\'\' must be a number");
              return false;
            }

          tmp = val->as_object ("texCoord");
          if (!extract_int (material.normal_texture.tex_coord, tmp, 0))
            {
              warn_and_reset ("``materials[n].normalTexture.texCoord\'\' must "
                              "be a number");
              return false;
            }

          tmp = val->as_object ("scale");
          if (!extract_float (material.normal_texture.scale, tmp, 1))
            {
              warn_and_reset ("``materials[n].normalTexture.scale\'\' must "
                              "be a number");
              return false;
            }

          val = val->parent ();
        }

      tmp = val->as_object ("occlusionTexture");
      if (check_object (tmp))
        {
          val = tmp;
          tmp = val->as_object ("index");
          if (!extract_int (material.occlusion_texture.index, tmp))
            {
              warn_and_reset ("``materials[n].occlusionTexture.index\'\' must "
                              "be a number");
              return false;
            }

          tmp = val->as_object ("texCoord");
          if (!extract_int (material.normal_texture.tex_coord, tmp, 0))
            {
              warn_and_reset ("``materials[n].occlusionTexture.texCoord\'\' "
                              "must be a number");
              return false;
            }

          tmp = val->as_object ("strength");
          if (!extract_float (material.occlusion_texture.strength, tmp, 1))
            {
              warn_and_reset ("``materials[n].occlusionTexture.strength\'\' "
                              "must be a number");
              return false;
            }

          val = val->parent ();
        }

      tmp = val->as_object ("emissiveTexture");
      if (check_object (tmp))
        {
          val = tmp;
          tmp = val->as_object ("index");
          if (!extract_int (material.emissive_texture.index, tmp))
            {
              warn_and_reset ("``materials[n].emissiveTexture.index\'\' must "
                              "be a number");
              return false;
            }

          tmp = val->as_object ("texCoord");
          if (!extract_int (material.emissive_texture.tex_coord, tmp, 0))
            {
              warn_and_reset ("``materials[n].emissiveTexture.texCoord\'\' "
                              "must be a number");
              return false;
            }

          val = val->parent ();
        }

      tmp = val->as_object ("emissiveFactor"); // Emissive factor
      if (tmp != nullptr)
        {
          if (tmp->array_size () == 3)
            {
              for (auto j = 0; j < 3; j++)
                {
                  if (!extract_float (material.emissive_factor[i],
                                      tmp->as_array (i), 0))
                    {
                      warn_and_reset (
                          "``materials[n].emissiveFactor[m]\'\' must be a number");
                      return false;
                    }
                }
            }
        }

      tmp = val->as_object ("alphaMode");
      if (!extract_string (material.alpha_mode, tmp, "OPAQUE"))
        {
          warn_and_reset ("``materials[n].alphaMode\'\' must be a string");
          return false;
        }
      if (!material.alpha_mode.empty () && material.alpha_mode != "OPAQUE"
          && material.alpha_mode != "MASK" && material.alpha_mode != "BLEND")
        {
          warn_and_reset ("``materials[n].alphaMode\'\' can be ``OPAQUE\'\', "
                          "``BLEND\'\' or ``MASK\'\'");
          return false;
        }

      tmp = val->as_object ("alphaCutoff");
      if (!extract_float (material.alpha_cutoff, tmp, 0.5f))
        {
          warn_and_reset ("``materials[n].alphaCutoff\'\' must be a string");
          return false;
        }

      tmp = val->as_object ("doubleSided");
      if (!extract_boolean (material.double_sided, tmp, false))
        {
          warn_and_reset ("``materials[n].doubleSided\'\' must be a string");
          return false;
        }

      val = val->parent ();
      materials.push_back (material);

      // Print data
      logger << SeverityLevel::info << "Material #" << i << " found."
             << std::endl;
      logger << "\tpbrMetallicRoughness =" << std::endl;
      logger << "\t\tbaseColorFactor = [";
      for (auto j = 0; j < 4; j++)
        {
          logger << materials[i].pbr_metallic_roughness.base_color_factor[i];
          if (j != 3)
            logger << ", ";
        }
      logger << "]" << std::endl;
      if (materials[i].pbr_metallic_roughness.base_color_texture.index >= 0)
        {
          logger << "\t\tbaseColorTexture =" << std::endl;
          logger
              << "\t\t\tindex = "
              << materials[i].pbr_metallic_roughness.base_color_texture.index
              << std::endl;
          logger << "\t\t\ttexCoord = "
                 << materials[i]
                        .pbr_metallic_roughness.base_color_texture.tex_coord
                 << std::endl;
        }
      logger << "\t\tmetallicFactor = "
             << materials[i].pbr_metallic_roughness.metallic_factor
             << std::endl;
      logger << "\t\troughnessFactor = "
             << materials[i].pbr_metallic_roughness.metallic_factor
             << std::endl;
      if (materials[i].pbr_metallic_roughness.metallic_roughness_texture.index
          >= 0)
        {
          logger << "\t\tmetallicRoughnessTexture =" << std::endl;
          logger
              << "\t\t\tindex = "
              << materials[i]
                     .pbr_metallic_roughness.metallic_roughness_texture.index
              << std::endl;
          logger << "\t\t\ttexCoord = "
                 << materials[i]
                        .pbr_metallic_roughness.metallic_roughness_texture
                        .tex_coord
                 << std::endl;
        }
      if (materials[i].normal_texture.index >= 0)
        {
          logger << "\tnormalTexture =" << std::endl;
          logger << "\t\tindex = " << materials[i].normal_texture.index
                 << std::endl;
          logger << "\t\ttexCoord = " << materials[i].normal_texture.tex_coord
                 << std::endl;
          logger << "\t\tscale = " << materials[i].normal_texture.scale
                 << std::endl;
        }
      if (materials[i].occlusion_texture.index >= 0)
        {
          logger << "\tocclusionTexture =" << std::endl;
          logger << "\t\tindex = " << materials[i].occlusion_texture.index
                 << std::endl;
          logger << "\t\ttexCoord = "
                 << materials[i].occlusion_texture.tex_coord << std::endl;
          logger << "\t\tstrength = "
                 << materials[i].occlusion_texture.strength << std::endl;
        }
      if (materials[i].emissive_texture.index >= 0)
        {
          logger << "\temissiveTexture =" << std::endl;
          logger << "\t\tindex = " << materials[i].emissive_texture.index
                 << std::endl;
          logger << "\t\ttexCoord = "
                 << materials[i].emissive_texture.tex_coord << std::endl;
        }
      logger << "\temissiveFactor = [";
      for (auto j = 0; j < 3; j++)
        {
          logger << materials[i].emissive_factor[j];
          if (j != 2)
            logger << ", ";
        }
      logger << "]" << std::endl;
      logger << "\talphaMode = " << materials[i].alpha_mode << std::endl;
      logger << "\talphaCutoff = " << materials[i].alpha_cutoff << std::endl;
      logger << "\tdoubleSided = "
             << (materials[i].double_sided ? "true" : "false") << std::endl;
    }

  // Extract cameras
  std::vector<gltf_camera_desc_t> cameras;
  gltf_camera_desc_t camera;
  val = loader.get_root ();
  val = val->as_object ("cameras");
  if (!check_array (val))
    {
      m_scene_ptr->reset ();
      return false;
    }
  n = val->array_size ();
  if (n == 0)
    {
      warn_and_reset ("``cameras\'\' array has no elements");
      return false;
    }

  for (int i = 0; i < n; i++)
    {
      camera.orthographic.
      val = val->as_array (i);
      if (!check_object (val))
        {
          m_scene_ptr->reset ();
          return false;
        }

      tmp = val->as_object ("pbrMetallicRoughness");
    }

  return true;
}

}