#pragma once
#include "Limux/Core/Base.h"
#include "Limux/Events/Event.h"
#include "Timestep.h"
namespace LMX
{
	class LMX_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender(Timestep ts) {}
		virtual void OnEvent(Event& event, Timestep ts) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}