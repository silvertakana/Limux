#include <Limux.h>
#include <Limux/Core/Input.h>
#include <Limux/Packs/CameraPack.h>
#include <Limux/Core/EntryPoint.h>
#include <Glad/glad.h>
#include "GLFW/glfw3.h"

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
		static auto LoadFunction = [&](LMX::SceneNode* scene, std::string path)
		{
			LMX_PROFILE_SCOPE("LoadFunction");
			//scene->AddModel(path);
			auto node = LMX::CreateRef<LMX::SceneNode>(path);
			std::lock_guard<std::mutex> lock(mesh_mutex);
			scene->Children.push_back(node);
		};
		std::vector<std::future<void>> futures;
		for (size_t i = 0; i < 50; i++)
		{
			futures.push_back(std::async(std::launch::async, LoadFunction, &scene, "res/models/crow/scene.gltf"));
			futures[i].wait();
		}
		
		LMX::Texture2D::SetDefaultTexture("res/textures/missing_texture.png");

		shader = LMX::Shader::Load("res/shaders/flat.shader");
		
		{
			auto& window = LMX::Application::Get().GetWindow();
			float aspect = (float)window.GetWidth() / (float)window.GetHeight();
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
			scene[i]->Init();
			scene[i]->Scale = glm::vec3(0.1f);
			scene[i]->Rotation.y = glm::radians(180.f);
			scene[i]->Translation = { i%3, 0.f, i/3 };
		}
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
			LMX::Renderer::BeginScene();
			LMX_PROFILE_SCOPE("Renderering");
			shader->Bind();
			shader->SetUniform("u_CamMatrix", cam->GetViewProjMatrix());
			for (size_t i = 0; i < scene.size(); i++)
			{
				scene[i]->UpdateTransform();
				scene[i]->Draw(shader);
			}
			statistics = LMX::Renderer::EndScene();
		}
	}
	virtual void OnImGuiRender(LMX::Timestep ts) override
	{
		LMX_PROFILE_FUNCTION();
	}

	virtual void OnEvent(LMX::Event& event, LMX::Timestep ts) override
	{
	}
private:
	LMX::SceneNode scene;
	LMX::Ref<LMX::Shader> shader;
	std::vector<LMX::Ref<LMX::Texture>> m_Textures;
	LMX::Ref<LMX::PerspectiveCamera> cam;
	LMX::Ref<LMX::Renderer::Statistics> statistics;
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
	return new Sandbox();
}