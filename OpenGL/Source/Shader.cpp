#include "Shader.h"
#include <iostream>
#include <fstream>

using IDmap = std::unordered_map<std::string, int>;

Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath)
{
    GLCall(m_ShaderID = glCreateProgram());

    AddShader(vertexFilepath, GL_VERTEX_SHADER);
    AddShader(fragmentFilepath, GL_FRAGMENT_SHADER);

    CompileShader();
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_ShaderID));
}

bool Shader::AddShader(const std::string& filepath, unsigned int type)
{
	std::ifstream ifs(filepath.c_str(), std::ios_base::in);
	if (!ifs.is_open())
	{
		std::cout << "Could not open file: " << filepath << std::endl;
		return false;
	}

	std::string line;
	std::string source;
	while (getline(ifs, line))
		source.append(line.append("\n"));
	ifs.close();

    unsigned int ID = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(ID, 1, &src, nullptr));
    GLCall(glCompileShader(ID));

    int result;
    GLCall(glGetShaderiv(ID, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(ID, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(ID, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(ID));
        return false;
    }

    switch (type)
    {
    case GL_VERTEX_SHADER:
        GLCall(glDeleteShader(m_VertexShaderID));
        m_VertexShaderID = ID;
        break;
    case GL_FRAGMENT_SHADER:
        GLCall(glDeleteShader(m_FragmentShaderID));
        m_FragmentShaderID = ID;
        break;
    default:
        ASSERT(false);
    }

    return true;
}

void Shader::CompileShader()
{
    GLCall(glAttachShader(m_ShaderID, m_VertexShaderID));
    GLCall(glAttachShader(m_ShaderID, m_FragmentShaderID));
    GLCall(glLinkProgram(m_ShaderID));
    GLCall(glValidateProgram(m_ShaderID));

    GLCall(glDeleteShader(m_VertexShaderID));
    GLCall(glDeleteShader(m_FragmentShaderID));
}

IDmap::iterator Shader::FindUniform(const std::string& name)
{
    IDmap::iterator it = m_Uniforms.find(name);
    if (it == m_Uniforms.end())
    {
        GLCall(int location = glGetUniformLocation(m_ShaderID, name.c_str()));
        if(location == -1)
            std::cout << name << " not found!" << std::endl;
        it = m_Uniforms.insert(m_Uniforms.begin(), { name, glGetUniformLocation(m_ShaderID, name.c_str()) });
    }
    return it;
}

void Shader::Bind() const
{
    glUseProgram(m_ShaderID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}
