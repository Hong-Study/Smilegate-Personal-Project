#include "pch.h"

class GameSession : public Session
{
public:
	GameSession() {
		cout << "실행" << endl;
	}
	~GameSession()
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

void Work(ServerServiceRef service) {
	while (true) {
		service->GetIocpCore()->Dispatch();
	}
}

void hello() {

}
int main()
{
	ServerServiceRef service = make_shared<ServerService>();
	service->SetFactory(make_shared<GameSession>);
	service->SetIocpCore(make_shared<IocpCore>());
	service->SetNetAddress(NetAddress(L"12.0.0.1", 5000));
	service->Start();

	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadPool->enqueue(hello);
	}
}