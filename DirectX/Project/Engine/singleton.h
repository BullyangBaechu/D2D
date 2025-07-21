#pragma once

template<typename T>
class singleton
{
private:
	static T* m_This;

public:
	static T* GetInst()
		{
		if (nullptr == m_This)
		{
			m_This = new T;
		}

		return m_This;
	}

	static void Destroy()
	{
		if (nullptr != m_This)
		{
			delete m_This;
			m_This = nullptr;
		}
	}

private:
	typedef void(*EXIT)(void);	

protected:
	singleton()
	{
		atexit((EXIT)&singleton::Destroy);
	}

	~singleton()
	{

	}
};

template<typename T>
T* singleton<T>::m_This = nullptr;


#define SINGLE(Type)	private:\
							Type* operator =(const Type& _other) = delete;\
							Type();\
							Type(const Type& _Other) = delete;\
							~Type();\
							template<typename T>\
							friend class singleton;