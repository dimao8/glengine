#include <gle/engine.h>
#include <iostream>

class Game : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;
  gle::Shader *m_fragment_shader;
  gle::ShaderProgram *m_shader_program;
  gle::Buffer *m_rect_mesh;
  gle::VertexArray *m_rect;

public:
  Game (int argc, char **argv);
  virtual ~Game ();
  virtual void init () final;
  void cleanup () final;
  void draw () final;

private:
  static const GLsizei m_mesh_size;
  static const GLfloat m_mesh[];
};

// clang-format off
const GLsizei Game::m_mesh_size = 42;
const GLfloat Game::m_mesh[] = {
//   x      y      z        r     g     b     a
  -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f,
   0.5f, -0.5f,  0.0f,    1.0f, 1.0f, 0.0f, 1.0f,
   0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f, 1.0f,

  -0.5f, -0.5f,  0.0f,    1.0f, 0.0f, 0.0f, 1.0f,
   0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 1.0f, 1.0f,
  -0.5f,  0.5f,  0.0f,    0.0f, 1.0f, 0.0f, 1.0f
};
// clang-format on

/* ******************************* Game::Game ****************************** */

Game::Game (int argc, char **argv) : gle::Application (argc, argv) {}

/* ****************************** Game::~Game ****************************** */

Game::~Game () { cleanup (); }

/* ******************************* Game::init ****************************** */

void
Game::init ()
{
  m_vertex_shader
      = new gle::Shader (gle::ShaderType::vertex, "tests/shader.vert");
  m_fragment_shader
      = new gle::Shader (gle::ShaderType::fragment, "tests/shader.frag");

  m_shader_program
      = new gle::ShaderProgram (m_vertex_shader, m_fragment_shader);

  m_rect_mesh = new gle::Buffer (gle::BufferAccess::draw,
                                 gle::BufferOptimization::stat,
                                 sizeof (GLfloat) * m_mesh_size, m_mesh);
  m_rect_mesh->add_attribute (new gle::Attribute (gle::AttributeType::fv3, 0));
  m_rect_mesh->add_attribute (new gle::Attribute (gle::AttributeType::fv4, 1));

  m_rect = new gle::VertexArray (gle::DrawingMode::triangle);
  m_rect->add_buffer(m_rect_mesh);
}

/* ***************************** Game::cleanup ***************************** */

void
Game::cleanup ()
{
  delete m_rect;
  delete m_rect_mesh;

  delete m_shader_program;

  delete m_vertex_shader;
  delete m_fragment_shader;
}

/* ******************************* Game::draw ****************************** */

void
Game::draw ()
{
  m_rect->draw (m_shader_program);
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  Game game (argc, argv);

  game.register_arg ('h', "help", "Print this message and exit");
  game.register_arg ('v', "version", "Print version prompt and exit");

  return game.run ();
}
