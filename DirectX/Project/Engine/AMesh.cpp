#include "pch.h"
#include "AMesh.h"

#include "Device.h"

AMesh::AMesh()
	: Asset(ASSET_TYPE::MESH)
	, m_VBDesc{}
	, m_VtxCount(0)
	, m_VtxSysMem(nullptr)
	, m_IBDesc{}
	, m_IdxCount(0)
	, m_IdxSysMem(nullptr)
{
}

AMesh::AMesh(const AMesh& _Origin)
	: Asset(_Origin)
	, m_VB(nullptr)
	, m_VBDesc(_Origin.m_VBDesc)
	, m_VtxCount(_Origin.m_VtxCount)
	, m_VtxSysMem(nullptr)
	, m_IB(nullptr)
	, m_IBDesc(_Origin.m_IBDesc)
	, m_IdxCount(_Origin.m_IdxCount)
	, m_IdxSysMem(nullptr)
{
	Create(_Origin.m_VtxSysMem, m_VtxCount, m_IdxSysMem, _Origin.m_IdxCount);
}

AMesh::~AMesh()
{
	if (nullptr != m_VtxSysMem)
		delete m_VtxSysMem;

	if (nullptr != m_IdxSysMem)
		delete m_IdxSysMem;
}

int AMesh::Create(Vtx* _VtxMem, UINT _VtxCount, UINT* _IdxMem, UINT _IdxCount)
{
	m_VtxCount = _VtxCount;

	// ===============
	// 버텍스 버퍼 생성
	// ===============
	m_VBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Cpu 를 통해서 버퍼 데이터를 다시 수정할 수 없음
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxMem;

	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &tSub, m_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"버텍스 버퍼 생성 실패", L"TempInit 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 동적할당을 해서, 원본 정점 정보를 자체적으로 저장해둔다.
	m_VtxSysMem = new Vtx[_VtxCount];
	memcpy(m_VtxSysMem, _VtxMem, sizeof(Vtx) * m_VtxCount);


	// =================
	// 인덱스 버퍼 만들기
	// =================
	m_IdxCount = _IdxCount;
	
	m_IBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// Cpu 를 통해서 버퍼 데이터를 다시 수정할 수 없음
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;
		
	tSub.pSysMem = _IdxMem;

	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &tSub, m_IB.GetAddressOf())))
	{
		MessageBox(nullptr, L"인덱스 버퍼 생성 실패", L"TempInit 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// 동적할당을 해서, 원본 인덱스 정보를 자체적으로 저장해둔다.
	m_IdxSysMem = new UINT[m_IdxCount];
	memcpy(m_IdxSysMem, _IdxMem, sizeof(UINT) * m_IdxCount);


	return S_OK;
}

void AMesh::Binding()
{
	UINT Stride = sizeof(Vtx);
	UINT Offset = 0;
	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &Stride, &Offset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void AMesh::Render()
{
	Binding();

	// 렌더링 파이프라인 시작
	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}