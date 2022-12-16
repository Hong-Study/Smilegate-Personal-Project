#pragma once

// 성능을 위해 방법 추가할 것.
// DBMS
class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();

public:
	void Add_DB();
	DBConnectorRef GetDBCppol();
	void ReturnDBpool(DBConnectorRef db);
private:
	queue<DBConnectorRef> _connectorPool;
	atomic<int> useCount;

	SpinLock s;
};

extern DBConnectionPool* dbPool;