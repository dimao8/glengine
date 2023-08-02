#include "object.h"

namespace gle
{

/* ***************************** Object::Object **************************** */

Object::Object () : m_id () {}

/* ******************************* Object::id ****************************** */

const UUID &
Object::id () const
{
  return m_id;
}

/* ************************ Object::register_object ************************ */

const UUID &
Object::register_object (Object *obj)
{
  if (obj == nullptr)
    return UUID::invalid_uuid;

  object_map_citer_t it = object_pool.find (obj->id ());

  if (it != object_pool.end ())
    delete it->second;

  object_pool[obj->id ()] = obj;

  return obj->id ();
}

/* *********************** Object::unregister_object *********************** */

void
Object::unregister_object (const UUID &id)
{
  object_map_citer_t it = object_pool.find (id);
  if (it != object_pool.end())
    object_pool.erase(it);
}

/* *********************** Object::remove_object_pool ********************** */

void Object::clear_object_pool()
{
  for (auto it : object_pool)
    delete it.second;
}

}
