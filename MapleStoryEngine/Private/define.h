#pragma once
#include <Windows.h>
#include <assert.h>

#define CRITICAL_ERROR(text) { MessageBoxA(0, text, "Error", MB_OK); assert(false); };