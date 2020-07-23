#include "Xpch.h"
#include "XEngine/LayerSystem/LayerStack.h"
namespace XEngine
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : layerstackLayers)
		{
			layer->OnDetach();
			delete layer;
		}
	}
	void LayerStack::PushLayer(Layer* layer) 
	{ 
		layerstackLayers.emplace(layerstackLayers.begin() + layerstackLayerInsertIndex, layer);
		layerstackLayerInsertIndex++;
	}
	void LayerStack::PushOverlay(Layer* overlay) 
	{
		layerstackLayers.emplace_back(overlay);
	}
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layerstackLayers.begin(), layerstackLayers.end(), layer);
		if (it != layerstackLayers.end())
		{
			layerstackLayers.erase(it);
			layerstackLayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layerstackLayers.begin(), layerstackLayers.end(), overlay);
		if (it != layerstackLayers.end())
			layerstackLayers.erase(it);
	}
}