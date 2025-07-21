#pragma once

template<typename T>
class Ptr
{
private:
	T*	m_Ptr;

public:
	T* Get() const { return m_Ptr; }
	T* operator->() const { return m_Ptr; }
	T** GetAdressOf() const { return &m_Ptr; }

public:
	bool operator ==(T* _Ptr) const { return m_Ptr == _Ptr; }
	bool operator == (const Ptr<T>& _Ptr) const { return m_Ptr == _Ptr.m_Ptr; }
	bool operator !=(T* _Ptr) const { return m_Ptr != _Ptr; }
	bool operator != (const Ptr<T>& _Ptr) const { return m_Ptr != _Ptr.m_Ptr; }
	void operator =(T* _Ptr) 
	{
		if (nullptr != m_Ptr)
			m_Ptr->Release();
		m_Ptr = _Ptr;
		if (nullptr != m_Ptr)
			m_Ptr->AddRef();
	}

	void operator =(const Ptr<T>& _Ptr)
	{
		if (nullptr != m_Ptr)
			m_Ptr->Release();
		m_Ptr = _Ptr.m_Ptr;
		if (nullptr != m_Ptr)
			m_Ptr->AddRef();
	}
public:
	Ptr()
		: m_Ptr(nullptr)
	{}

	Ptr(T* _Ptr)
		: m_Ptr(_Ptr)
	{
		if (nullptr != _Ptr)
			_Ptr->AddRef();
	}

	Ptr(const Ptr<T>& _Ptr)
		: m_Ptr(_Ptr.m_Ptr)
	{
		if (nullptr != m_Ptr)
			_Ptr->AddRef();
	}

	~Ptr()
	{
		if (nullptr != m_Ptr)
			m_Ptr->Release();
	}
};



template<typename T>
bool operator == (void* _Adress, const Ptr<T>& _Ptr)
{
	return _Adress == _Ptr.Get();
}
template<typename T>
bool operator != (void* _Adress, const Ptr<T>& _Ptr)
{
	return _Adress != _Ptr.Get();
}