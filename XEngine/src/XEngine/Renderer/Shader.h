#pragma once
#include <string>
namespace XEngine
{
	class Shader
	{
	public:
		// Defined in Souce File
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();
		void Bind() const;
		void Unbind() const;
	private:
		uint32_t shaderRendererID;
	};
	std::string ConvertShader(const std::string& shaderFilestream);
}