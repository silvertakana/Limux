#include <Limux.h>
#include <Limux/Packs/CameraPack.h>
#include <glm/gtx/rotate_vector.hpp>
#include <Platform/OpenGL/OpenGLShader.h>
#include <Limux/Core/EntryPoint.h>
#include <Glad/glad.h>
#include "GLFW/glfw3.h"
#include <future>
#include <mutex>


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
		std::mutex mesh_mutex;
		auto LoadFunction = [&](std::vector<LMX::Ref<LMX::SceneNode>>* meshes, std::string path)
		{
			LMX_PROFILE_SCOPE("LoadFunction");
			auto mesh = LMX::CreateRef<LMX::SceneNode>(path);
			
			std::lock_guard<std::mutex> lock(mesh_mutex);
			meshes->push_back(mesh);
		};
		std::vector<std::future<void>> futures;
		for (size_t i = 0; i < 1; i++)
		{
			futures.push_back(std::async(std::launch::async, LoadFunction, &models, "res/models/backpack/scene.gltf"));
			//futures[i].wait();
		}
		//model = LMX::CreateRef<LMX::SceneNode>("res/models/crow/scene.gltf");
		
		LMX::Texture2D::SetDefaultTexture("res/textures/missing_texture.png");

		shader = LMX::Shader::Load("res/shaders/flat.shader");
		
		{
			auto& window = LMX::Application::Get().GetWindow();
			float aspect = (float)window.GetWidth() / (float)window.GetHeight();
			//cam.reset(new LMX::OrthographicCamera(-aspect, aspect, -1, 1, 0.01f, 100.f));
			cam.reset(new LMX::PerspectiveCamera(glm::radians(60.f), (float)window.GetWidth(), (float)window.GetHeight(), 0.01f, 100.f));
		}
		shader->Bind();
		(*shader)["tiling"] = glm::vec2(1);
		cam->Position = { 0, 0, -1 };
		//cam->Front = -cam->Position;
		cam->Front = { 0, 0, 1 };
		for (size_t i = 0; i < futures.size(); i++)
		{
			LMX_PROFILE_SCOPE("setup model");
			futures[i].wait();
			models[i]->Init();
		}
		models[0]->Scale = glm::vec3(0.01f);
	}
	virtual void OnUpdate(LMX::Timestep ts) override
	{
		LMX_PROFILE_FUNCTION();
		glfwSetWindowTitle((GLFWwindow*)LMX::Application::Get().GetWindow().GetNativeWindow(), std::format("Test - {0}", 1/ts).c_str());
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
			shader->SetUniform("u_CamMatrix", cam->GetViewProjMatrix());
			for (size_t i = 0; i < models.size(); i++)
			{
				models[i]->Translation = glm::vec3 { i, 0.f, 0.f };
				models[i]->UpdateTransform();
				models[i]->Draw(shader);
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
	std::vector<LMX::Ref<LMX::SceneNode>> models;
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
	}
};
LMX::Application* LMX::CreateApplication()
{
	return new Sandbox(); // telling the engine what Application to use
}
