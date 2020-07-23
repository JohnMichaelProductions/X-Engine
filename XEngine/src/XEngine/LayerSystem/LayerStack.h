#pragma once
#include <vector>
#include "XEngine/Core/XCore.h"
#include "XEngine/LayerSystem/Layer.h"
namespace XEngine
{
	class LayerStack
	{
	public:
		// Defined in Source File
		LayerStack() = default;
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);
		// Prototype in Header File
		std::vector<Layer*>::iterator begin()
			{ return layerstackLayers.begin(); }
		std::vector<Layer*>::iterator end()
			{ return layerstackLayers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin()
			{ return layerstackLayers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend()
			{ return layerstackLayers.rend(); }
		std::vector<Layer*>::const_iterator begin() const
			{ return layerstackLayers.begin(); }
		std::vector<Layer*>::const_iterator end() const
			{ return layerstackLayers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin() const
			{ return layerstackLayers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const
			{ return layerstackLayers.rend(); }
	private:
		std::vector<Layer*> layerstackLayers;
		unsigned int layerstackLayerInsertIndex = 0;
	};
}

