#pragma once
#include "UnrealRuby/Renderer/GraphicsContext.h"
 
struct GLFWwindow;

namespace UnrealRuby {

	class OpenGLContext: public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}