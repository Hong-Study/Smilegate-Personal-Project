#pragma once

// ������ ���� ��� �߰��� ��.
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