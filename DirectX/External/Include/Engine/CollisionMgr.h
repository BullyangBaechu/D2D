#pragma once


union COLLIDER_ID
{
	struct
	{
		UINT Left;
		UINT Right;
	};
	DWORD_PTR ID;
};


class CollisionMgr
	: public singleton<CollisionMgr>
{
	SINGLE(CollisionMgr);
private:
	UINT					m_Matrix[MAX_LAYER];
	map<DWORD_PTR, bool>	m_mapColInfo;

public:
	void CollisionCheck(UINT _Left, UINT _Right);
	void CollisionCheckClear() 	{ memset(m_Matrix, 0, sizeof(UINT) * MAX_LAYER); }

public:
	void Tick();

private:
	void CollisionProcess(class CCollider2D* _left, CCollider2D* _Right);
	void CollisionBtwLayer(UINT _Left, UINT _Right);
	bool IsOverlap(class CCollider2D* _Left, class CCollider2D* _Right);
};

