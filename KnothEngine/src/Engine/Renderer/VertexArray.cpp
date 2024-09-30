#include "knothpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Knoth {
	VertexArray* VertexArray::Create(){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API_InUse::None:
			KNOTH_ASSERT(false, "Render api none not supported!");
			return nullptr;
			break;
		case RendererAPI::API_InUse::OpenGL:
			return new OpenGLVertexArray();
			break;
		}
		KNOTH_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}