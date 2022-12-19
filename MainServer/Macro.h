#pragma once
#include <iostream>
#include <memory>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "1234"
#define DB_NAME "urldb"


using DBConnectorRef = std::shared_ptr<class DBConnector>;