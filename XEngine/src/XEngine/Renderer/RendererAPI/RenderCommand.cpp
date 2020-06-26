// Render Command Source File
#include "Xpch.h"
#include "RenderCommand.h"
#include "Platforms/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
	{ RendererAPI* RenderCommand::renderCommandAPI = new OpenGLRendererAPI; }