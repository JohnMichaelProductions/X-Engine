#include "Xpch.h"
#include "LayerStack.h"
namespace XEngine
{
	LayerStack::LayerStack() 
		{ XCORE_INFO("Layer Stack has been created"); }
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
		XCORE_INFO("Layer Stack and all layers have been destroyed");
	}
	void LayerStack::PushLayer(Layer* layer) 
	{ 
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer); 
		m_LayerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) 
		{ m_Layers.emplace_back(overlay); }
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}
}