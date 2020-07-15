#include "Xpch.h"
#include "XEngine/GraphicsSystem/Shader.h"
#include "XEngine/GraphicsSystem/Renderer/Renderer.h"
#include "Platforms/RenderingAPIs/OpenGL/OpenGLShader.h"
namespace XEngine
{
	// Shader Functions
	Ref<Shader> Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			XCORE_ASSERT(false, "RendererAPI::None is currently not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(path);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				XCORE_ASSERT(false, "RendererAPI::None is currently not supported");
				return nullptr;
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertexShader, fragmentShader);
		}
		XCORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
	// Shader Library Functions
	void ShaderLibrary::Add(Ref<Shader>& shader, const std::string& name)
	{
		XCORE_ASSERT(!Exists(name), "Shader already exists!");
		libraryShaders[name] = shader;
	}
	void ShaderLibrary::Add(Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(shader, name);
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& path)
	{
		auto shader = Shader::Create(path);
		Add(shader);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Load(const std::string& path, const std::string& name)
	{
		auto shader = Shader::Create(path);
		Add(shader, name);
		return shader;
	}
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		XCORE_ASSERT(Exists(name), "Shader not found!");
		return libraryShaders[name];
	}
	bool ShaderLibrary::Exists(const std::string& name) const
		{ return libraryShaders.find(name) != libraryShaders.end(); }
}