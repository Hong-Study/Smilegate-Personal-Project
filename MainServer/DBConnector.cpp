#include "pch.h"
#include "DBConnector.h"
#pragma warning(disable:4996)
DBConnector::DBConnector(int n)
	:sql_Result(nullptr), sql_Row(nullptr)
{
	sql = new char[1024];
	//연결, 짝수면 1번 슬레이어db, 홀수면 2번 슬레이어db에 연결
	mysql_init(&conn1);
	mysql_init(&conn2);
	m_Connection = mysql_real_connect(&conn1, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char*)NULL, 0);
	if ((n % 2) == 0)
		s_Connection = mysql_real_connect(&conn2, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3307, (char*)NULL, 0);
	else
		s_Connection = mysql_real_connect(&conn2, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3308, (char*)NULL, 0);
	if (m_Connection == NULL || s_Connection == NULL) {
		HandleError("Connectinon Error");
		return;
	}
	cout << "연결 성공" << endl;
	mysql_query(m_Connection, "set session character_set_connection=euckr;");
	mysql_query(m_Connection, "set session character_set_result=euckr;");
	mysql_query(m_Connection, "set session character_set_client=euckr;");
}

DBConnector::~DBConnector()
{
	delete[] sql;
	mysql_close(m_Connection);
	mysql_close(s_Connection);
}

bool DBConnector::InsertURL(string urlL, string urlS)
{
	//쿼리문 실행
	sprintf(sql, "INSERT INTO urltable (URLLONG, URLSHORT) VALUES ('%s','%s')", urlL.c_str(), urlS.c_str());
	if (mysql_query(m_Connection, sql) != 0)
		return false;
	cout << "Input 성공" << endl;
	return true;
}

char* DBConnector::MappingURL(string url)
{
	//쿼리문 실행
	sprintf(sql, "SELECT * FROM urltable WHERE URLSHORT='%s'", url.c_str());
	cout << sql << endl;
	if (mysql_query(s_Connection, sql) != 0)
		return nullptr;
	sql_Result = mysql_store_result(s_Connection);
	if((sql_Row = mysql_fetch_row(sql_Result)) == NULL)
		return nullptr;
	cout << sql_Row[0] << " : " << sql_Row[1] << endl;
	mysql_free_result(sql_Result);
	cout << "Mapping Success" << endl;

	return sql_Row[0];
}
