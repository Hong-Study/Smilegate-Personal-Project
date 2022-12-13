#pragma once

class DBConnector;

class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

public:
	void Add_DB();
	//bool Find(string url);
	
private:
	vector<DBConnector*> _connectorPool;
	atomic<int> useCount;
} dbConnectionPool;