#pragma once
#include <KnothEngine.h>

class ExampleLayer : public Knoth::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	void OnUpdate() override {
		LOG("ExampleLayer::Update");
	}

	void OnEvent(Knoth::Event& e) override {
		INFO("{0}", e.ToString());
	}
};

class Sandbox : public Knoth::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Knoth::ImGuiLayer());
	}

	~Sandbox() {

	}
};

Knoth::Application* Knoth::CreateApplication() {
	return new Sandbox();
}