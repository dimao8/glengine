# Achitecture of the GLEngine #

## OpenGL Object Wrapper Architecture ##

OpenGL object in this context means some programming object with generator,
deleter and binder. Some examples: texture object, vertex array object, buffer
object.

The wrapper class for OpenGL object must have `GLuint m_handle` or
`GLint m_handle` private field. This field used in generator function to
generate it's object. See texture example below:

```C++
class Texture
{
...
private:
  GLuint m_handle;
...
public:
  Texture ();
  virtual ~Texture ()
  void enable ();
  GLuint handle () const;
...
  static void disable ();
};
...
Texture::Texture ()
{
  glGenTextures(1, &m_handle);
  if ...
}
...
Texture::~Texture ()
{
  disable ();
  glDeleteTextures(1, &m_handle);
}
...
void Texture::enable ()
{
  glBindTexture (GL_TEXTURE_2D, m_handle);
}
...
void Texture::disable ()
{
  glBindTexture (GL_TEXTURE_2D, 0);
}
...
GLuint Texture::handle () const
{
  return m_handle;
}
```

When wrapper in creation, there must be glGen function used to generate object.
The returned object name must be saved in `m_handle` field. In deleter the
glDelete is used. `m_handle` used to delete object.

If bind is needed before use of object, glBind function must be called with
`m_handle` field as object name. Bind wrap function must be called `enable` and
must have no arguments nor return values. To unbind any previously bound object
there must be _static_ `disable` function, that bind default object (usually
object with name 0). It is good idea to check if current object was bound
before unbind it in destructor.

Object name can be retrieved by using getter `handle()`.
