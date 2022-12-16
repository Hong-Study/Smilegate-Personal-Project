#pragma once

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