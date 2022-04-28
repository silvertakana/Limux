#include <Lumix.h>

#include <imgui.h>

class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	virtual void OnUpdate() override
	{

	}
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello world!");
		ImGui::End();
	}

	virtual void OnEvent(LMX::Event& event) override
	{
		
	}
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