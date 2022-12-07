#include "pch.h"
#include "Session.h"
#include "IocpEvent.h"

Session::Session()
{
	_sock = SocketUtils::CreateSocket();
	_session = make_shared<Session>(shared_from_this());
}

Session::~Session()
{
	SocketUtils::Close(_sock);
	_session.reset();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_sock);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	switch (iocpEvent->GetType()) {
	case EventType::Connect:

		break;

	case EventType::Recv:

		break;

	case EventType::Send:

		break;

	default:

		break;
	}
}
