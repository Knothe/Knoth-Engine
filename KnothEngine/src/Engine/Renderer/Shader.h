#pragma once
#include "Engine/Core.h"

namespace Knoth {
	class KNOTH_API Shader {
	public:
		Shader(const std::string& vertexsrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t _RendererID;
	};
}