#pragma once
#include "Engine/Core.h"

namespace Knoth {
	template<class T1, class T2> struct pair;

	class KNOTH_API Input {
	public:
		inline static bool IsKeyPressed(int keycode) { return _Instance->IsKeyPressedImpl(keycode); }
		inline static bool IsMouseButtonPressed(int button) { return _Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePos() { return _Instance->GetMousePosImpl(); }
		inline static float GetMouseX() { return _Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return _Instance->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* _Instance;
	};
}