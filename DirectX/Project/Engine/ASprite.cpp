#include "pch.h"
#include "ASprite.h"


ASprite::ASprite()
    : Asset(ASSET_TYPE::SPRITE)
{
}

ASprite::~ASprite()
{
}

void ASprite::SetBackgroundUV(Vec2 _PixelPos)
{
    m_BackgroundUV.x = _PixelPos.x / (float)m_Atlas->GetWidth();
    m_BackgroundUV.y = _PixelPos.y / (float)m_Atlas->GetHeight();
}

Vec2 ASprite::GetBackgroundPixel()
{
    return m_BackgroundUV * Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
}

void ASprite::SetLeftTopUV(Vec2 _PixelPos)
{
    assert(m_Atlas.Get());

    m_LeftTopUV.x = _PixelPos.x / (float)m_Atlas->GetWidth();
    m_LeftTopUV.y = _PixelPos.y / (float)m_Atlas->GetHeight();
}

Vec2 ASprite::GetLeftTopPixel()
{
    return m_LeftTopUV * Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
}

void ASprite::SetSliceUV(Vec2 _PixelPos)
{
    m_SliceUV.x = _PixelPos.x / (float)m_Atlas->GetWidth();
    m_SliceUV.y = _PixelPos.y / (float)m_Atlas->GetHeight();
}

Vec2 ASprite::GetSlicePixel()
{
    return m_SliceUV * Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
}


void ASprite::SetOffsetUV(Vec2 _PixelPos)
{
    m_OffsetUV.x = _PixelPos.x / (float)m_Atlas->GetWidth();
    m_OffsetUV.y = _PixelPos.y / (float)m_Atlas->GetHeight();
}

Vec2 ASprite::GetOffsetPixel()
{
    return m_OffsetUV * Vec2((float)m_Atlas->GetWidth(), (float)m_Atlas->GetHeight());
}

int ASprite::Save(const wstring& _FilePath)
{
    FILE* pFile = nullptr;

    _wfopen_s(&pFile, _FilePath.c_str(), L"wb");

    // ����Ű�� �ִ� Atlas �ؽ����� ������ �����Ѵ�.
    SaveAssetRef(m_Atlas.Get(), pFile);

    fwrite(&m_BackgroundUV, sizeof(Vec2), 1, pFile);
    fwrite(& m_LeftTopUV, sizeof(Vec2), 1, pFile);
    fwrite(& m_SliceUV, sizeof(Vec2), 1, pFile);
    fwrite(& m_OffsetUV, sizeof(Vec2), 1, pFile);

    fclose(pFile);


    // �ڽ��� ����� ���(�����) �� ������ �˰��Ѵ�.
    wstring ContentPath = PathMgr::GetInst()->GetContentPath();
    assert(wstring::npos != _FilePath.find(ContentPath));

    wstring RelativePath = _FilePath.substr(ContentPath.length(), _FilePath.length());
    SetRelativePath(RelativePath);

    return S_OK;
}


int ASprite::Load(const wstring& _FilePath)
{
    FILE* pFile = nullptr;

    _wfopen_s(&pFile, _FilePath.c_str(), L"rb");

    // ������ ����Ű�� �ִ� Atlas �ؽ��ĸ� �ٽ� ����Ų��. 
    m_Atlas = LoadAssetRef<ATexture>(pFile);

    fread(&m_BackgroundUV, sizeof(Vec2), 1, pFile);
    fread(&m_LeftTopUV, sizeof(Vec2), 1, pFile);
    fread(&m_SliceUV, sizeof(Vec2), 1, pFile);
    fread(&m_OffsetUV, sizeof(Vec2), 1, pFile);

    fclose(pFile);

    return S_OK;
}