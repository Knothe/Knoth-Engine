#pragma once
#include "knothpch.h"
#include "Engine/Core.h"

namespace Knoth {
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	}; 

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)	virtual int GetCategoryFlags() const override { return category; }

	class KNOTH_API Event {
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		} 
	protected:
		bool m_Handled = false;
	};

	
}

template<>
struct std::formatter<Knoth::Event> {
	constexpr auto parse(auto& ctx) {
		auto it = ctx.begin();
		if (it == ctx.end())
			return it;
		if (it != ctx.end() && *it != '}') {
			throw std::format_error("Invalid ARGS-Event");
		}
		return it;
	}

	auto format(const Knoth::Event& p, auto& ctx) const {
		return std::format_to(ctx.out(), "{}", p.ToString());
	}
};