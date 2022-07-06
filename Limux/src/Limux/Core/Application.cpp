#include "lmxpch.h"

#include "Application.h"
#include <imgui.h>
#include "Limux/Renderer/Renderer.h"
#include "Input.h"

namespace LMX
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& name)
	{
		LMX_PROFILE_FUNCTION();
		LMX_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		
		m_Window = Window::Create({ name });
		m_Window->SetEventCallback(LMX_BIND_EVENT_FN(Application::OnEvent));
		Renderer::Init();
		PushOverlay(m_ImGuiLayer = new ImGuiLayer());
	}
	void Application::PushLayer(Layer* layer)
	{
		LMX_PROFILE_FUNCTION();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		LMX_PROFILE_FUNCTION();
		m_LayerStack.PushOverlay(layer);
	}
	void Application::PopLayer(Layer* layer)
	{
		LMX_PROFILE_FUNCTION();
		m_LayerStack.PopLayer(layer);
	}
	void Application::PopOverlay(Layer * layer)
	{
		LMX_PROFILE_FUNCTION();
		m_LayerStack.PopOverlay(layer);
	}
	void Application::OnEvent(Event& e)
	{
		LMX_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(LMX_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(LMX_BIND_EVENT_FN(Application::OnWindowResize));
		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e, m_Timestep);
		}
	}
	void Application::Run()
	{
		LMX_PROFILE_FUNCTION();
		while (m_Running)
		{		
			LMX_PROFILE_SCOPE("RunLoop");
			float time = RenderCommand::GetTime();
			m_Timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			
			if (!m_Minimized)
			{
				LMX_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(m_Timestep);
			}
			
			m_ImGuiLayer->Begin();
			
			for (Layer* layer : m_LayerStack)
			{
				LMX_PROFILE_SCOPE("LayerStack OnImGUIRender");
				layer->OnImGuiRender(m_Timestep);
			}
			
			m_ImGuiLayer->End();
			m_Window->OnUpdate();
		}
	}
	void Application::Close()
	{
		m_Running = false;
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		LMX_PROFILE_FUNCTION();
		m_Running = false;
		return true;
	}	
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		LMX_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}
