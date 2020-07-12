#pragma once
#include <string>
#include <unordered_map>
namespace XEngine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual const std::string& GetName() const = 0;
		static Ref<Shader> Create(const std::string& path);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader);
	private:
		uint32_t shaderRendererID;
	};
	class ShaderLibrary
	{
	public:
		// Defined in source file
		void Add(Ref<Shader>& shader, const std::string& name);
		void Add(Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& path);
		Ref<Shader> Load(const std::string& path, const std::string& name);
		Ref<Shader>Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> libraryShaders;
	};
}