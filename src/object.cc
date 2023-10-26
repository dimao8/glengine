#include "object.h"
#include "logger.h"
#include "translate.h"

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
  logger << SeverityLevel::info << _ ("Delete ") << m_id.text ().c_str ()
         << std::endl;
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

  logger << SeverityLevel::info << "Register object";
  logger << *obj << std::endl;

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
      logger << SeverityLevel::warning << _ ("Object with id ")
             << object_id.text ().c_str () << _ (" is not registered")
             << std::endl;
      return nullptr;
    }
  else
    return it->second;
}

/* ******************************* operator<< ****************************** */

Logger &
operator<< (Logger &logger, const Object &object)
{
  logger << _ ("Object ") << object.id ().text ().c_str () << std::endl;
  return logger;
}

}
