#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

namespace gle
{

///
/// \brief Attribute type enumerator
///
enum class AttributeType
{
  f,   /// single float
  fv2, /// 2 floats vector
  fv3, /// 3 floats vector
  fv4, /// 4 floats vector
  i,   /// single integer
  iv2, /// 2 integers vector
  iv3, /// 3 integers vector
  iv4, /// 4 integers vector
  b,   /// single boolean
  bv2, /// 2 booleans vector
  bv3, /// 3 booleans vector
  bv4  /// 4 booleans vector
};

///
/// \brief Vertex attribute
///
class Attribute
{

private:
  std::string m_name;   /// Optional name. Can be empty string
  int m_number;         /// Layout number of the attribute
  AttributeType m_type; /// Type of the attribute

public:
  Attribute () = delete;
  Attribute (const Attribute &) = delete;

  ///
  /// \brief Create named attribute
  /// \param [in] type    -- Type of the attribute. Must be one of
  /// AttributeType
  /// \param [in] number  -- Layout number. Attribute with negative number is
  /// invalid
  /// \param [in] name    -- Optional name of the attribute
  ///
  Attribute (AttributeType type, int number, const std::string &name = "");

  AttributeType get_type() const;
  int get_number() const;
  const std::string & get_name() const;
  size_t get_size() const;
};

}

#endif // ATTRIBUTE_H
