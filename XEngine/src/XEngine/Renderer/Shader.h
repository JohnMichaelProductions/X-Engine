#pragma once
#include <string>
#include <glm/glm.hpp>
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
		void UploadUniformFloat4(const std::string name, const glm::vec4& values);
		void UploadUniformMat4(const std::string name, const glm::mat4& matrix);
	private:
		uint32_t shaderRendererID;
	};
	std::string ConvertShader(const std::string& shaderFilestream);
}