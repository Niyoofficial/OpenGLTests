#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
    :m_Count(0), m_RendererID(0)
{
}

IndexBuffer::IndexBuffer(const unsigned int* data, const unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(GLuint) == sizeof(unsigned int));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Init(const unsigned int* data, const unsigned int count)
{
    m_Count = count;
    ASSERT(sizeof(GLuint) == sizeof(unsigned int));

    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
