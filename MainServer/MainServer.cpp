#include "pch.h"

class URLSession : public Session
{
public:
	URLSession() {
		cout << "실행" << endl;
	}
	~URLSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual int32 OnRecv(BYTE* buffer, int32 len) override
	{
		// Echo
		cout << "OnRecv Len = " << len << endl;
		Send(buffer, len);
		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "OnSend Len = " << len << endl;
	}
};

int main()
{
	ServerServiceRef service = make_shared<ServerService>(10);
	service->SetFactory(make_shared< URLSession>);
	service->SetIocpCore(make_shared<IocpCore>());
	service->SetNetAddress(NetAddress(L"127.0.0.1", 5000));

	if (!service->Start())
		HandleError("Start Error");

	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadPool->enqueue([=]()
			{
				service->GetIocpCore()->Dispatch();
			});
	}

	GThreadPool->Join();
}