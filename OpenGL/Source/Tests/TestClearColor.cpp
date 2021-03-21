#include "TestClearColor.h"
#include "GL/glew.h"
#include "Renderer.h"
#include "imgui/imgui.h"

test::TestClearColor::TestClearColor()
	:m_ClearColor{ 1.f, 0.f, 1.f, 1.f }
{
}

test::TestClearColor::~TestClearColor()
{
}

void test::TestClearColor::OnUpdate(float DeltaTime)
{
}

void test::TestClearColor::OnRender()
{
	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void test::TestClearColor::OnImGuiRender()
{
	ImGui::ColorEdit4("Color", m_ClearColor);
}
