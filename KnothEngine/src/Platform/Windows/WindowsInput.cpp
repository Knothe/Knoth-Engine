#include "knothpch.h"
#include "WindowsInput.h"

#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Knoth {
#define GET_GLFW_WINDOW() const auto& window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

	Input* Input::_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) {
		GET_GLFW_WINDOW();
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) {
		GET_GLFW_WINDOW();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		GET_GLFW_WINDOW();
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return std::pair<float, float>(xPos, yPos);
	}

	float WindowsInput::GetMouseXImpl() {
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() {
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}