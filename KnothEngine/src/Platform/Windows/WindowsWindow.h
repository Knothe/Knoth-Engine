#pragma once

#include "Engine/Core.h"
#include "Engine/Window.h"
#include "Engine/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>

namespace Knoth {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return _Data.Width; }
		inline unsigned int GetHeight() const override { return _Data.Height; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { _Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return _Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* _Window;
		GraphicsContext* _Context;

		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData _Data;
	};
}