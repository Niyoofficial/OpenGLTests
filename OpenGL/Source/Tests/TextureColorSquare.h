#pragma once

#include "Test.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "imgui/imgui.h"

namespace test
{
	class TextureColorSquare : public Test
	{
	public:
		TextureColorSquare();
		~TextureColorSquare();

		void OnUpdate(float DeltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexBuffer m_VBO;
		VertexBufferLayout m_Layout;
		VertexArray m_VAO;
		IndexBuffer m_IBO;
		Shader m_Shader;
		Texture m_Texture;

		float incrementR = 0.05f;
		float incrementG = 0.05f;
		float incrementB = 0.05f;
		float r = 0.5f;
		float g = 0.8f;
		float b = 0.2f;
		bool isTexture = false;
		ImVec4 m_Color;
		ImVec4 m_Incolor;
		float m_TransformA[2];
		float m_TransformB[2];
	};
}