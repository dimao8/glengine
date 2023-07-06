#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>

namespace gle
{

typedef std::vector<Attribute *> attribute_vector_t;
typedef std::vector<Buffer *> buffer_vector_t;

class Attribute;
class Buffer;

///
/// \brief Vertex array class
///
class VertexArray
{

private:
  unsigned int m_handle;           /// Handle of the vertex array
  buffer_vector_t m_buffers;       /// List of vertex buffers

public:
  ///
  /// \brief Create empty vertex array
  ///
  VertexArray ();

  VertexArray (const VertexArray &) = delete;

  ///
  /// \brief Destroy vertex array. Free all resources.
  ///
  ~VertexArray ();

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
};

}

#endif // VERTEXARRAY_H
