#include "lmxpch.h"
#include "Limux/Core/Input.h"

#ifdef LMX_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace LMX
{

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
		#ifdef LMX_PLATFORM_WINDOWS
			return CreateScope<WindowsInput>();
		#else
			LMX_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}
}