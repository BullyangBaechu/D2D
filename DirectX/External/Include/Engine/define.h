#pragma once

#define GET(type, MemName) type Get##MemName() {return m_##MemName;}
#define SET(type, MemName) void Set##MemName(type _Data) { m_##MemName = _Data;}
#define GET_SET(type, MemName) GET(type, MemName); SET(type, MemName);

#define GET_REF(type, MemName) const type& Get##MemName() {return m_##MemName;}
#define SET_REF(type, MemName) void Set##MemName(const type& _Data) { m_##MemName = _Data;}
#define GET_SET_REF(type, MemName) GET_REF(type, MemName); SET_REF(type, MemName);

#define DEVICE	Device::GetInst()->Get11Device()
#define CONTEXT Device::GetInst()->Get11DeviceContext()

#define DT TimeMgr::GetInst()->GetDeltaTime()

#define MAX_LAYER 32

#define KEY_CHECK(Key, State)	(State == KeyMgr::GetInst()->GetKeyState(Key))
#define KEY_TAP(Key)			KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_PRESSED(Key)		KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_RELEASED(Key)		KEY_CHECK(Key, KEY_STATE::RELEASED)
#define KEY_NONE(Key)			KEY_CHECK(Key, KEY_STATE::NONE)


#define CONTENT_PATH PathMgr::GetInst()->GetContentPath()
#define FIND(Type, Key) AssetMgr::GetInst()->Find<Type>(Key)
#define LOAD(Type, Key, Path) AssetMgr::GetInst()->Load<Type>(Key, Path)

#define CLONE(Class) virtual Class* Clone() override\
                     {\
                         return new Class(*this);\
                     }

#define CLONE_DISABLE(Class) virtual Class* Clone() override\
                             {\
                                return nullptr;\
                             }\
                             Class(const Class& _Origin) = delete;