#include "Menu.h"
#include "imgui/imgui.h"
#include "Renderer.h"

Menu::Menu()
{
}

Menu::~Menu()
{
	if (m_CurrentTest.second != nullptr)
		delete m_CurrentTest.second;
}

void Menu::OnUpdate(float DeltaTime)
{
	if (m_CurrentTest.second)
		m_CurrentTest.second->OnUpdate(DeltaTime);
}

void Menu::OnRender()
{
	if (m_CurrentTest.second)
		m_CurrentTest.second->OnRender();
}

void Menu::OnImGuiRender()
{
	GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));

	if (!m_CurrentTest.second)
	{
		ImGui::Begin("Main Menu");
		for (auto& it : m_Tests)
			if (ImGui::Button(it.first.c_str(), ImVec2(it.first.length() * 8, 20)))
			{
				m_CurrentTest.first = &it.first;
				m_CurrentTest.second = it.second();
			}
		ImGui::End();
	}
	if (m_CurrentTest.second)
	{
		ImGui::Begin(m_CurrentTest.first->c_str());
		if (ImGui::Button("<-", ImVec2(25, 20)))
		{
			delete m_CurrentTest.second;
			m_CurrentTest.second = nullptr;
			m_CurrentTest.first = nullptr;
		}
		else
			m_CurrentTest.second->OnImGuiRender();
		ImGui::End();
	}
}
