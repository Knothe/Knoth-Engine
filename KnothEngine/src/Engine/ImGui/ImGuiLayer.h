#pragma once
#include "Engine/Core.h"
#include "Engine/Layer.h"

namespace Knoth {
	class KNOTH_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float _Time = 0.0f;
	};
}