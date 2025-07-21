#pragma once

enum class CB_TYPE
{
	TRANSFORM,
	MATERIAL,

	CB_END,
};

enum class RS_TYPE
{
	CULL_BACK,  // �޸�(�ݽð�) �ø�
	CULL_FRONT, // �ո�(�ð�) �ø�
	CULL_NONE,  // ��, �޸� ��� �ø����� ����
	WIRE_FRAME, // ���������� ���θ� ������ + CULL_NONE
	END,
};

enum class DS_TYPE
{
	LESS,				// ����Ÿ�ٿ� ��ϵ� ���̺��� �ڽ��� ���̰� �� ������, ���̴� ���
	GREATER,			// ����Ÿ���� ��ϵ� ���̺��� �ڽ��� ���̰� �� �ֶ�, ���̴� ���
	NO_TEST,			// ���̰˻縦 �������� ����, ���̴� ���
	NO_WRITE,			// ���� �˻�� Less �� ����, ���̴� ������� ����
	NO_TEST_NO_WRITE,	// ���̰˻縦 �������� ����, ���̸� ������� ����
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
	TRANSFORM,		// ��ġ (��ǥ, ũ��, ȸ��) 
	CAMERA,			// ī�޶�(����) ���
	COLLIDER2D,		// 2D �浹ü, OBB
	COLLIDER3D,		// 3D �浹ü,
	LIGHT2D,		// 2D ����
	LIGHT3D,		// 3D ����

	// Rendering
	MESHRENDER,			// �⺻ ������ ������Ʈ
	SPRITE_RENDER,		// Sprite ������
	FLIPBOOK_RENDER,	// Flipbook �ִϸ��̼� ������
	TILE_RENDER,		// Ÿ�ϸ� ������
	PRATICLE_RENDER,	// ���� �ùķ��̼� �� ������
	SKYBOX,				// 3D ��� ������
	DECAL,				// ���� ���� ����
	LANDSCAPE,			// ���� ���� �� ������

	END,

	SCRIPT,				// �뺻
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
	DOMAIN_OPAQUE,		// ������
	DOMAIN_MASKED,		// �������� or ������ �ش������� ���
	DOMAIN_TRANSPARENT, // ������
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