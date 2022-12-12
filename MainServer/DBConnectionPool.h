#pragma once

class DBConnector;

class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

public:
	bool Find();
	
private:
	vector<DBConnector> _connectorPool;
};

