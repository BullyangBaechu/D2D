#include "pch.h"
#include "AFlipbook.h"

AFlipbook::AFlipbook()
	: Asset(ASSET_TYPE::FLIPBOOK)
{
}

AFlipbook::~AFlipbook()
{
}

int AFlipbook::Save(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"wb");

	size_t Count = m_vecSprites.size();
	fwrite(&Count, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < m_vecSprites.size(); ++i)
	{
		SaveAssetRef(m_vecSprites[i].Get(), pFile);
	}

	fclose(pFile);

	return S_OK;
}

int AFlipbook::Load(const wstring& _FilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _FilePath.c_str(), L"rb");

	size_t Count = 0;
	fread(&Count, sizeof(size_t), 1, pFile);

	for (size_t i = 0; i < Count; ++i)
	{
		AddSprite(LoadAssetRef<ASprite>(pFile));
	}

	fclose(pFile);

	return S_OK;
}