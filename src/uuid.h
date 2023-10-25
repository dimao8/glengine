#ifndef UUID_H
#define UUID_H

#include <cstdint>
#include <ostream>
#include <iomanip>

namespace gle
{

class Logger;

class UUID
{

public:

  static const UUID invalid_uuid;

private:
  static const uint32_t version;
  static const uint32_t variant;
  static uint32_t clock_sequencer;

  uint32_t m_uuid1;
  uint16_t m_uuid2;
  uint16_t m_uuid3;
  uint16_t m_uuid4;
  uint64_t m_uuid5;

  static bool less_than (const UUID &first, const UUID &second);
  static bool greater_than (const UUID &first, const UUID &second);
  static bool less_or_equal (const UUID &first, const UUID &second);
  static bool greater_or_equal (const UUID &first, const UUID &second);
  static bool equal (const UUID &first, const UUID &second);

public:
  UUID ();
  UUID (const UUID &uuid);
  UUID (uint32_t uuid1, uint16_t uuid2, uint16_t uuid3, uint16_t uuid4,
        uint64_t uuid5);

  bool operator< (const UUID &second) const;
  bool operator> (const UUID &second) const;
  bool operator<= (const UUID &second) const;
  bool operator>= (const UUID &second) const;
  bool operator== (const UUID &second) const;
  uint64_t operator[](size_t n) const;

  const std::string text() const;

  friend std::ostream& operator<<(std::ostream& stream, const UUID& uuid);
  friend Logger &operator<< (Logger & logger, const UUID& uuid);
};



}

#endif // UUID_H
