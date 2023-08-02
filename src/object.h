#ifndef OBJECT_H
#define OBJECT_H

#include <gle/uuid.h>

#include <map>

namespace gle
{

class Object
{

private:

  typedef std::map<UUID, Object*> object_map_t;
  typedef object_map_t::const_iterator object_map_citer_t;

  static object_map_t object_pool;

  static const UUID & register_object(Object * obj);
  static void unregister_object(const UUID & id);

public:

  static void clear_object_pool();

private:

  UUID m_id;

public:
  Object();
  Object(const Object &) = delete;
  Object(Object &&) = delete;
  virtual ~Object() {}

  const UUID & id() const;
};

}

#endif // OBJECT_H
