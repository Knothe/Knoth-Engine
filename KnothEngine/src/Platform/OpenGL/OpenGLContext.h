#pragma once
#include "Engine/Core.h"
#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Knoth {
	class KNOTH_API OpenGLContext : public GraphicsContext {
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* _WindowHandle;
	};
}