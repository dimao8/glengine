#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "object.h"

#include <string>
#include <vector>

namespace gle
{

class Buffer;
class ShaderProgram;

typedef std::vector<Buffer *> buffer_vector_t;

///
/// \brief Drawing mode enumerator
///
enum class DrawingMode
{
  point,          /// Draw point
  line,           /// Draw line
  line_strip,     /// Draw line strip
  line_loop,      /// Draw looped line
  triangle,       /// Draw triangle
  triangle_strip, /// Draw triangle strip
  triangle_fan    /// Draw triangle fan
};

///
/// \brief Vertex array class
///
class VertexArray : public Object
{

private:
  unsigned int m_handle;     /// Handle of the vertex array
  buffer_vector_t m_buffers; /// List of vertex buffers
  DrawingMode m_mode;        /// Drawing mode
  unsigned int m_gl_mode;
  size_t m_vertex_count;

public:
  VertexArray () = delete;
  VertexArray (const VertexArray &) = delete;

  ///
  /// \brief Create empty vertex array
  /// \param [in] mode -- Drawing mode for current array
  ///
  VertexArray (DrawingMode mode);

  ///
  /// \brief Destroy vertex array. Free all resources.
  ///
  virtual ~VertexArray ();

  ///
  /// \brief Add data buffer
  /// \param [in] buffer -- Data buffer. Only non-null valid buffer will be
  /// added
  ///
  /// After buffer has been added, add_buffer add all buffer's attributes
  /// to the vertex array state. If there is no attributes in the buffer,
  /// it is not added.
  ///
  void add_buffer (Buffer *buffer);

  ///
  /// \brief Remove all data buffers
  ///
  void remove_buffers ();

  ///
  /// \brief Draw current vertex array
  /// \param [in] program -- Shader program
  ///
  void draw (ShaderProgram *program);

  ///
  /// \brief Enable current vertex array
  ///
  void enable ();

  virtual const std::string type_name () const;
};

}

#endif // VERTEXARRAY_H
