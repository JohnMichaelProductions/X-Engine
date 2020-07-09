#include "Xpch.h"
#include "Shader.h"
#include "Renderer/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
namespace XEngine
{
	Shader* Shader::Create(const std::string& vertexShader, const std::string& fragmentShader)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None: 
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertexShader, fragmentShader);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	std::string Shader::ConvertShader(const std::string& shaderFilestream)
	{
		std::ifstream stream;
		stream.open(shaderFilestream);
		std::stringstream fileContents;
		fileContents << stream.rdbuf();
		return fileContents.str();
	}

}