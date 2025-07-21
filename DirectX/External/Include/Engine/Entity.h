#pragma once


class Entity
{
	static UINT m_GlobalID;
private:
	const UINT	m_ID;
	wstring		m_Name;	
	int			m_RefCount;

private:
	void AddRef() { ++m_RefCount; }
	void Release()
	{
		--m_RefCount;
		if (m_RefCount <= 0)
			delete this;
	}


public:
	GET(UINT, ID);
	GET_SET_REF(wstring, Name);


public:
	// 자기자신의 복제본을 리턴시킴
	virtual	Entity* Clone() = 0;

public:
	Entity();
	Entity(const Entity& _Origin);
	virtual ~Entity();

	template<typename T>
	friend class Ptr;
};