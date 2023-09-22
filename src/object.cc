#include "object.h"
#include "logger.h"

#include <typeinfo>

namespace gle
{

Object::object_map_t Object::object_pool;

/* ***************************** Object::Object **************************** */

Object::Object () : m_id () 
{
  //
}

/* **************************** Object::~Object **************************** */

Object::~Object ()
{
  LOG_PRINT (SeverityLevel::info, "Delete %s\n", m_id.text ().c_str ());
}

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

  LOG_PRINT (SeverityLevel::info, "Register object");
  logger << *obj << log::endl;

  object_map_iter_t it = object_pool.find (obj->id ());

  if (it != object_pool.end ())
    {
      delete it->second;
      object_pool.erase (it);
    }

  object_pool.emplace (obj->id (), obj);

  return obj->id ();
}

/* *********************** Object::unregister_object *********************** */

void
Object::unregister_object (const UUID &id)
{
  object_map_iter_t it = object_pool.find (id);
  if (it != object_pool.end ())
    object_pool.erase (it);
}

/* *********************** Object::remove_object_pool ********************** */

void
Object::clear_object_pool ()
{
  for (auto &it : object_pool)
    delete it.second;
}

/* *************************** Object::get_object ************************** */

Object *
Object::get_object (const UUID &object_id)
{
  object_map_iter_t it = object_pool.find (object_id);

  if (it == object_pool.end ())
    {
      LOG_PRINT (SeverityLevel::warning,
                 "Object with id %s is not registered\n",
                 object_id.text ().c_str ());
      return nullptr;
    }
  else
    return it->second;
}

/* ******************************* operator<< ****************************** */

Logger &
operator<< (Logger &logger, const Object &object)
{
  logger.print (SeverityLevel::none, " %s(%s)", object.type_name ().c_str (),
                object.id ().text ().c_str ());
  return logger;
}

}
