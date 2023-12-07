#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

#include "opengl.h"

namespace gle
{

enum class BufferAccess
{
  draw,
  read,
  copy
};

enum class BufferOptimization
{
  stat,
  dyn,
  stream
};

class Attribute;

typedef std::vector<Attribute *> attribute_vector_t;

///
/// \brief Data buffer class
///
class Buffer
{

private:
  unsigned int m_handle;             /// Buffer name
  BufferAccess m_access;             /// Data access type
  BufferOptimization m_optimization; /// Storage optimization type
  std::vector<GLfloat> m_data;       /// Data
  attribute_vector_t m_attributes;   /// Attribute list
  bool m_actual;                     /// Data status

public:
  Buffer () = delete;
  Buffer (const Buffer &) = delete;

  ///
  /// \brief Create empty buffer with storage parameters
  /// \param [in] access        -- Access type
  /// \param [in] optimization  -- Optimization type
  /// \param [in] size          -- Size of the data in bytes
  /// \param [in] data          -- Stored data
  ///
  /// Buffer can be created with or without data. Buffer can have space with no
  /// data to further filling. If \c data is \c nullptr , the buffer is empty
  /// but allocated. If \c data and \c data_size is 0, the buffer allocate no
  /// memory.
  ///
  Buffer (BufferAccess access, BufferOptimization optimization,
          size_t data_size = 0, const void *data = nullptr);

  ///
  /// \brief Clear buffer
  ///
  void clear ();

  ///
  /// \brief
  /// \param [in] access        -- Access type
  /// \param [in] optimization  -- Optimization type
  /// \param [in] data_size     -- Size of the data in bytes
  /// \param [in] data          -- Stored data
  ///
  /// Unlike constructor, this method does nothing, if there is no data or
  /// data is zero size.
  ///
  void append_data (BufferAccess access, BufferOptimization optimization,
                    size_t data_size, const void *data);

  void add_attribute (Attribute * attribute);

  size_t attrib_count () const;

  const Attribute * attribute (int i) const;

  ///
  /// \brief Send data to the server
  ///
  void update ();

  ///
  /// \brief Enable current buffer
  ///
  void enable ();

  ///
  /// \brief Destroy buffer. Free resources
  ///
  virtual ~Buffer ();

  ///
  /// \brief Size of the data in bytes
  ///
  size_t size () const;

  ///
  /// \brief Get data status
  /// \return Return status of current buffer data. Return true if buffer data
  /// and server data is equal. Otherwise return false.
  ///
  /// \note Use update() to actualize data on server.
  ///
  bool is_actual () const;

private:
  ///
  /// \brief Get OpenGL specific buffer type
  /// \param [in] access        -- Access type enum
  /// \param [in] optimization  -- Optimization type enum
  ///
  static unsigned int buffer_type_to_glenum (BufferAccess access,
                                             BufferOptimization optimization);

public:
  ///
  /// \brief Disable all buffers
  ///
  static void disable ();
};

}

#endif // BUFFER_H
