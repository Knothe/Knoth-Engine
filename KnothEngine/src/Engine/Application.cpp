#include "knothpch.h"
#include "Application.h"
#include "Log.h"
#include <GLFW/glfw3.h>


namespace Knoth {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application() {
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (_running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e) {
		if (e.GetEventType() == EventType::WindowClose) {
			OnWindowClosed(*(WindowCloseEvent*)&e);
		}
		LOG("{0}", e.ToString());
	}
	bool Application::OnWindowClosed(WindowCloseEvent& e){
		_running = false;
		return true;
	}
}

