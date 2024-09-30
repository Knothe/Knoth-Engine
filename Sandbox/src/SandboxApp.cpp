#pragma once
#include <KnothEngine.h>
#include "ImGui/imgui.h"

class ExampleLayer : public Knoth::Layer {
public:
	ExampleLayer() : Layer("Example"){}

	virtual void OnEvent(Knoth::Event& e) override {
		KNOTH_LOG("{0}", e.ToString());
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();
	}
};

class Sandbox : public Knoth::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

Knoth::Application* Knoth::CreateApplication() {
	return new Sandbox();
}