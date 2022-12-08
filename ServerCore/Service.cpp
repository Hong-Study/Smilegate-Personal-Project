#include "pch.h"
#include "Service.h"
#include "Session.h"

Service::Service(ServiceType type, NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount)
	: _type(type), _netAddress(address), _iocpCore(core), _sessionFactory(factory), _maxSessionCount(maxSessionCount) {}


Service::Service(ServiceType type, NetAddress address, IocpCoreRef core, int32 maxSessionCount)
	: _type(type), _netAddress(address), _iocpCore(core), _maxSessionCount(maxSessionCount) {}

Service::~Service()
{
}

void Service::CloseService()
{
	// TODO
}

SessionRef Service::CreateSession()
{
	SessionRef session = _sessionFactory();
	session->SetService(shared_from_this());

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Service::AddSession(SessionRef session)
{
	{
		//lock_guard<SpinLock> guard (spinLock);
		_sessionCount++;
		_sessions.insert(session);
	}
}

void Service::ReleaseSession(SessionRef session)
{
	{
		//lock_guard<SpinLock> guard(spinLock);
		_sessionCount--;
		_sessions.erase(session);
	}
}

ServerService::ServerService(NetAddress address, IocpCoreRef core, int32 maxSessionCount)
	:Service(ServiceType::Server, address, core, maxSessionCount)
{


}
ServerService::ServerService(NetAddress address, IocpCoreRef core, SessionFactory factory, int32 maxSessionCount)
	:Service(ServiceType::Server, address, core, factory, maxSessionCount)
{

}

bool ServerService::Start()
{
	if (CanStart() == false)
		return false;

	_listener = make_shared<Listener>();
	if (_listener == nullptr)
		return false;

	if (_listener->StartAccept(static_pointer_cast<ServerService>(shared_from_this())) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	Service::CloseService();
}
