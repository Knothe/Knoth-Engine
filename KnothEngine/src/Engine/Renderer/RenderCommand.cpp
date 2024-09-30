#include "knothpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Knoth {
	RendererAPI* RenderCommand::_RendererAPI = new OpenGLRendererAPI;
}