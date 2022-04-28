#pragma once

#include "Lumix/Core/Core.h"
#include "Lumix/Events/Event.h"
#include "Layer.h"

namespace LMX
{
	class LMX_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		size_t m_LayerInsertIndex = 0;
	};

}