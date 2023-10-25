#include "logger.h"

#include "uuid.h"

#include <chrono>
#include <ctime>
#include <random>
#include <sstream>
#include <stdexcept>

namespace gle
{

const UUID UUID::invalid_uuid = { 0, 0, 0, 0, 0 };

const uint32_t UUID::version = 1;
const uint32_t UUID::variant = 4;
uint32_t UUID::clock_sequencer = 0;

/* **************************** UUID::less_than **************************** */

bool
UUID::less_than (const UUID &first, const UUID &second)
{
  if (first.m_uuid1 < second.m_uuid1)
    return true;
  else if (first.m_uuid1 > second.m_uuid1)
    return false;

  if (first.m_uuid2 < second.m_uuid2)
    return true;
  else if (first.m_uuid2 > second.m_uuid2)
    return false;

  if (first.m_uuid3 < second.m_uuid3)
    return true;
  else if (first.m_uuid3 > second.m_uuid3)
    return false;

  if (first.m_uuid4 < second.m_uuid4)
    return true;
  else if (first.m_uuid4 > second.m_uuid4)
    return false;

  if (first.m_uuid5 < second.m_uuid5)
    return true;
  else if (first.m_uuid5 > second.m_uuid5)
    return false;

  // Equal
  return false;
}

/* *************************** UUID::greater_than ************************** */

bool
UUID::greater_than (const UUID &first, const UUID &second)
{
  if (first.m_uuid1 > second.m_uuid1)
    return true;
  else if (first.m_uuid1 < second.m_uuid1)
    return false;

  if (first.m_uuid2 > second.m_uuid2)
    return true;
  else if (first.m_uuid2 < second.m_uuid2)
    return false;

  if (first.m_uuid3 > second.m_uuid3)
    return true;
  else if (first.m_uuid3 < second.m_uuid3)
    return false;

  if (first.m_uuid4 > second.m_uuid4)
    return true;
  else if (first.m_uuid4 < second.m_uuid4)
    return false;

  if (first.m_uuid5 > second.m_uuid5)
    return true;
  else if (first.m_uuid5 < second.m_uuid5)
    return false;

  // Equal
  return false;
}

/* ************************** UUID::less_or_equal ************************** */

bool
UUID::less_or_equal (const UUID &first, const UUID &second)
{
  if (first.m_uuid1 < second.m_uuid1)
    return true;
  else if (first.m_uuid1 > second.m_uuid1)
    return false;

  if (first.m_uuid2 < second.m_uuid2)
    return true;
  else if (first.m_uuid2 > second.m_uuid2)
    return false;

  if (first.m_uuid3 < second.m_uuid3)
    return true;
  else if (first.m_uuid3 > second.m_uuid3)
    return false;

  if (first.m_uuid4 < second.m_uuid4)
    return true;
  else if (first.m_uuid4 > second.m_uuid4)
    return false;

  if (first.m_uuid5 < second.m_uuid5)
    return true;
  else if (first.m_uuid5 > second.m_uuid5)
    return false;

  // Equal
  return true;
}

/* ************************* UUID::greater_or_equal ************************ */

bool
UUID::greater_or_equal (const UUID &first, const UUID &second)
{
  if (first.m_uuid1 > second.m_uuid1)
    return true;
  else if (first.m_uuid1 < second.m_uuid1)
    return false;

  if (first.m_uuid2 > second.m_uuid2)
    return true;
  else if (first.m_uuid2 < second.m_uuid2)
    return false;

  if (first.m_uuid3 > second.m_uuid3)
    return true;
  else if (first.m_uuid3 < second.m_uuid3)
    return false;

  if (first.m_uuid4 > second.m_uuid4)
    return true;
  else if (first.m_uuid4 < second.m_uuid4)
    return false;

  if (first.m_uuid5 > second.m_uuid5)
    return true;
  else if (first.m_uuid5 < second.m_uuid5)
    return false;

  // Equal
  return true;
}

/* ****************************** UUID::equal ****************************** */

bool
UUID::equal (const UUID &first, const UUID &second)
{
  return (first.m_uuid1 == second.m_uuid1) && (first.m_uuid2 == second.m_uuid2)
         && (first.m_uuid3 == second.m_uuid3)
         && (first.m_uuid4 == second.m_uuid4)
         && (first.m_uuid5 == second.m_uuid5);
}

/* ******************************* UUID::UUID ****************************** */

UUID::UUID ()
{
  std::tm timeinfo = std::tm ();

  timeinfo.tm_sec = 0;
  timeinfo.tm_min = 0;
  timeinfo.tm_hour = 0;
  timeinfo.tm_mday = 15;
  timeinfo.tm_mon = 9;
  timeinfo.tm_year = -318;

  std::time_t tt = std::mktime (&timeinfo);

  std::chrono::system_clock::time_point ref_pt
      = std::chrono::system_clock::from_time_t (tt);

  std::chrono::system_clock::duration d
      = std::chrono::high_resolution_clock::now () - ref_pt;

  typedef std::chrono::duration<long long, std::ratio<1, 10000000> >
      handred_nsecs_type;
  handred_nsecs_type cnt = std::chrono::duration_cast<handred_nsecs_type> (d);

  uint64_t timestamp = cnt.count ();
  uint32_t node;

  std::mt19937_64 generator (timestamp);

  m_uuid1 = timestamp & 0xFFFFFFFF;
  m_uuid2 = (timestamp >> 32) & 0xFFFF;
  m_uuid3 = ((timestamp >> 48) & 0xFFF) | (version << 12);
  m_uuid4 = (clock_sequencer & 0x1FFF) | (variant << 13);
  m_uuid5 = generator ();

  clock_sequencer++;
}

/* ******************************* UUID::UUID ****************************** */

UUID::UUID (const UUID &uuid)
    : m_uuid1 (uuid.m_uuid1), m_uuid2 (uuid.m_uuid2), m_uuid3 (uuid.m_uuid3),
      m_uuid4 (uuid.m_uuid4), m_uuid5 (uuid.m_uuid5)
{
  clock_sequencer++;
}

/* ******************************* UUID::UUID ****************************** */

UUID::UUID (uint32_t uuid1, uint16_t uuid2, uint16_t uuid3, uint16_t uuid4,
            uint64_t uuid5)
    : m_uuid1 (uuid1), m_uuid2 (uuid2), m_uuid3 (uuid3), m_uuid4 (uuid4),
      m_uuid5 (uuid5)
{
  clock_sequencer++;
}

/* **************************** UUID::operator < *************************** */

bool
UUID::operator< (const UUID &second) const
{
  return less_than (*this, second);
}

/* **************************** UUID::operator > *************************** */

bool
UUID::operator> (const UUID &second) const
{
  return greater_than (*this, second);
}

/* *************************** UUID::operator <= *************************** */

bool
UUID::operator<= (const UUID &second) const
{
  return less_or_equal (*this, second);
}

/* *************************** UUID::operator >= *************************** */

bool
UUID::operator>= (const UUID &second) const
{
  return greater_or_equal (*this, second);
}

/* *************************** UUID::operator == *************************** */

bool
UUID::operator== (const UUID &second) const
{
  return equal (*this, second);
}

/* **************************** UUID::operator[] *************************** */

uint64_t
UUID::operator[] (size_t n) const
{
  switch (n)
    {
    case 0:
      return m_uuid1;
      break;

    case 1:
      return m_uuid2;
      break;

    case 2:
      return m_uuid3;
      break;

    case 3:
      return m_uuid4;
      break;

    case 4:
      return m_uuid5;
      break;

    default:
      throw std::out_of_range ("index must be in range 0-4");
    }
}

/* ******************************* UUID::text ****************************** */

const std::string
UUID::text () const
{
  std::stringstream ss;
  ss << *this;

  return ss.str ();
}

/* ******************************* operator<< ****************************** */

std::ostream &
operator<< (std::ostream &stream, const UUID &uuid)
{
  std::streamsize width = stream.width (8);
  stream << std::hex << std::setfill ('0') << uuid[0] << "-";
  stream << std::setw (4) << uuid[1] << "-";
  stream << uuid[2] << "-";
  stream << uuid[3] << "-";
  stream << std::setw (16) << uuid[4];

  stream << std::setw (width) << std::dec << std::setfill (' ');

  return stream;
}

/* ******************************* operator<< ****************************** */

Logger &
operator<< (Logger &logger, const UUID &uuid)
{
  logger.print (SeverityLevel::none, "{%08llx-%04llx-%04llx-%04llx-%016llx}", uuid[0], uuid[1],
                uuid[2], uuid[3], uuid[4]);

  return logger;
}

}
