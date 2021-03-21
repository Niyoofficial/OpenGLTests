#pragma once

#include <functional>
#include <vector>
#include "Tests/Test.h"

class Menu
{
public:
	Menu();
	~Menu();

	void OnUpdate(float DeltaTime);
	void OnRender();
	void OnImGuiRender();

	template<typename T>
	void AddTest(std::string name)
	{
		m_Tests.push_back(std::pair<std::string, std::function<test::Test* ()>>(name, []() { return new T(); }));
	}

private:
	std::vector<std::pair<std::string, std::function<test::Test*()>>> m_Tests;
	std::pair<std::string*, test::Test*> m_CurrentTest;
};