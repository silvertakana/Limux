#pragma once
#include "Lumix/Core/Layer.h"

#include "Lumix/Events/ApplicationEvent.h"
#include "Lumix/Events/KeyEvent.h"
#include "Lumix/Events/MouseEvent.h"

namespace LMX
{
	class LMX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private: 
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};
}

