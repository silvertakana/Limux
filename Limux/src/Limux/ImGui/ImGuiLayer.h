#pragma once
#include "Limux/Core/Layer.h"

#include "Limux/Events/ApplicationEvent.h"
#include "Limux/Events/KeyEvent.h"
#include "Limux/Events/MouseEvent.h"

namespace LMX
{
	class LMX_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e, Timestep ts) override;
		virtual void OnImGuiRender(Timestep ts) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }

		void SetDarkThemeColors();
	private: 
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}

