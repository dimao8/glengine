#include "mesh.h"

namespace gle
{

/* ******************************* Mesh::Mesh ****************************** */

Mesh::Mesh (DrawingMode mode, SceneNode *parent)
    : SceneNode (parent), m_vertex_array (mode)
{
}

/* ****************************** Mesh::~Mesh ****************************** */

Mesh::~Mesh ()
{
  m_vertex_array.remove_buffers ();

  for (auto it : m_buffers)
    delete it;
}

/* ******************************* Mesh::draw ****************************** */

void
Mesh::draw ()
{
  // TODO : Draw mesh code
}

}
