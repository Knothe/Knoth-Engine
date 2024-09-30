#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"

namespace Knoth {
	class KNOTH_API Application {
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		static inline Application& Get() { return *Instance; }
		inline Window& GetWindow() { return *_Window; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Knoth::Window> _Window;
		ImGuiLayer* _ImGuiLayer;
		bool _running = true;
		LayerStack _LayerStack;
		static Application* Instance;
		unsigned int _VertexArray, _VertexBuffer, _IndexBuffer;
	};

	Application* CreateApplication();
}