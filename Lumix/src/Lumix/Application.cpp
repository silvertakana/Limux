#include "lmxpch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Lumix/Log.h"
namespace LMX
{
	Application::Application()
	{}

	Application::~Application()
	{}

	void Application::Run()
	{
		WindowResizeEvent e(180, 100);
		LMX_INFO("{0}", e.ToString());
		while (true);
	}
}
