#pragma once
#include "Engine/Core.h"
#include "Engine/Layer.h"

namespace Knoth {
	class KNOTH_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);

	private:
		float _Time = 0.0f;
	};
}