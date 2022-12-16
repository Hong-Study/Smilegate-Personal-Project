#include "pch.h"
#include <iostream>
#include <PKT_Maker.h>


void HandleError(const char* cause)
{
	int errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	PKT_Maker maker;
	char str[] = "HelloWorld\0";
	BYTE* byte = maker.MakePacket_URLMAPPING(str, strlen(str)+1);
	int pos = 0;
	BYTE* dest = new BYTE[sizeof(PKT_Header)];
	memcpy(dest, &byte[0], sizeof(PKT_Header));
	PKT_Header* head = reinterpret_cast<PKT_Header*>(&dest[pos]);
	cout << "PKT_Header : " << head->pkt_Size << endl;
	pos += sizeof(head);

	/*dest = new BYTE[head->pkt_Size];
	memcpy(dest, &byte[pos], head->pkt_Size);*/
	PKT_DATA* data = reinterpret_cast<PKT_DATA*>(&byte[pos]);
	cout << data->url_length << endl;

	
}