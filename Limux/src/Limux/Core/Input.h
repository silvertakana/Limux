#pragma once

#include "Limux/Core/Core.h"
#include "glm/glm.hpp"
#include "Limux/Core/KeyCodes.h"
#include "Limux/Core/MouseCodes.h"

namespace LMX
{
	class LMX_API Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		
		inline static bool IsKeyPressed(KeyCode key) { return s_Instance->IsKeyPressedImpl(key); }

		inline static bool IsMouseButtonPressed(MouseCode button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
		inline static std::pair<float, float> SetMousePosition(float x, float y) { return s_Instance->SetMousePositionImpl(x,y); }
		inline static float SetMouseX(float x) { return s_Instance->SetMouseXImpl(x); }
		inline static float SetMouseY(float y) { return s_Instance->SetMouseYImpl(y); }
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
		inline static void SetInputMode(InputType inptype, InputMode mode){return s_Instance->SetInputModeImpl(inptype, mode);}
	protected:
		virtual bool IsKeyPressedImpl(KeyCode key) = 0;

		virtual bool IsMouseButtonPressedImpl(MouseCode button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
		virtual std::pair<float, float> SetMousePositionImpl(float x, float y) = 0;
		virtual float SetMouseXImpl(float x) = 0;
		virtual float SetMouseYImpl(float y) = 0;
		virtual void SetInputModeImpl(InputType inptype, InputMode mode) = 0;
	private:
		static Scope<Input> s_Instance;
	};

}