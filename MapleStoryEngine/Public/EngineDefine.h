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

#define DEFAULT_PIXEL_SHADER_NAME "PSDefault"
#define TRANSPARENT_PIXEL_SHADER_NAME "PSTransparent"
#define BOX_OUTLINED_GREEN_PIXEL_SHADER_NAME "PSBoxOutlinedGreen"
#define WIREFRAME_PIXEL_SHADER_NAME "PSWireframe"
#define GREEN_PIXEL_SHADER_NAME "PSGreen"

#define RESOURCES_FOLDER_NAME "Resources"
#define TEXTURES_FOLDER_NAME "Resources\\Textures"
#define MISSING_TEXTURE_PATH "Resources\\Textures\\MissingTexture.png"
#define VSShader_PATH "Resources\\Shaders\\Shader_VS.hlsl"
#define PSShader_PATH "Resources\\Shaders\\Shader_PS.hlsl"

/* 상수 값 */
#define DEFAULT_WINDOW_SIZE_X 1366.0f
#define DEFAULT_WINDOW_SIZE_Y 768.0f
#define TAG_CONTAINER_RESERVE_COUNT 100
#define REGISTERED_TAGS_RESERVE_COUNT 200

/* 에러 문자열 */
#define DEFAULT_ERROR_TEXT "Error Occured"

#define RESOURCE_FIND_FAILED_TEXT "Failed To Find Resource"
#define RESOURCE_FOLDER_FIND_FAILED_TEXT "Failed To Find Resource Folder"

#define ENGINE_INIT_ERROR_TEXT "Engine Init Failed"
#define INVALID_COMPONENT_ERROR_TEXT "Engine Init Failed"
#define BUFFER_CREATE_FAILED_TEXT "Buffer Creation Failed"
