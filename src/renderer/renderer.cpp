#include "renderer.h"

void renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void renderer::Draw(const vertexArray& va, const indexBuffer& ib, const shader& sh)
{
    sh.Bind();
    va.Bind();
    ib.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ib.m_count, GL_UNSIGNED_INT, nullptr));
}