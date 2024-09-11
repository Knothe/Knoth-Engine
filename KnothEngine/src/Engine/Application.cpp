#include "knothpch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

namespace Knoth {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application() {
		KNOTH_CORE_ASSERT(!Instance, "Application already exists!");
		Instance = this;
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (_running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : _LayerStack)
				layer->OnUpdate();
			_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		if (e.GetEventType() == EventType::WindowClose) {
			OnWindowClosed(*(WindowCloseEvent*)&e);
		}
		//LOG("{0}", e.ToString());

		for (auto it = _LayerStack.end(); it != _LayerStack.begin();) {
			int i;
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::PushLayer(Layer* layer){
		_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay){
		_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e){
		_running = false;
		return true;
	}
}

