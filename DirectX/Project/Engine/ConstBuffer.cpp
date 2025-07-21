#include "pch.h"
#include "ConstBuffer.h"

#include "Device.h"

ConstBuffer::ConstBuffer(CB_TYPE _Type)
	: m_CBDesc{}
	, m_Type(_Type)
{

}

ConstBuffer::~ConstBuffer()
{

}

int ConstBuffer::Create(UINT _BufferSize)
{
	// 상수버퍼의 크기는 16 의 배수여야 한다.
	assert(!(_BufferSize % 16));

	m_CBDesc.ByteWidth = _BufferSize;
	m_CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// Cpu 를 통해서 버퍼 데이터를 다시 수정할 수 있음
	m_CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	m_CBDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(DEVICE->CreateBuffer(&m_CBDesc, nullptr, m_CB.GetAddressOf())))
	{
		MessageBox(nullptr, L"상수 버퍼 생성 실패", L"TempInit 초기화 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void ConstBuffer::SetData(void* _SysMem, UINT _DataSize)
{
	D3D11_MAPPED_SUBRESOURCE tMapSub = {};
	CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapSub);

	memcpy(tMapSub.pData, _SysMem, _DataSize);

	CONTEXT->Unmap(m_CB.Get(), 0);
}

void ConstBuffer::Binding()
{
	CONTEXT->VSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
	CONTEXT->HSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
	CONTEXT->DSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
	CONTEXT->GSSetConstantBuffers((UINT)m_Type, 1, m_CB.GetAddressOf());
}
