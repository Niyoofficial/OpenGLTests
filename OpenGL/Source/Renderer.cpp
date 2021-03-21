#include "Renderer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogError(const char* function, const char* file, int line)
{
    GLenum error;
    bool b_clear = true;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        b_clear = false;
        std::cout << "[OpenGL Error] (" << std::hex << error << std::dec << ") | " << "On line: " << line << " | In function call: " << function << " | In file: " << file << std::endl;
    }

    return b_clear;
}

void Renderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const
{
    vao.Bind();
    ibo.Bind();
    shader.Bind();

    GLCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
