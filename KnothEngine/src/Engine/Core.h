#pragma once

#ifdef KNOTH_PLATFORM_WINDOWS
	#ifdef KNOTH_BUILD_DLL
		#define KNOTH_API __declspec(dllexport)
	#else
		#define KNOTH_API __declspec(dllimport)
	#endif
#else
	#error Only support windows
#endif

#ifdef KNOTH_DEBUG
	#define KNOTH_ENABLE_ASSERTS
#endif

#ifdef KNOTH_ENABLE_ASSERTS
	#define KNOTH_ASSERT(x, ...) {if(!(x)){KNOTH_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define KNOTH_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define KNOTH_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)