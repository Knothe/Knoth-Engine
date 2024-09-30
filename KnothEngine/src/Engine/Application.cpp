#include "knothpch.h"
#include "Application.h"
#include <glad/glad.h>
#include "Engine/Renderer/Renderer.h"

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

		_VertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> triangleVB;
		triangleVB.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		{
			BufferLayout layout = {
				{ShaderDataType::Float3, "a_Position"},
				{ShaderDataType::Float4, "a_Color"}
			};

			triangleVB->SetLayout(layout);
		}
		_VertexArray->AddVertexBuffer(triangleVB);
		uint32_t indices[3] = {
			0, 1, 2
		};

		std::shared_ptr<IndexBuffer> triangleIB;
		triangleIB.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		_VertexArray->SetIndexBuffer(triangleIB);

		_SquareVA.reset(VertexArray::Create());
		float sqrvertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(sqrvertices, sizeof(sqrvertices)));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "a_Position"}
			});
		_SquareVA->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = {
			0, 1, 2, 2, 3, 0
		};
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
				v_Color = a_Color;
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;		
			in vec4 v_Color;

			void main(){
				color = v_Color;
			}
		)";

		_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string vertexSrc2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main(){
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;
			in vec3 v_Position;		

			void main(){
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";
		_Shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (_running) {
			RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			_Shader2->Bind();
			Renderer::Submit(_SquareVA);

			_Shader->Bind();
			Renderer::Submit(_VertexArray);

			Renderer::EndScene();

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

