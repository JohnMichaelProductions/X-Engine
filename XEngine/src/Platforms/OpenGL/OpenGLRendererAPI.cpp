// Source file for OpenGL Specific RenderAPI
#include "Xpch.h"
#include "OpenGLRendererAPI.h"
#include <GLAD/glad.h>
namespace XEngine
{
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{ glClearColor(color.r, color.g, color.b, color.a); }
	void OpenGLRendererAPI::Clear()
		{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{ glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); }
	void OpenGLRendererAPI::Documentation()
	{
		printf("OPENGL RENDERER API DOCUMENTATION FUNCTION HAS BEEN CALLED!\n"
			"Functions\n"
			"SetClearColor(const glm::vec4& color): Set color of background using rgba vec 4\n"
			"\tExample: SetClearColor(0, 0, 1, 1);\n"
			"Clear(): Resets buffers\n"
			"DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray): Draws specified index array\n");
	}
}