#include "pch.h"
#include "DBConnectionPool.h"
#include "DBConnector.h"

DBConnectionPool::DBConnectionPool()
{
	_connectorPool.resize(10);
	for (int i = 0; i < 10; i++) {
		_connectorPool.push_back(new DBConnector);
	}
	useCount.store(0);
}

DBConnectionPool::~DBConnectionPool()
{
	for (auto db : _connectorPool) {
		delete db;
	}
}

void DBConnectionPool::Add_DB()
{
	_connectorPool.emplace_back(new DBConnector);
}
