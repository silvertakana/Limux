#pragma once
#include "Core.h"
#include "Lumix/Events/ApplicationEvent.h"
#include "Lumix/Core/LayerStack.h"
#include "Window.h"
#include "Lumix/ImGui/ImGuiLayer.h"

namespace LMX
{
	class LMX_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};
	
	Application* CreateApplication();
}
