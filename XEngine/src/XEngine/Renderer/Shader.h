#pragma once
// C++ Libraries
#include <string>
namespace XEngine
{
	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();
		void Bind() const;
		void Unbind() const;
	private:
		uint32_t mainRendererID;
	};
	std::string ConvertShader(const std::string& shaderFilestream);
}