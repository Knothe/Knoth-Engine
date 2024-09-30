#include "knothpch.h"
#include "Application.h"
#include "Log.h"
#include <glad/glad.h>

namespace Knoth {
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::Instance = nullptr;

	Application::Application() {
		KNOTH_ASSERT(!Instance, "Application already exists!");
		Instance = this;
		_Window = std::unique_ptr<Window>(Window::Create());
		_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		_ImGuiLayer = new ImGuiLayer();
		PushOverlay(_ImGuiLayer);

		glGenVertexArrays(1, &_VertexArray);
		glBindVertexArray(_VertexArray);

		glGenBuffers(1, &_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, _VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IndexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (_running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : _LayerStack)
				layer->OnUpdate();

			_ImGuiLayer->Begin();
			for (Layer* layer : _LayerStack)
				layer->OnImGuiRender();
			_ImGuiLayer->End();

			_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		e.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));
		_ImGuiLayer->PreEvent(e);
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

