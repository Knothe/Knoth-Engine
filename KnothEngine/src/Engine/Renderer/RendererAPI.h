#pragma once
#include "Engine/Core.h"

#include <glm/glm.hpp>
#include "Engine/Renderer/VertexArray.h"

namespace Knoth {
	class KNOTH_API RendererAPI {
	public:
		enum class API_InUse {
			None = 0, OpenGL = 1
		};
		
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API_InUse GetAPI() { return API; }

	private:
		static API_InUse API;
	};
}