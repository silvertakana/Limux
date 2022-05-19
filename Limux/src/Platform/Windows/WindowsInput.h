#pragma once

#include "Limux/Core/Input.h"

namespace LMX
{

	class WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
			
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
		virtual std::pair<float, float> SetMousePositionImpl(float x, float y) override;
		virtual float SetMouseXImpl(float x) override;
		virtual float SetMouseYImpl(float y) override;
		virtual void SetInputModeImpl(InputType inptype, InputMode mode) override;
	};

}