#include <Lumix.h>
#include <glm/gtx/rotate_vector.hpp>
#include <Lumix/Addon/ControllerInput.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include <imgui.h>

class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
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
			cam.ProjectionMatrix *= glm::perspective(glm::radians(60.f), (float)window.GetWidth() / window.GetHeight(), 0.01f, 100.f);
		}
		shader->Bind();
		shader->setInt("u_Texture", 0);
		cam.Position = { 1,1,1 };
	}

	virtual void OnUpdate(LMX::Timestep ts) override
	{
		LMX::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		LMX::RenderCommand::Clear();
		//cam.DebugCameraController(2.f, 2.f, ts);
		float rotateAngle = LMX::RenderCommand::GetTime();
		cam.Position = {cos(rotateAngle), 1, sin(rotateAngle)};
		cam.Front = -cam.Position;

		glm::mat4 transform{1.f};

		transform = glm::rotate(transform, glm::radians(90.f), glm::vec3(1, 0, 0));
		
		shader->Bind();
		shader->setMat4("u_CamMatrix", cam.GetCameraMatrix());

		m_Textures[(int)round(LMX::RenderCommand::GetTime()*0.3) % m_Textures.size()]->Bind();
		LMX::Renderer::Submit(shader, squareVAO, transform);
	}
	virtual void OnImGuiRender() override
	{
		
	}

	virtual void OnEvent(LMX::Event& event) override
	{
		
	}
private:
	LMX::Ref<LMX::VertexArray> squareVAO;
	LMX::Ref<LMX::Shader> shader;
	std::vector<LMX::Ref<LMX::Texture2D>> m_Textures;
	LMX::Camera cam;
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
	return new Sandbox();
}