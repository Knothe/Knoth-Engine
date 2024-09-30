#pragma once
#include "knothpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Knoth {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API_InUse::None:
			KNOTH_ASSERT(false, "Render api none not supported!");
			return nullptr;
			break;
		case RendererAPI::API_InUse::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
			break;
		}
		KNOTH_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count){
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API_InUse::None:
			KNOTH_ASSERT(false, "Render api none not supported!");
			return nullptr;
			break;
		case RendererAPI::API_InUse::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
			break;
		}
		KNOTH_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}