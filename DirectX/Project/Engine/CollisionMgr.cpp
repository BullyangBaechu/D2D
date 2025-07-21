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
    // ���� ������ ����
    ALevel* pLevel = LevelMgr::GetInst()->GetCurrentLevel().Get();

    // �浹��ų �� Layer ������
    Layer* pLeftLayer = pLevel->GetLayer(_Left).Get();
    Layer* pRightLayer = pLevel->GetLayer(_Right).Get();

    const vector<Ptr<GameObject>>& vecLeftObj = pLeftLayer->GetObjects();
    const vector<Ptr<GameObject>>& vecRightObj = pRightLayer->GetObjects();

    // ���� �ٸ� �� ���̾�� �浹ü���� �˻縦 1:1 �� �����ϴ� ���
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

    // ���� ���̾� ���ο��� �ڱ�� ���� �浹 �˻縦 �����ؾ� �ϴ°�� �ε��� ����ó��
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
    // �� �浹ü�� ���������ӿ��� �浹���̾����� Ȯ���ϱ����ؼ�, ���������� �浹������ �˻��Ѵ�.
    COLLIDER_ID ColID;
    ColID.Left = _Left->GetID();
    ColID.Right = _Right->GetID();
    map<DWORD_PTR, bool>::iterator iter = m_mapColInfo.find(ColID.ID);

    if (iter == m_mapColInfo.end())
    {
        m_mapColInfo.insert(make_pair(ColID.ID, false));
        iter = m_mapColInfo.find(ColID.ID);
    }

    // �� �浹ü �� ���� �ϳ��� Dead �������� Ȯ���Ѵ�.
    bool IsDead = false;
    if (_Left->IsDead() || _Right->IsDead())
        IsDead = true;


    // �浹ü�� �����ϰ� �ִ� �� ������Ʈ�� �浹�˻縦 �����Ѵ�.
    // ���� �浹���̴�
    if (IsOverlap(_Left, _Right))
    {
        // �������� �浹�߾����
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

        // �������� �浹������ �ʾҴ�.
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

    // ���� �浹�ϰ� ���� �ʴ�
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
    // �и��� �̷�
    // RectMesh�� ���ð����� �� ��ǥ�� �ش� �浹ü�� ��������� ���ؼ� 
    // ������� �ش� �浹ü�� 4���� ������ ��ġ�� �� �� �ִ�.
    AMesh* pRectMesh = AssetMgr::GetInst()->Find<AMesh>(L"RectMesh").Get();
    const Vtx* pVtx = pRectMesh->GetVtxSysyMem();

    // �� �浹ü�� ��������� �����´�.
    const Matrix& matLeftWorld = _Left->GetWorldMat();
    const Matrix& matRightWorld = _Right->GetWorldMat();

    // ���ð����� �޽��� ������ �� �浹ü�� �������� �߽������� �̵����Ѽ�
    // ������� �浹ü�� ��ġ�� �˾Ƴ���.
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

    // �˾Ƴ� �� �浹ü�� ������� ������ ��ġ�� �̿��ؼ� ������ų �� �浹ü�� ǥ�� ���⺤�� 4���� ���Ѵ�.
    Vec3 vProjAxis[4] =
    {
        vLeftPos[1] - vLeftPos[0],
        vLeftPos[2] - vLeftPos[1],
        vRightPos[1] - vRightPos[0],
        vRightPos[2] - vRightPos[1]
    };

    // �� �浹ü�� �߽����� ���� ���͸� ���Ѵ�.
    Vec3 vCenter = vRightCenter - vLeftCenter;


    // 4���� �������� �ϳ��� ���, ������ �������� �������Ѽ� ������ ������ ��´�.
    for (int i = 0; i < 4; ++i)
    {
        // 4���� ������ �߿��� ������ ���� �����ϳ��� ����.
        Vec3 vProject = vProjAxis[i];
        vProject.Normalize();

        // �ٽ� 4���� �������� ������ ���������� ����Ų �� ��ü ������ ���� ���̸� ��´�.
        float Distance = 0.f;
        for (int j = 0; j < 4; ++j)
        {
            Distance += fabs(vProject.Dot(vProjAxis[j]));
        }
        Distance /= 2.f;

        // �߽������� ���� ���͸� ���� ���������� ������Ų ���̸� ��´�.
        float fCenterDist = fabs(vProject.Dot(vCenter));

        if (Distance < fCenterDist)
            return false;
    }

    return true;
}
