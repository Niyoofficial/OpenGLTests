#pragma once

#include <GL/glew.h>

class VertexArray;
class IndexBuffer;
class Shader;

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogError(#x, __FILE__, __LINE__));

void GLClearError();

bool GLLogError(const char* function, const char* file, int line);

class Renderer
{
public:
    void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader) const;
    void Clear() const;
};