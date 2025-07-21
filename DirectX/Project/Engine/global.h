#pragma once


#include <Windows.h>
#include <stdlib.h>

// Directx11 ���̺귯��
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

// DirectxTex ���̺귯��
#include <DirectxTex/DirectXTex.h>
#include <DirectxTex/DirectXTex.inl>

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_debug.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#endif
using namespace DirectX;


// FileSystem (ǥ�� C++17)
#include <filesystem>
using namespace std::filesystem;

// Ŭ���� or ������ü virtual �Լ��� �����ؾ��Ѵ�.
#include <typeinfo>

// STD �����̳�
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


// Engine ���
#include "singleton.h"
#include "define.h"
#include "enum.h"
#include "struct.h"
#include "Ptr.h"
#include "func.h"

