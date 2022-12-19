#pragma once

class URLSession : public Session
{
public:
	URLSession() { dbConector = nullptr; }
	~URLSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void OnConnected() override;
	virtual int32 OnRecv(BYTE* buffer, int32 len) override;
	virtual void OnSend(int32 len) override;

private:
	void HANDLE_URL_MAKING(BYTE* buffer, int32 len);
	void HANDLE_URL_MAPPING(BYTE* buffer, int32 len);

private:
	DBConnectorRef dbConector;
	PKT_Header* head;
};