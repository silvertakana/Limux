#pragma once

#include "Limux/Core/Base.h"
#include "glm/glm.hpp"
#include "Limux/Core/KeyCodes.h"
#include "Limux/Core/MouseCodes.h"

namespace LMX
{
	class LMX_API Input
	{
	public:
		
		static bool IsKeyPressed(KeyCode key);

		
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		
		static std::pair<float, float> SetMousePosition(float x, float y);
		static float SetMouseX(float x);
		static float SetMouseY(float y);

		enum class InputType
		{
			CURSOR,
		};
		enum class InputMode
		{
			CURSOR_NORMAL,
			CURSOR_HIDDEN,
			CURSOR_DISABLED
		};
		static void SetInputMode(InputType inptype, InputMode mode);
	};

}