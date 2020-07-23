// Source file for OpenGL Specific RenderAPI
#include "Xpch.h"
#include <GLAD/glad.h>
#include "Platforms/RenderingAPIs/OpenGL/OpenGLRendererAPI.h"
namespace XEngine
{
	void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id, unsigned severity, int length, const char* message, const void* userParam)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:
				XCORE_CRITICAL(message);
				return;
			case GL_DEBUG_SEVERITY_MEDIUM:
				XCORE_ERROR(message);
				return;
			case GL_DEBUG_SEVERITY_LOW:
				XCORE_WARN(message);
				return;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				XCORE_INFO(message);
				return;
		}
	}
	void OpenGLRendererAPI::Init()
	{
		XPROFILE_FUNCTION();
		#ifdef HZ_DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		#endif
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}
	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{ glViewport(x, y, width, height); }
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
		{ glClearColor(color.r, color.g, color.b, color.a); }
	void OpenGLRendererAPI::Clear()
		{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }
	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr); 
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	void OpenGLRendererAPI::Documentation()
	{
		printf("OPENGL RENDERER API DOCUMENTATION FUNCTION HAS BEEN CALLED!\n"
			"Functions\n"
			"SetClearColor(const glm::vec4& color): Set color of background using rgba vec 4\n"
			"\tExample: SetClearColor(0, 0, 1, 1);\n"
			"Clear(): Resets buffers\n"
			"DrawIndexed(const Ref<VertexArray>& vertexArray): Draws specified index array\n");
	}
}