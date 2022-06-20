#include "lmxpch.h"
#include "Limux/Core/Window.h"

#ifdef LMX_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace LMX
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
		#ifdef LMX_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
		#else
		LMX_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
		#endif
	}

}