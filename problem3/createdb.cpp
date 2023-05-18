#include <mysql/mysql.h>
#include <iostream>
using namespace std;

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    const char* server = "localhost";
    const char* user = "socket"; // MySQL 사용자 이름
    const char* password = "비밀번호입력란"; // MySQL 비밀번호

    conn = mysql_init(NULL);

    // MySQL 연결
    if (!mysql_real_connect(conn, server, user, password, NULL, 0, NULL, 0)) {
        cerr << "Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    // problem3 데이터베이스 생성 쿼리
    const char* create_db_query = "CREATE DATABASE IF NOT EXISTS problem3";

    // 쿼리 실행
    if (mysql_query(conn, create_db_query)) {
        cerr << "Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    cout << "Database 'problem3' created successfully." << '\n';

    // problem3 데이터베이스 선택
    if (mysql_select_db(conn, "problem3")) {
        cerr << "Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    // DNS 테이블 생성 쿼리
    const char* create_table_query = "CREATE TABLE IF NOT EXISTS DNS (Domain VARCHAR(32) NOT NULL, IP TEXT NOT NULL)";

    // 쿼리 실행
    if (mysql_query(conn, create_table_query)) {
        cerr << "Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    cout << "Table 'DNS' created successfully." << '\n';

    mysql_close(conn);
    return 0;
}

