#pragma once

class URLSession : public Session
{
public:
	URLSession() { }
	~URLSession()
	{
		cout << "~GameSession" << endl;
	}
	virtual void OnConnected() override;
	virtual int32 OnRecv(BYTE* buffer, int32 len) override;

	virtual void OnSend(int32 len) override;
};