#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "buffer.h"

#include <string>
#include <vector>
#include <memory>

namespace gle
{

class ShaderProgram;

typedef std::vector<std::shared_ptr<Buffer>> buffer_vector_t;

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
class VertexArray
{

private:
  unsigned int m_handle;           /// Handle of the vertex array
  buffer_vector_t m_buffers;       /// List of vertex buffers
  attribute_vector_t m_attributes; /// Attribute vector
  DrawingMode m_mode;              /// Drawing mode
  unsigned int m_gl_mode;
  size_t m_vertex_count;
  bool m_actual;

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
  /// \param [in] attribute -- Attribute of that buffer.
  ///
  /// Add data buffer and link it with an attribute. If buffer is already
  /// exists, bind it and add attribute.
  ///
  void add_buffer (const std::shared_ptr<Buffer> & buffer, Attribute *attrib);

  ///
  /// \brief Remove all data buffers
  ///
  void remove_buffers ();

  ///
  /// \brief Draw current vertex array
  /// \param [in] program -- Shader program
  ///
  void draw (ShaderProgram & program);

  ///
  /// \brief Enable current vertex array
  ///
  void enable ();

  void update ();

  bool is_actual () const;
};

}

#endif // VERTEXARRAY_H
