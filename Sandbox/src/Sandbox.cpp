#include <Limux.h>
#include <Limux/Packs/CameraPack.h>
#include <glm/gtx/rotate_vector.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Limux/Core/EntryPoint.h>


class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}
	virtual void OnDetach() override
	{
		LMX_INFO("layer {0} detached", m_DebugName);
	}
	virtual void OnAttach() override
	{
		LMX_PROFILE_FUNCTION();
		std::vector<LMX::Vertex> vertices {
			{{ 0.5f,  0.5f, 0.0f}, {0.f, 0.f, 0.f, 1.f}, {1.0f, 1.0f}},
			{{-0.5f,  0.5f, 0.0f}, {0.f, 0.f, 0.f, 1.f}, {0.0f, 1.0f}},
			{{ 0.5f, -0.5f, 0.0f}, {0.f, 0.f, 0.f, 1.f}, {1.0f, 0.0f}},
			{{-0.5f, -0.5f, 0.0f}, {0.f, 0.f, 0.f, 1.f}, {0.0f, 0.0f}}, 
		};

		std::vector<uint32_t> indices {0,2,1,1,2,3};
		LMX::Ref<LMX::VertexBuffer> VBO;
		VBO = LMX::VertexBuffer::Create(vertices.data(), vertices.size() * sizeof(LMX::Vertex));
		LMX::Ref<LMX::IndexBuffer> EBO;
		EBO = LMX::IndexBuffer::Create(indices.data(), indices.size() * sizeof(uint32_t));
		
		VAO = LMX::VertexArray::Create(VBO, EBO, 0, sizeof(LMX::Vertex));
		VAO->AddAttrib(LMX::DataType::Float3, true, offsetof(LMX::Vertex, pos));
		VAO->AddAttrib(LMX::DataType::Float4, true, offsetof(LMX::Vertex, color));
		VAO->AddAttrib(LMX::DataType::Float2, true, offsetof(LMX::Vertex, texCoord));\
		m_Textures = {
			LMX::Texture2D::Load("res/textures/fence.png", LMX::Texture2D::Mipmap | LMX::Texture2D::MagLinear)
		};
		shader = LMX::Shader::Load("res/shaders/flat.shader");
		
		{
			auto& window = LMX::Application::Get().GetWindow();
			float aspect = (float)window.GetWidth() / (float)window.GetHeight();
			//cam.reset(new LMX::OrthographicCamera(-aspect, aspect, -1, 1, 0.01f, 100.f));
			cam.reset(new LMX::PerspectiveCamera(glm::radians(60.f), window.GetWidth(), window.GetHeight(), 0.01f, 100.f));
		}
		shader->Bind();
		(*shader)["u_Texture"] = 0;
		cam->Position = { 0, 0, 1 };
		//cam->Front = -cam->Position;
		cam->Front = { 0, 0, -1 };
	}
	virtual void OnUpdate(LMX::Timestep ts) override
	{
		LMX_PROFILE_FUNCTION();
		{
			LMX_PROFILE_SCOPE("Camera Controlling");
			LMX::DebugPerspecCamUpdate(cam, 2.f, 2.f, ts);
			cam->UpdateViewMatrix();
		}
		{
			LMX_PROFILE_SCOPE("Renderer Prep");
			LMX::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			LMX::RenderCommand::Clear();
		}
		
		{
			LMX_PROFILE_SCOPE("Renderering");
			shader->Bind();
			(*shader)["u_CamMatrix"] = cam->GetViewProjMatrix();

			m_Textures[0]->Bind();
			for (size_t i = 0; i < 4; i++)
			{
				glm::mat4 model = glm::mat4(1.f);
				model = glm::rotate(model, glm::radians(i * 90.f), glm::vec3(0.f, 1.f, 0.f));
				model = glm::translate(model, glm::vec3(0.f, 0.f, -0.5f));
				LMX::Renderer::Submit(shader, VAO, model);
			}
		}
	}
	virtual void OnImGuiRender() override
	{
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
	LMX::Ref<LMX::VertexArray> VAO;
	LMX::Ref<LMX::Shader> shader;
	std::vector<LMX::Ref<LMX::Texture>> m_Textures;
	LMX::Ref<LMX::PerspectiveCamera> cam;
};
static LMX::Layer* layer;
class Sandbox : public LMX::Application
{
public:
	Sandbox()
	{
		PushLayer(layer = new ExampleLayer());
	}

	~Sandbox()
	{
		PopLayer(nullptr);
	}
};
LMX::Application* LMX::CreateApplication()
{
	return new Sandbox(); // telling the engine what Application to use
}
