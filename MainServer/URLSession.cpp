#include "pch.h"
#include "URLSession.h"

void URLSession::OnConnected()
{
	cout << "Connected" << endl;
}

int32 URLSession::OnRecv(BYTE* buffer, int32 len)
{
	// Echo
	//cout << "OnRecv data = " << (char*)buffer << "(" << len << ")" << endl;
	
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&buffer[0]);
	cout << "Recv Len : " << len << " pkt : " << head->pkt_Size << endl;
	char* string = new char[head->pkt_Size];
	memcpy(string, &buffer[sizeof(PKT_Header)], head->pkt_Size);

	cout << "Recv data : " << string << "\n\n";

	//DBConnectorRef db = nullptr;
	//{
	//	//spinLock 변경해야함.
	//	lock_guard<SpinLock> gaurd(spinLock);
	//	while (1) {
	//		db = dbPool->GetDBCppol();
	//		if (db == nullptr)
	//			continue;
	//		break;
	//	}
	//}

	Send(buffer, len);
	return len;
}

void URLSession::OnSend(int32 len)
{
	cout << "OnSend Len = " << len << endl;
}
