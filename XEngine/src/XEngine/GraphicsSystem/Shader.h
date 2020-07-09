#pragma once
namespace XEngine
{
	class Shader
	{
	public:
		// Defined in Souce File
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		static Shader* Create(const std::string& vertexShader, const std::string& fragmentShader);
		static std::string ConvertShader(const std::string& shaderFilestream);
	private:
		uint32_t shaderRendererID;
	};
}