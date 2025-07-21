#include "pch.h"
#include "CollisionMgr.h"

#include "LevelMgr.h"
#include "ALevel.h"
#include "Layer.h"
#include "GameObject.h"
#include "CCollider2D.h"

#include "AssetMgr.h"
#include "AMesh.h"

CollisionMgr::CollisionMgr()
    : m_Matrix{}
{

}

CollisionMgr::~CollisionMgr()
{

}

void CollisionMgr::CollisionCheck(UINT _Left, UINT _Right)
{
    UINT Row = _Left;
    UINT Col = _Right;

    if (Row > Col)
    {
        Row = _Right;
        Col = _Left;
    }

    m_Matrix[Row] ^= (1 << Col);
}

void CollisionMgr::Tick()
{
    for (UINT Row = 0; Row < MAX_LAYER; ++Row)
    {
        for (UINT Col = Row; Col < MAX_LAYER; ++Col)
        {
            if (!(m_Matrix[Row] & (1 << Col)))
                continue;

            CollisionBtwLayer(Row, Col);
        }
    }
}

void CollisionMgr::CollisionBtwLayer(UINT _Left, UINT _Right)
{
    // 현재 레벨에 접근
    ALevel* pLevel = LevelMgr::GetInst()->GetCurrentLevel().Get();

    // 충돌시킬 두 Layer 가져옴
    Layer* pLeftLayer = pLevel->GetLayer(_Left).Get();
    Layer* pRightLayer = pLevel->GetLayer(_Right).Get();

    const vector<Ptr<GameObject>>& vecLeftObj = pLeftLayer->GetObjects();
    const vector<Ptr<GameObject>>& vecRightObj = pRightLayer->GetObjects();

    // 서로 다른 두 레이어간의 충돌체끼리 검사를 1:1 로 진행하는 경우
    if (_Left != _Right)
    {
        for (size_t i = 0; i < vecLeftObj.size(); ++i)
        {
            if (nullptr == vecLeftObj[i]->Collider2D())
                continue;

            for (size_t j = 0; j < vecRightObj.size(); ++j)
            {
                if (nullptr == vecRightObj[j]->Collider2D())
                    continue;

                CollisionProcess(vecLeftObj[i]->Collider2D().Get(), vecRightObj[j]->Collider2D().Get());
            }
        }
    }

    // 동일 레이어 내부에서 자기들 끼리 충돌 검사를 진행해야 하는경우 인덱스 예외처리
    else
    {
        for (size_t i = 0; i < vecLeftObj.size(); ++i)
        {
            if (nullptr == vecLeftObj[i]->Collider2D())
                continue;

            for (size_t j = i + 1; j < vecRightObj.size(); ++j)
            {
                if (nullptr == vecRightObj[j]->Collider2D())
                    continue;

                CollisionProcess(vecLeftObj[i]->Collider2D().Get(), vecRightObj[j]->Collider2D().Get());
            }
        }
    }
}

void CollisionMgr::CollisionProcess(CCollider2D* _Left, CCollider2D* _Right)
{
    // 두 충돌체가 이전프레임에도 충돌중이었는지 확인하기위해서, 이전프레임 충돌정보를 검색한다.
    COLLIDER_ID ColID;
    ColID.Left = _Left->GetID();
    ColID.Right = _Right->GetID();
    map<DWORD_PTR, bool>::iterator iter = m_mapColInfo.find(ColID.ID);

    if (iter == m_mapColInfo.end())
    {
        m_mapColInfo.insert(make_pair(ColID.ID, false));
        iter = m_mapColInfo.find(ColID.ID);
    }

    // 두 충돌체 중 둘중 하나라도 Dead 상태인지 확인한다.
    bool IsDead = false;
    if (_Left->IsDead() || _Right->IsDead())
        IsDead = true;


    // 충돌체를 보유하고 있는 두 오브젝트의 충돌검사를 진행한다.
    // 현재 충돌중이다
    if (IsOverlap(_Left, _Right))
    {
        // 이전에도 충돌중어었다
        if (iter->second)
        {
            if (IsDead)
            {
                _Left->EndOverlap(_Right);
                _Right->EndOverlap(_Left);
            }
            else
            {
                _Left->Overlap(_Right);
                _Right->Overlap(_Left);
            }
        }

        // 이전에는 충돌중이지 않았다.
        else
        {
            if (!IsDead)
            {
                _Left->BeginOverlap(_Right);
                _Right->BeginOverlap(_Left);
            }
        }
        iter->second = true;
    }

    // 현재 충돌하고 있지 않다
    else
    {
        if (iter->second)
        {
            _Left->EndOverlap(_Right);
            _Right->EndOverlap(_Left);
        }

        iter->second = false;
    }
}

bool CollisionMgr::IsOverlap(CCollider2D* _Left, CCollider2D* _Right)
{
    // 분리축 이론
    // RectMesh의 로컬공간의 모델 좌표를 해당 충돌체의 월드행렬을 곱해서 
    // 월드상의 해당 충돌체의 4개의 꼭지점 위치를 알 수 있다.
    AMesh* pRectMesh = AssetMgr::GetInst()->Find<AMesh>(L"RectMesh").Get();
    const Vtx* pVtx = pRectMesh->GetVtxSysyMem();

    // 두 충돌체의 월드행렬을 가져온다.
    const Matrix& matLeftWorld = _Left->GetWorldMat();
    const Matrix& matRightWorld = _Right->GetWorldMat();

    // 로컬공간의 메쉬의 정점을 각 충돌체의 꼭지점과 중심점으로 이동시켜서
    // 월드상의 충돌체의 위치를 알아낸다.
    Vec3 vLeftPos[3] = {};
    vLeftPos[0] = XMVector3TransformCoord(pVtx[0].vPos, matLeftWorld);
    vLeftPos[1] = XMVector3TransformCoord(pVtx[1].vPos, matLeftWorld);
    vLeftPos[2] = XMVector3TransformCoord(pVtx[2].vPos, matLeftWorld);
    Vec3 vLeftCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeftWorld);

    Vec3 vRightPos[3] = {};
    vRightPos[0] = XMVector3TransformCoord(pVtx[0].vPos, matRightWorld);
    vRightPos[1] = XMVector3TransformCoord(pVtx[1].vPos, matRightWorld);
    vRightPos[2] = XMVector3TransformCoord(pVtx[2].vPos, matRightWorld);
    Vec3 vRightCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRightWorld);


    for (int i = 0; i < 3; ++i)
    {
        vLeftPos[i].z = 0.f;
        vRightPos[i].z = 0.f;
    }
    vLeftCenter.z = 0.f;
    vRightCenter.z = 0.f;

    // 알아낸 각 충돌체의 월드상의 꼭지점 위치를 이용해서 투영시킬 각 충돌체의 표면 방향벡터 4개를 구한다.
    Vec3 vProjAxis[4] =
    {
        vLeftPos[1] - vLeftPos[0],
        vLeftPos[2] - vLeftPos[1],
        vRightPos[1] - vRightPos[0],
        vRightPos[2] - vRightPos[1]
    };

    // 두 충돌체의 중심점을 이은 벡터를 구한다.
    Vec3 vCenter = vRightCenter - vLeftCenter;


    // 4개의 투영축중 하나를 골라서, 나머지 투영축을 투영시켜서 투영된 면적을 얻는다.
    for (int i = 0; i < 4; ++i)
    {
        // 4개의 투영축 중에서 투영을 당할 벡터하나를 고른다.
        Vec3 vProject = vProjAxis[i];
        vProject.Normalize();

        // 다시 4개의 투영축을 정해진 투영축으로 투영킨 후 전체 면적의 절반 길이를 얻는다.
        float Distance = 0.f;
        for (int j = 0; j < 4; ++j)
        {
            Distance += fabs(vProject.Dot(vProjAxis[j]));
        }
        Distance /= 2.f;

        // 중심점끼리 이은 벡터를 정한 투영축으로 투영시킨 길이를 얻는다.
        float fCenterDist = fabs(vProject.Dot(vCenter));

        if (Distance < fCenterDist)
            return false;
    }

    return true;
}
