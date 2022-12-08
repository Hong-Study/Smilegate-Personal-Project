#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "Listener.h"

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
int main()
{
	ThreadPool th(THREAD_SIZE);

	ServerServiceRef service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 5000)
		, make_shared<IocpCore>()
		//, make_shared<GameSession>
		, 100);

	//service->Start();

	/*for (int i = 0; i < THREAD_SIZE; i++) {
		th.enqueue([=]() 
			{
				while (true) {
					service->GetIocpCore()->Dispatch();
				}
			});
	}*/
}