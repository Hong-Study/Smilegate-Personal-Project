#pragma once

// 성능을 위해 방법 추가할 것.
// DBMS
class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool() {}

public:
	DBConnectorRef GetDBCppol();
	void ReturnDBpool(DBConnectorRef db);

private:
	queue<DBConnectorRef> _connectorPool;

	SpinLock s;
};

extern DBConnectionPool* dbPool;