#pragma once

#include "EngineDefine.h"

// std & stl
#include <assert.h>
#include <chrono>
#include <filesystem>
#include <format>
#include <functional>
#include <memory>
#include <ranges>
#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <utility>
#include <vector>
#include <Windows.h>
#include <random>

using std::shared_ptr;
using std::string;
using std::map;
using std::unordered_map;
using std::vector;
using std::weak_ptr;

// DirectX & Direct3D & Microsoft
#include <wrl.h>
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

// 추가 외부 라이브러리
#include <DirectXTex.h>
#include <box2d.h>

using Microsoft::WRL::ComPtr;