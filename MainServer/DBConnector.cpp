#include "pch.h"
#include "DBConnector.h"

DBConnector::DBConnector()
	:sql_Result(nullptr), sql_Row(nullptr)
{
	mysql_init(&conn);
	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 5000, (char*)NULL, 0);
	if (connection == NULL) {
		HandleError("Connectinon Error");
		return;
	}
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_result=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");
}

DBConnector::~DBConnector()
{
	mysql_close(connection);
}

string DBConnector::InsertURL(string url)
{
	string s = "INSERT INTO urltable (URLLong, URLShort) VALUES ('asdfasdf','asdfa')";

	return s;
}
