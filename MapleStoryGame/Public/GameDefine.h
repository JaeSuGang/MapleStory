#pragma once

#ifdef  _WIN32
#ifdef GAME_EXPORTS
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif //  _WIN32
#endif // 