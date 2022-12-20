#pragma once

class DBConnector
{
public:
	DBConnector(int n);
	~DBConnector();

public:
	bool InsertURL(string urlL, string urlS);
	char* MappingURL(string url);
	
private:
	//master ����
	MYSQL* m_Connection = NULL, conn1;
	//slave ����
	MYSQL* s_Connection = NULL, conn2;
	MYSQL_RES* sql_Result;
	MYSQL_ROW sql_Row;
	char* sql;
};