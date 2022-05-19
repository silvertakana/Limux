<<<<<<< HEAD
#include <Limux.h>
#include <glm/gtx/rotate_vector.hpp>
#include <Limux/Addon/ControllerInput.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Limux/Renderer/Cameras/PerspectiveCamera.h>
#include <Limux/Renderer/Cameras/OrthographicCamera.h>
=======
#include <Lumix.h>
#include <glm/gtx/rotate_vector.hpp>
#include <Lumix/Addon/ControllerInput.h>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Lumix/Renderer/Cameras/PerspectiveCamera.h>
#include <Lumix/Renderer/Cameras/OrthographicCamera.h>
>>>>>>> 5b95b19c54b3dbd73c4028756609e5ad568466b1

#include <imgui.h>

class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}
	virtual void OnAttach() override
	{
		std::vector<LMX::Vertex> squareVertices {
			{{-0.75f, -0.75f, 0.0f}, {0.2f, 0.3f, 0.8f, 1.0f}, {0.0f, 0.0f}},
			{{ 0.75f, -0.75f, 0.0f}, {0.2f, 0.3f, 0.8f, 1.0f}, {1.0f, 0.0f}},
			{{ 0.75f,  0.75f, 0.0f}, {0.2f, 0.3f, 0.8f, 1.0f}, {1.0f, 1.0f}},
			{{-0.75f,  0.75f, 0.0f}, {0.2f, 0.3f, 0.8f, 1.0f}, {0.0f, 1.0f}},
		};

		std::vector<uint32_t> squareIndices = { 0, 1, 2, 2, 3, 0 };

		LMX::Ref<LMX::VertexBuffer> squareVBO;
		squareVBO.reset(LMX::VertexBuffer::Create(squareVertices.data(), squareVertices.size() * sizeof(LMX::Vertex)));
		LMX::Ref<LMX::IndexBuffer> squareEBO;
		squareEBO.reset(LMX::IndexBuffer::Create(squareIndices.data(), squareIndices.size() * sizeof(uint32_t)));

		squareVAO.reset(LMX::VertexArray::Create(squareVBO, squareEBO, 0, sizeof(LMX::Vertex)));
		squareVAO->AddAttrib(LMX::ShaderDataType::Float3, true, offsetof(LMX::Vertex, pos));
		squareVAO->AddAttrib(LMX::ShaderDataType::Float4, true, offsetof(LMX::Vertex, color));
		squareVAO->AddAttrib(LMX::ShaderDataType::Float2, true, offsetof(LMX::Vertex, texCoord));

		m_Textures = {
			LMX::Texture2D::Create("res/textures/brick.png"),
			LMX::Texture2D::Create("res/textures/caution.png"),
			LMX::Texture2D::Create("res/textures/cobble_stone.png"),
			LMX::Texture2D::Create("res/textures/default.png"),
			LMX::Texture2D::Create("res/textures/perlin_noise.png"),
			LMX::Texture2D::Create("res/textures/perlin_noise.png"),
			LMX::Texture2D::Create("res/images/lake.png"),
			LMX::Texture2D::Create("res/images/silver.png"),
		};

		shader.reset(LMX::Shader::Create("res/shaders/flat.shader"));
		{
			auto& window = LMX::Application::Get().GetWindow();
			//LMX::PerspectiveCamera* c = new LMX::PerspectiveCamera(glm::radians(60.f), window.GetWidth(), window.GetHeight(), 0.01f, 100.f);

			float aspect = (float)window.GetWidth() / (float)window.GetHeight();
			cam.reset(new LMX::OrthographicCamera(-aspect, aspect, -1, 1, 0.01f, 100.f));
			//cam.reset(new LMX::PerspectiveCamera(glm::radians(60.f), window.GetWidth(), window.GetHeight(), 0.01f, 100.f));
		}

		shader->Bind();
		shader->setInt("u_Texture", 0);
		cam->Position = { 0, 0, 1 };
		//cam->Front = -cam->Position;
		cam->Front = { 0, 0, -1 };
	}
	virtual void OnUpdate(LMX::Timestep ts) override
	{
		LMX_INFO("this is a test");
		LMX::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		LMX::RenderCommand::Clear();
		cam->DebugCameraUpdate(2.f, ts);
		float rotateAngle = LMX::RenderCommand::GetTime();
		//cam->Front = -cam->Position;
		cam->UpdateViewMatrix();
		
		glm::mat4 transform{1.f};

		//transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(1, 0, 0));
		
		shader->Bind();
		shader->setMat4("u_CamMatrix", cam->GetViewProjMatrix());

		m_Textures[(int)round(LMX::RenderCommand::GetTime()*0.3) % m_Textures.size()]->Bind();
		LMX::Renderer::Submit(shader, squareVAO, transform);
	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Camera");
		ImGui::DragFloat3("Position", &cam->Position.x, 0.1f, -100.f, 100.f);
		ImGui::End();
	}

	virtual void OnEvent(LMX::Event& event) override
	{
		if (event.GetEventType() == LMX::EventType::KeyPressed)
		{
			LMX::KeyPressedEvent& e = (LMX::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LMX_KEY_TAB)
				LMX_INFO("Hello World");
		}
	}
private:
	LMX::Ref<LMX::VertexArray> squareVAO;
	LMX::Ref<LMX::Shader> shader;
	std::vector<LMX::Ref<LMX::Texture2D>> m_Textures;
	LMX::Ref<LMX::OrthographicCamera> cam;
};
class Sandbox : public LMX::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{}
};
LMX::Application* LMX::CreateApplication()
{
	return new Sandbox(); // telling the engine what Application to use
}
