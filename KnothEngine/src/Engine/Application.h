#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "Engine/Window.h"

namespace Knoth {
	class KNOTH_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Knoth::Window> _Window;
		bool _running = true;
	};

	Application* CreateApplication();
}