#pragma once
#include "Engine/Core.h"

#include "RenderCommand.h"

namespace Knoth {
	class KNOTH_API Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API_InUse GetAPI() { return RendererAPI::GetAPI(); }
	};

	
}