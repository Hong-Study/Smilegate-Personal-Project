#include "pch.h"
#include "DBConnectionPool.h"
#include "DBConnector.h"

DBConnectionPool* dbPool = new DBConnectionPool;

DBConnectionPool::DBConnectionPool()
{
	for (int i = 0; i < 10; i++) {
		_connectorPool.emplace(make_shared<DBConnector>(i));
	}
}

DBConnectorRef DBConnectionPool::GetDBCppol()
{
	lock_guard<SpinLock> garud(s);
	if (_connectorPool.empty())
		return nullptr;

	DBConnectorRef t = _connectorPool.front();
	_connectorPool.pop();
	return t;
}

void DBConnectionPool::ReturnDBpool(DBConnectorRef db)
{
	lock_guard<SpinLock> garud(s);
	_connectorPool.push(db);
}
