#include <Lumix.h>
class ExampleLayer : public LMX::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{}

	void OnUpdate() override
	{
		if (LMX::Input::IsKeyPressed(LMX_KEY_TAB))
			LMX_INFO("Tab key is pressed (poll)!");
	}

	void OnEvent(LMX::Event& event) override
	{
		if (event.GetEventType() == LMX::EventType::MouseButtonPressed)
		{
			LMX::MouseButtonPressedEvent& e = (LMX::MouseButtonPressedEvent&)event;
			if (e.GetMouseButton() == LMX_MOUSE_BUTTON_1)
				LMX_INFO("button 1 is pressed (event)!");
			LMX_INFO("{0}", e.GetMouseButton());
		}
		
		if (event.GetEventType() == LMX::EventType::KeyPressed)
		{
			LMX::KeyPressedEvent& e = (LMX::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LMX_KEY_TAB)
				LMX_INFO("Tab key is pressed (event)!");
			LMX_INFO("{0}", (char)e.GetKeyCode());
		}
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