#pragma once

// ������ ���� ��� �߰��� ��.
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