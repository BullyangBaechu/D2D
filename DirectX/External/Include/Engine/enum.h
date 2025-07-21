#pragma once

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,

	CB_END,
};

enum class RS_TYPE
{
	CULL_BACK,  // 뒷면(반시계) 컬링
	CULL_FRONT, // 앞면(시계) 컬링
	CULL_NONE,  // 앞, 뒷면 모두 컬링하지 않음
	WIRE_FRAME, // 정점사이의 라인만 렌더링 + CULL_NONE
	END,
};

enum class DS_TYPE
{
	LESS,				// 깊이타겟에 기록된 깊이보다 자신의 깊이가 더 작을때, 깊이는 기록
	GREATER,			// 깊이타겟이 기록된 깊이보다 자신의 깊이가 더 멀때, 깊이는 기록
	NO_TEST,			// 깊이검사를 수행하지 않음, 깊이는 기록
	NO_WRITE,			// 깊이 검사는 Less 로 수행, 깊이는 기록하지 않음
	NO_TEST_NO_WRITE,	// 깊이검사를 수행하지 않음, 깊이를 기록하지 않음
	END,
};

enum class BS_TYPE
{
	DEFAULT,		// (SrcRGB x 1)			+	(DstRGB * 0) 
	ALPHABLEND,		// (SrcRGB x SrcAlpha)	+	(DstRGB * (1 - SrcAlpha))
	END,
};

enum ASSET_TYPE
{
	MESH,
	MESHDATA,
	PREFAB,
	MATERIAL,
	GRAPHICSHADER,
	COMPUTESHADER,
	LEVEL,
	TEXTURE,
	SOUND,
	SPRITE,
	FLIPBOOK,
	ASSET_END,
};
extern const char* ASSET_TYPE_STR[(UINT)ASSET_END];
extern const wchar_t* ASSET_TYPE_WSTR[(UINT)ASSET_END];


enum class COMPONENT_TYPE
{
	TRANSFORM,		// 위치 (좌표, 크기, 회전) 
	CAMERA,			// 카메라(시점) 기능
	COLLIDER2D,		// 2D 충돌체, OBB
	COLLIDER3D,		// 3D 충돌체,
	LIGHT2D,		// 2D 광원
	LIGHT3D,		// 3D 광원

	// Rendering
	MESHRENDER,			// 기본 렌더링 컴포넌트
	SPRITE_RENDER,		// Sprite 렌더링
	FLIPBOOK_RENDER,	// Flipbook 애니메이션 렌더링
	TILE_RENDER,		// 타일맵 렌더링
	PRATICLE_RENDER,	// 입자 시뮬레이션 및 렌더링
	SKYBOX,				// 3D 배경 렌더링
	DECAL,				// 문양 문신 맵핑
	LANDSCAPE,			// 지형 설계 및 렌더링

	END,

	SCRIPT,				// 대본
};
extern const char* COMPONENT_TYPE_STR[(UINT)COMPONENT_TYPE::END];
extern const wchar_t* COMPONENT_TYPE_WSTR[(UINT)COMPONENT_TYPE::END];

enum class DIR
{
	RIGHT,
	UP,
	FRONT,

	END,
};

enum SCALAR_PARAM
{
	INT_0,
	INT_1,
	INT_2,
	INT_3,

	FLOAT_0,
	FLOAT_1,
	FLOAT_2,
	FLOAT_3,

	VEC2_0,
	VEC2_1,
	VEC2_2,
	VEC2_3,

	VEC4_0,
	VEC4_1,
	VEC4_2,
	VEC4_3,

	MAT_0,
	MAT_1,
};

enum TEX_PARAM
{
	TEX_0,
	TEX_1,
	TEX_2,
	TEX_3,	
	TEX_4,
	TEX_5,
	TEX_END,
};

enum RENDER_DOMAIN
{
	DOMAIN_OPAQUE,		// 불투명
	DOMAIN_MASKED,		// 완전투명 or 불투명 극단적으로 양분
	DOMAIN_TRANSPARENT, // 반투명
};

enum class DEBUG_SHAPE
{
	// 2D
	RECT,
	CIRCLE,
	LINE,

	// 3D
	CUBE,
	SPHERE,
};

enum class TASK_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	CHANGE_LEVEL,
	CHANGE_LEVEL_STATE,
};