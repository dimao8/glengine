#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

namespace gle
{

class Attribute;

typedef std::vector<Attribute*> attribute_vector_t;

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

///
/// \brief Data buffer class
///
class Buffer
{

private:
  unsigned int m_handle;             /// Buffer name
  size_t m_size;                     /// Size of the buffer
  attribute_vector_t m_attributes;   /// Attribute vector
  BufferAccess m_access;             /// Data access type
  BufferOptimization m_optimization; /// Storage optimization type

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
  /// \brief
  /// \param [in] access        -- Access type
  /// \param [in] optimization  -- Optimization type
  /// \param [in] data_size     -- Size of the data in bytes
  /// \param [in] data          -- Stored data
  ///
  /// Unlike constructor, this method does nothing, if there is no data or
  /// data is zero size.
  ///
  void set_data (BufferAccess access, BufferOptimization optimization,
                 size_t data_size, const void *data);

  ///
  /// \brief Add vertex attribute
  /// \param [in] attr -- Vertex attribute. Only non-null attribute will be
  /// added
  ///
  void add_attribute (Attribute *attr);

  ///
  /// \brief Enable current buffer
  ///
  void enable();

  ///
  /// \brief Destroy buffer. Free resources
  ///
  ~Buffer ();

  bool is_empty () const;
  size_t get_attribute_count() const;
  const Attribute * get_attribute(size_t n) const;
  size_t get_element_count() const;

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
  static void disable();
};

}

#endif // BUFFER_H
