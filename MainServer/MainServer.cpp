#include "pch.h"
#include "URLSession.h"

int main()
{
	ServerServiceRef service = make_shared<ServerService>(10);
	service->SetFactory(make_shared< URLSession>);
	service->SetIocpCore(make_shared<IocpCore>());
	service->SetNetAddress(NetAddress(L"127.0.0.1", 5005));

	if (!service->Start())
		HandleError("Start Error");

	for (int i = 0; i < THREAD_SIZE; i++) {
		GThreadPool->enqueue([=]()
			{
				while (true) {
					service->GetIocpCore()->Dispatch();
				}
			});
	}
	GThreadPool->Join();

	delete dbPool;
}