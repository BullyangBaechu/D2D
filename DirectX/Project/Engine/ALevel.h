#pragma once
#include "Asset.h"

#include "Layer.h"

class GameObject;

class ALevel :
    public Asset
{
private:
    Ptr<Layer>  m_Layer[MAX_LAYER];

public:
    void Begin();
    void Tick();
    void FinalTick();

public:
    // _MoveWithChild: GameObject �� ������ �ڽ� ������Ʈ�� ���� ���̾ �߰��� ������
    void AddObject(int _LayerIdx, GameObject* _Object, bool _MoveWithChild);
    Ptr<Layer> GetLayer(int _LayerIdx) { return m_Layer[_LayerIdx]; }

private:
    // ��ϵȰ��� ���, Unregister ����� ���(��ϵ��� ����)
    void Deregister();
    GameObject* FindObjectByName(const wstring& _Name);

public:
    virtual int Save(const wstring& _FilePath) override { return S_OK; }
    virtual int Load(const wstring& _FilePath) override { return S_OK; }

    virtual ALevel* Clone() override
    {
        // Default ���������
        // �ɹ����� �ܼ�����, ���� ����(Swallow Copy)
        // ==> ���� ��������ڸ� ����(Deep Copy)
        return new ALevel(*this);
    }
public:
    ALevel();
    ALevel(const ALevel& _Origin);
    virtual ~ALevel();

    friend class LevelMgr;
};

