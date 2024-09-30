#pragma once
#include "Engine/Core.h"
#include "Engine/Renderer/RendererAPI.h"

namespace Knoth {
	class KNOTH_API OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}