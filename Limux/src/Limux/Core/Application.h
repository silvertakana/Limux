#pragma once
#include "Base.h"

#include "Limux/Events/ApplicationEvent.h"
#include "Limux/Core/LayerStack.h"
#include "Window.h"
#include "Limux/ImGui/ImGuiLayer.h"
#include "Limux/Renderer/Buffer.h"
#include "Limux/Renderer/VertexArray.h"

#include "Timestep.h"

int main(int argc, char** argv);

namespace LMX
{
	class LMX_API Application
	{
	public:
		Application(const std::string& name = "Limux");
		virtual ~Application() = default;
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);
		
		inline Window& GetWindow() { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		inline static Application& Get() { return *s_Instance; }
		
		void Close();
		bool m_DockingEnable = true;
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		Timestep m_Timestep;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};
	
	Application* CreateApplication();
}
