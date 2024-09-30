#include "knothpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Knoth {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _WindowHandle(windowHandle) {
		KNOTH_ASSERT(_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init(){
		glfwMakeContextCurrent(_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		KNOTH_ASSERT(status, "Failed to initialize Glad!");
		KNOTH_INFO("    Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		KNOTH_INFO("    Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		KNOTH_INFO("    Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers(){
		
		glfwSwapBuffers(_WindowHandle);
	}
}