#ifndef OBJECT_H
#define OBJECT_H

#include <gle/uuid.h>

#include <map>
#include <string>

namespace gle
{

class Logger;

class Object
{

private:

  typedef std::map<UUID, Object*> object_map_t;
  typedef object_map_t::iterator object_map_iter_t;

  static object_map_t object_pool;

public:

  static void clear_object_pool();
  static Object* get_object(const UUID & object_id);
  static const UUID & register_object(Object * obj);
  static void unregister_object(const UUID & id);

private:

  UUID m_id;

public:
  Object();
  Object(const Object &) = delete;
  Object(Object &&) = delete;
  virtual ~Object();

  virtual const std::string type_name() const = 0;

  const UUID & id() const;
};

Logger& operator<<(Logger& logger, const Object& object);

}

#endif // OBJECT_H
