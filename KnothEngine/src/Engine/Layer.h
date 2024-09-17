#pragma once
#include "Engine/Core.h"
#include "Engine/Event/Event.h"

namespace Knoth {
	class KNOTH_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach(){}
		virtual void OnDetach(){}
		virtual void OnUpdate(){}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e){}

		inline const std::string& GetName() const { return _DebugName; }

	protected:
		std::string _DebugName;
	};
}