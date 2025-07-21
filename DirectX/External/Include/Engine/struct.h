#pragma once


// 정점 구조체
struct Vtx
{
	Vec3	vPos;
	Vec2	vUV;
	Vec4	vColor;
};


struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			Pos;
	Vec3			Scale;
	Vec3			Rot;
	Matrix			matWorld;

	Vec4			Color;
	bool			DepthTest; 

	float			CurTime;
	float			Duration;
};


struct tTaskInfo
{
	TASK_TYPE Type;
	DWORD_PTR Param_0;
	DWORD_PTR Param_1;
};



// Transform 구조체
struct tTransform
{
	Matrix	matWorld;
	Matrix	matView;  
	Matrix	matProj; 
	
	Matrix	matWV;
	Matrix	matWVP;
};
extern tTransform g_Trans;

struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[2];
};


