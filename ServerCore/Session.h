#pragma once

class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();

public:
	void SetNetAddress(NetAddress address) { _addr = address; };
	NetAddress GetAddress() { return _addr; }
	SOCKET GetSocket() { return _sock; }

public:
	virtual HANDLE GetHandle() override;
	virtual void Dispatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;

	void ProcessAccept(AcceptEvent* iocpEvent);
	void ProcessSend();
	void ProcessRecv();
	void ProcessConnect();

private:
	NetAddress				_addr;
	SOCKET					_sock = INVALID_SOCKET;
	atomic<bool>			_connected = false;
	shared_ptr<Session>		_session;
};

