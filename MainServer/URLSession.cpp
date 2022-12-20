#include "pch.h"
#include "URLSession.h"
#include "ShortAlgorightm.h"
#include "DBConnectionPool.h"
#include "DBConnector.h"

void URLSession::OnConnected()
{
	cout << "Connected" << endl;
}

int32 URLSession::OnRecv(BYTE* buffer, int32 len)
{
	if (len < sizeof(PKT_Header)) {
		cout<<"Recv Size Error"<<endl;
		return 0;
	}

	head = reinterpret_cast<PKT_Header*>(&buffer[0]);
	
	if (head->pkt_State == PKT_STATE::URL_MAKING) {
		HANDLE_URL_MAKING(buffer, head->pkt_Size);
	}
	else {
		HANDLE_URL_MAPPING(buffer, head->pkt_Size);
	}
	return len;
}

void URLSession::OnSend(int32 len)
{
	cout << "OnSend Len = " << len << endl;
}

void URLSession::HANDLE_URL_MAKING(BYTE* buffer, int32 len)
{
	char* str = new char[len];
	memcpy(str, &buffer[sizeof(PKT_Header)], len);
	string s = ShortAlgorightm::convURLtoShort(str, len);

	head->pkt_Size = s.length();
	memcpy(&buffer[sizeof(PKT_Header)], (BYTE*)s.data(), s.length());
	
	while (1) {
		dbConector = dbPool->GetDBCppol();
		if (dbConector == nullptr)
			continue;
		break;
	}
	//TODO
	if (dbConector->MappingURL(s) == nullptr) {
		dbConector->InsertURL(str, s);
	}else Send(buffer, s.length() + sizeof(PKT_Header));
	//
	delete[] str;
	dbPool->ReturnDBpool(dbConector);
	dbConector = nullptr;
}

void URLSession::HANDLE_URL_MAPPING(BYTE* buffer, int32 len)
{
	char* str = new char[len];
	memcpy(str, &buffer[sizeof(PKT_Header)], len);
	string s = ShortAlgorightm::convURLtoShort(str, len);

	while (1) {
		dbConector = dbPool->GetDBCppol();
		if (dbConector == nullptr)
			continue;
		break;
	}
	//TODO
	char* urlL = nullptr;
	if ((urlL = dbConector->MappingURL(s.c_str())) == nullptr) {
		head->pkt_State = PKT_STATE::URL_ERROR;
		Send(buffer, sizeof(PKT_Header));
	}
	else {
		memcpy(&buffer[sizeof(PKT_Header)], (BYTE*)urlL, strlen(urlL));
		head->pkt_Size = strlen(urlL);
		Send(buffer, sizeof(PKT_Header) + strlen(urlL));
	}
	//

	delete[] str;
	dbPool->ReturnDBpool(dbConector);
	dbConector = nullptr;
}
