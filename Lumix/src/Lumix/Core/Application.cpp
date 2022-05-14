#include "lmxpch.h"

#include "Application.h"

#include <imgui.h>

#include "Lumix/Renderer/Renderer.h"



#include "Input.h"

namespace LMX
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		LMX_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create({ "Lumix Engine" }));
		m_Window->SetEventCallback(LMX_BIND_EVENT_FN(Application::OnEvent));
		PushOverlay(new ImGuiLayer());
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LMX_BIND_EVENT_FN(Application::OnWindowClose));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	void Application::Run()
	{
		while (m_Running)
		{		
			float time = RenderCommand::GetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(timestep);
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}	
}
