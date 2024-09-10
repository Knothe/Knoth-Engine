#pragma once

#include "Event.h"

namespace Knoth {
	class KNOTH_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return _KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode) : _KeyCode(keycode){}

		int _KeyCode;
	};

	class KNOTH_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, int repeateCount)
			: KeyEvent(keycode), _RepeatCount(repeateCount) {}

		inline int GetRepeatCount() const { return _RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode << " (" << _RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	protected:
		int _RepeatCount;
	};

	class KNOTH_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString()const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}