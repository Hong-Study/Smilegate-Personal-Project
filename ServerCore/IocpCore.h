#pragma once

class IocpObject : public enable_shared_from_this<IocpObject> {
public:
	virtual HANDLE GetHandle() abstract;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class IocpCore
{
public:
	IocpCore();
	bool	Register(class IocpObject* object);
	bool	Dispatch(uint32 timeoutMS = INFINITE);

private:
	HANDLE _iocpHandle;
};

