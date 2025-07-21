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
	// ���ؽ� ���� ����
	// ===============
	m_VBDesc.ByteWidth = sizeof(Vtx) * m_VtxCount;
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// Cpu �� ���ؼ� ���� �����͸� �ٽ� ������ �� ����
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA tSub = {};
	tSub.pSysMem = _VtxMem;

	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &tSub, m_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"���ؽ� ���� ���� ����", L"TempInit �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// �����Ҵ��� �ؼ�, ���� ���� ������ ��ü������ �����صд�.
	m_VtxSysMem = new Vtx[_VtxCount];
	memcpy(m_VtxSysMem, _VtxMem, sizeof(Vtx) * m_VtxCount);


	// =================
	// �ε��� ���� �����
	// =================
	m_IdxCount = _IdxCount;
	
	m_IBDesc.ByteWidth = sizeof(UINT) * m_IdxCount;
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// Cpu �� ���ؼ� ���� �����͸� �ٽ� ������ �� ����
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;
		
	tSub.pSysMem = _IdxMem;

	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &tSub, m_IB.GetAddressOf())))
	{
		MessageBox(nullptr, L"�ε��� ���� ���� ����", L"TempInit �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	// �����Ҵ��� �ؼ�, ���� �ε��� ������ ��ü������ �����صд�.
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

	// ������ ���������� ����
	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}