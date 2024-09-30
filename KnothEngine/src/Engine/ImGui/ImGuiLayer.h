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

		void PreEvent(Event& e);

		void Begin();
		void End();

	private:
		bool ConsumeKeyboardEvent(Event& e);
		bool ConsumeMouseEvent(Event& e);

		float _Time = 0.0f;
	};
}