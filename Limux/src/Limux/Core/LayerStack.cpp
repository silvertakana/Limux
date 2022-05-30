#include "lmxpch.h"
#include "LayerStack.h"

namespace LMX
{

	LayerStack::LayerStack()
	{
		LMX_PROFILE_FUNCTION();
	}

	LayerStack::~LayerStack()
	{
		LMX_PROFILE_FUNCTION();
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		LMX_PROFILE_FUNCTION();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		LMX_PROFILE_FUNCTION();
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		LMX_PROFILE_FUNCTION();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		LMX_PROFILE_FUNCTION();
		overlay->OnDetach();
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}

}