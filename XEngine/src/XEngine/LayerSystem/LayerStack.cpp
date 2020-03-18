// Top Files
#include "Xpch.h"
// Layer System Files
#include "LayerStack.h"
namespace XEngine
{
	LayerStack::LayerStack() {}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}
	void LayerStack::PushLayerStack(Layer* layer) 
	{ 
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer); 
		m_LayerInsertIndex++;
		XCORE_INFO("Added Layer to Layer Stack. Layey Index Count: {0}", m_LayerInsertIndex);
	}
	void LayerStack::PushOverlayStack(Layer* overlay) { m_Layers.emplace_back(overlay); }
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