#include <Lumix.h>
class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		//LMX_INFO("ExampleLayer::Update");
	}

	void OnEvent(LMX::Event& event) override
	{
		//LMX_INFO("{0}", event.ToString());
	}

};
class Sandbox : public LMX::Application
{
public:
	Sandbox()
		:Application()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new LMX::ImGuiLayer());
	}

	~Sandbox()
	{}
};

LMX::Application* LMX::CreateApplication()
{
	return new Sandbox();
}