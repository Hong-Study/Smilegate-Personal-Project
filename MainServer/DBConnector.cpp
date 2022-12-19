#include "pch.h"
#include "DBConnector.h"
#pragma warning(disable:4996)
DBConnector::DBConnector()
	:sql_Result(nullptr), sql_Row(nullptr)
{
	sql = new char[1024];
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if (connection == NULL) {
		HandleError("Connectinon Error");
		return;
	}
	cout << "연결 성공" << endl;
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_result=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
}

DBConnector::~DBConnector()
{
	delete[] sql;
	mysql_close(connection);
}

bool DBConnector::InsertURL(string urlL, string urlS)
{
	sprintf(sql, "INSERT INTO urltable (URLLONG, URLSHORT) VALUES ('%s','%s')", urlL.c_str(), urlS.c_str());
	if (mysql_query(connection, sql) != 0)
		return false;
	cout << "Input 성공" << endl;
	return true;
}

char* DBConnector::MappingURL(string url)
{
	sprintf(sql, "SELECT URLLONG FROM urltable WHERE URLSHORT = '%s'", url.c_str());
	if (mysql_query(connection, sql) != 0)
		return nullptr;
	sql_Result = mysql_store_result(connection);
	if((sql_Row = mysql_fetch_row(sql_Result)) == NULL)
		return nullptr;

	char str[1024];
	strcpy(str,sql_Row[0]);
	cout << "Mapping Success" << endl;
	mysql_free_result(sql_Result);
	return str;
}
