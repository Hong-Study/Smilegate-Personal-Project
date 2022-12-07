#include "pch.h"
#include "IocpCore.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	_iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if (_iocpHandle == INVALID_HANDLE_VALUE)
		HandleError("CreateIoCOmpletionPort");
}

bool IocpCore::Register(class IocpObject* object)
{
	return CreateIoCompletionPort(object->GetHandle(), _iocpHandle, reinterpret_cast<ULONG_PTR>(object), 0);
}

bool IocpCore::Dispatch(uint32 timeoutMS = INFINITE)
{
	DWORD numOfBytes;
	IocpObject* iocpObject = nullptr;
	IocpEvent* iocpEvent = nullptr;
	if (GetQueuedCompletionStatus(_iocpHandle, &numOfBytes, reinterpret_cast<PULONG_PTR>(iocpObject), reinterpret_cast<LPOVERLAPPED*>(iocpEvent), timeoutMS)) {
		iocpObject->Dispatch(iocpEvent);
	}else
	{
		int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;
		default:
			// TODO : ·Î±× Âï±â
			iocpObject->Dispatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
