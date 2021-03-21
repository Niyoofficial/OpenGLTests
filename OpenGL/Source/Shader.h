#pragma once

#include "Renderer.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"


class Shader
{
private:
	using IDmap = std::unordered_map<std::string, int>;

	unsigned int m_ShaderID = 0;
	unsigned int m_VertexShaderID = 0;
	unsigned int m_FragmentShaderID = 0;

	IDmap m_Uniforms;

public:
	Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath);
	~Shader();

	bool AddShader(const std::string& filepath, unsigned int type);
	void CompileShader();

	template<typename... Args>
	inline void SetUniform(const std::string& name, Args... args)
	{
		static_assert(false);
	}

	template<>
	inline void SetUniform(const std::string& name, bool v)
	{
		IDmap::iterator it = FindUniform(name);
		GLCall(glUniform1i(it->second, v));
	}

	template<>
	inline void SetUniform(const std::string& name, float v0, float v1, float v2, float v3)
	{
		IDmap::iterator it = FindUniform(name);
		GLCall(glUniform4f(it->second, v0, v1, v2, v3));
	}

	template<>
	inline void SetUniform(const std::string& name, int v)
	{
		IDmap::iterator it = FindUniform(name);
		GLCall(glUniform1i(it->second, v));
	}

	template<>
	inline void SetUniform(const std::string& name, glm::mat4x4 matrix)
	{
		IDmap::iterator it = FindUniform(name);
		GLCall(glUniformMatrix4fv(it->second, 1, GL_FALSE, &matrix[0][0]));
	}

	void Bind() const;
	void Unbind() const;
protected:
	IDmap::iterator FindUniform(const std::string& name);
};
