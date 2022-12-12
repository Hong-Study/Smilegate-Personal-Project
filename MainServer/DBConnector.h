#pragma once

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "Dignrnfjrl12!"
#define DB_NAME "TestDB"

class DBConnector
{
public:
	DBConnector();
	~DBConnector();

public:
	string InsertURL(string url);
	string FindURL(string url);

private:
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_Result;
	MYSQL_ROW sql_Row;
	
};