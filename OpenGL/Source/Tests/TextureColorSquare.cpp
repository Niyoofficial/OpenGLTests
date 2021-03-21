#include "TextureColorSquare.h"

#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

test::TextureColorSquare::TextureColorSquare()
    :m_Shader("Resources/Shaders/VertexBasic.shader", "Resources/Shaders/FragmentBasic.shader"), m_Texture("Resources/Textures/Box.png"),
    m_Color(0.5f, 0.8f, 0.2f, 1.f), m_TransformA{ 200.f, 200.f }, m_TransformB{ 400.f, 200.f }
{
    m_Incolor = m_Color;
    float positions[]
    {
        -50.f, -50.f, 0.f, 0.f,
         50.f, -50.f, 1.f, 0.f,
         50.f,  50.f, 1.f, 1.f,
        -50.f,  50.f, 0.f, 1.f
    };

    unsigned int indices[]
    {
        0, 1, 2,
        0, 2, 3
    };

    m_Shader.Bind();

    m_Texture.Bind();
    m_Shader.SetUniform("u_Texture", 0);

    m_VBO.Init(positions, 4 * 4 * sizeof(float));

    m_Layout.Push<float>(2);
    m_Layout.Push<float>(2);

    m_VAO.AddBuffer(m_VBO, m_Layout);

    m_IBO.Init(indices, 6);

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

test::TextureColorSquare::~TextureColorSquare()
{
}

void test::TextureColorSquare::OnUpdate(float DeltaTime)
{
}

void test::TextureColorSquare::OnRender()
{
}

void test::TextureColorSquare::OnImGuiRender()
{
    if (r <= 0.f || r >= 1.f)
        incrementR = -incrementR;
    if (g <= 0.f || g >= 1.f)
        incrementG = -incrementG;
    if (b <= 0.f || b >= 1.f)
        incrementB = -incrementB;
    r += incrementR;
    g += incrementG;
    b += incrementB;

    ImGui::DragFloat2("TransformA", m_TransformA, 1.5f, -1000.f, 1000.f, "%.1f", 1.f);
    ImGui::DragFloat2("TransformB", m_TransformB, 1.5f, -1000.f, 1000.f, "%.1f", 1.f);
    ImGui::ColorEdit3("color", (float*)&m_Incolor); // Edit 3 floats representing a color
    ImGui::Checkbox("Show Texture", &isTexture);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    r += m_Incolor.x - m_Color.x;
    g += m_Incolor.y - m_Color.y;
    b += m_Incolor.z - m_Color.z;

    m_Color = m_Incolor;

    m_Shader.Bind();
    m_Shader.SetUniform("u_Color", r, g, b, 1.f);
    m_Shader.SetUniform("u_IsTexture", isTexture);

    glm::mat4x4 proj = glm::ortho(0.f, 640.f, 0.f, 480.f, -1.f, 1.f);
    glm::mat4x4 view = glm::translate(glm::mat4x4(1.f), glm::vec3(0, 0, 0));
    glm::mat4x4 model;

    Renderer renderer;

    {
        model = glm::translate(glm::mat4x4(1.f), glm::vec3(m_TransformA[0], m_TransformA[1], 0.f));
        glm::mat4x4 mvp = proj * view * model;
        m_Shader.Bind();
        m_Shader.SetUniform("u_MVP", mvp);
        renderer.Draw(m_VAO, m_IBO, m_Shader);
    }

    {
        model = glm::translate(glm::mat4x4(1.f), glm::vec3(m_TransformB[0], m_TransformB[1], 0.f));
        glm::mat4x4 mvp = proj * view * model;
        m_Shader.Bind();
        m_Shader.SetUniform("u_MVP", mvp);
        renderer.Draw(m_VAO, m_IBO, m_Shader);
    }
}
