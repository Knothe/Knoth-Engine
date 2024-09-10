#pragma once
#include <KnothEngine.h>

class Sandbox : public Knoth::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Knoth::Application* Knoth::CreateApplication() {
	return new Sandbox();
}