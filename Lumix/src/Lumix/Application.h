#pragma once
#include "Core.h"
namespace LMX
{
	class LMX_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();	
	};

	Application* CreateApplication();
}
