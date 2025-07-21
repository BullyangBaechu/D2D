#pragma once


#include <Windows.h>
#include <stdlib.h>

// Directx11 라이브러리
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <wrl.h>

#include "SimpleMath.h"
using namespace DirectX::SimpleMath;
using namespace DirectX::PackedVector;
using namespace Microsoft::WRL;

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")

// DirectxTex 라이브러리
#include <DirectxTex/DirectXTex.h>
#include <DirectxTex/DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#endif
using namespace DirectX;


// FileSystem (표준 C++17)
#include <filesystem>
using namespace std::filesystem;

// 클래스 or 구조에체 virtual 함수가 존재해야한다.
#include <typeinfo>

// STD 컨테이너
#include <vector>
#include <list>
#include <map>
#include <string>

using std::vector;
using std::list;
using std::map;
using std::make_pair;
using std::string;
using std::wstring;


// Engine 헤더
#include "singleton.h"
#include "define.h"
#include "enum.h"
#include "struct.h"
#include "Ptr.h"
#include "func.h"

