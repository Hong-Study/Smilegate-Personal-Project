#include "pch.h"
#include "DBConnector.h"

DBConnector::DBConnector()
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

	cout << "연결 성공" << endl;
}

DBConnector::~DBConnector()
{
	mysql_close(connection);
}
