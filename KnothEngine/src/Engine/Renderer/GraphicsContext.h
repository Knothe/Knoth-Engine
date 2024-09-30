#pragma once
#include "Engine/Core.h"

namespace Knoth {
	class KNOTH_API GraphicsContext {
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}