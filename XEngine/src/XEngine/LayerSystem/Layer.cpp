#include "Xpch.h"
#include "Layer.h"
namespace XEngine
{
	Layer::Layer(const std::string& name) : layerDebugName(name)
		{ XCORE_INFO("{0} has been created", layerDebugName); }
	Layer::~Layer()
		{ XCORE_INFO("{0} has been destroyed", layerDebugName); }

}