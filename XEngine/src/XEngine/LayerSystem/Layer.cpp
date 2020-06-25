#include "Xpch.h"
#include "Layer.h"
namespace XEngine
{
	Layer::Layer(const std::string& debugName) : layerDebugName(debugName)
		{ XCORE_TRACE("{0} has been created", layerDebugName); }
	Layer::~Layer()
		{ XCORE_TRACE("{0} has been destroyed", layerDebugName); }

}