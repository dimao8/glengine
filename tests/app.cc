#include "../src/application.h"

class App : public gle::Application
{

private:
  gle::Shader *m_vertex_shader;
  gle::Shader *m_fragment_shader;
  gle::ShaderProgram *m_shader_program;
  gle::VertexArray *m_vertex_array;
  gle::Buffer *m_buffer;

public:
  App (int argc = 0, char **argv = nullptr);

  virtual void draw ();
  virtual void init ();
  virtual void cleanup ();
};

GLfloat mesh[21]
    = { -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f,  0.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f };

/* ******************************** App::App ******************************* */

App::App (int argc, char **argv) : gle::Application (argc, argv) {}

/* ******************************* App::draw ******************************* */

void
App::draw ()
{
  gle::logger << gle::SeverityLevel::info << "App::draw()" << std::endl;
  m_vertex_array->draw (m_shader_program);
}

/* ******************************* App::init ******************************* */

void
App::init ()
{
  m_vertex_shader
      = new gle::Shader (gle::ShaderType::vertex, "tests/shader.vert");
  m_fragment_shader
      = new gle::Shader (gle::ShaderType::fragment, "tests/shader.frag");
  m_shader_program
      = new gle::ShaderProgram (m_vertex_shader, m_fragment_shader);
  m_shader_program->enable ();

  m_buffer = new gle::Buffer (gle::BufferAccess::draw,
                              gle::BufferOptimization::stat);
  m_buffer->append_data (gle::BufferAccess::draw,
                         gle::BufferOptimization::stat, 21, mesh);
  m_vertex_array = new gle::VertexArray (gle::DrawingMode::triangle);
  m_vertex_array->enable ();
  m_vertex_array->add_buffer (m_buffer,
                              new gle::Attribute (gle::AttributeType::fv3, 0));
  m_vertex_array->add_buffer (m_buffer,
                              new gle::Attribute (gle::AttributeType::fv4, 1));
  m_vertex_array->update ();
}

/* ****************************** App::cleanup ***************************** */

void
App::cleanup ()
{
  delete m_shader_program;
  delete m_vertex_shader;
  delete m_fragment_shader;
  delete m_vertex_array;
  delete m_buffer;
}

/* ********************************** main ********************************* */

int
main (int argc, char **argv)
{
  App app (argc, argv);
  int result = app.run ();
  app.terminate ();
  return result;
}
