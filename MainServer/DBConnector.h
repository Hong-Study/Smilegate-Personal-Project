#pragma once

class DBConnector
{
public:
	DBConnector();
	~DBConnector();

public:
	bool InsertURL(string urlL, string urlS);
	char* MappingURL(string url);
	
private:
	MYSQL* connection = NULL, conn;
	MYSQL_RES* sql_Result;
	MYSQL_ROW sql_Row;
	char* sql;
};