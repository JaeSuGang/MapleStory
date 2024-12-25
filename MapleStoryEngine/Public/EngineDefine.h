#pragma once
#include <assert.h>
#include <Windows.h>

#ifdef  _WIN32
#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif //  _WIN32
#endif // 

#define CRITICAL_ERROR(text) { MessageBoxA(0, text, "Error", MB_OK); assert(false); };

#define ENGINE_INIT_ERROR_TEXT "Engine Init Failed"

#define INVALID_COMPONENT_ERROR_TEXT "Engine Init Failed"

#define TAG_CONTAINER_RESERVE_COUNT 100
#define REGISTERED_TAGS_RESERVE_COUNT 200
