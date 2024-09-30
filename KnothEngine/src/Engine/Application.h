#pragma once
#include "Core.h"
#include "Event/ApplicationEvent.h"
#include "Event/Event.h"
#include "Engine/Window.h"
#include "Engine/LayerStack.h"
#include "Engine/ImGui/ImGuiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"
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

		std::shared_ptr<Shader> _Shader;
		std::shared_ptr<VertexArray> _VertexArray;

		std::shared_ptr<VertexArray> _SquareVA;
		std::shared_ptr<Shader> _Shader2;
	};

	Application* CreateApplication();
}