#include <mysql/mysql.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

int main()
{
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    int ss, sa;
    struct sockaddr_in ssa;
    string recvbuf;
    int recvsize[1];

    // MySQL 연결 생성
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "socket", "여기에 비밀번호 입력", NULL, 0, NULL, 0)) {
        cout << "MySQL Connection Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    if (mysql_query(conn, "USE problem3")) {
        cout << "MySQL Query Error: " << mysql_error(conn) << '\n';
        return 1;
    }

    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(ss, (struct sockaddr *) &ssa, sizeof(ssa));

    while (1) {
        listen(ss, 10);
        sa = accept(ss, 0, 0);

        recv(sa, recvsize, sizeof(recvsize), 0);

        while (1) {
            char buf[1024];
            int len = recv(sa, buf, sizeof(buf), 0);
            if (len <= 0)   break;

            for (int i = 0; i < len; i++) {
                recvbuf += buf[i];
            }
            memset(buf, 0, sizeof(buf));

            if (recvbuf.size() == recvsize[0]) break;
        }

        string query, response;
        switch (recvbuf[0]) {
            case 'D':
                query = "SELECT IP FROM DNS WHERE Domain='"+ recvbuf.substr(3) + "'";
                if (mysql_query(conn, query.c_str())) {
                    cout << "MySQL Query Error: " << mysql_error(conn) << '\n';
                    return 1;
                }

                res = mysql_use_result(conn);
                if (res) {
                    while ((row = mysql_fetch_row(res))) {
                        string ip(row[0]);
                        response += ("IP: " + ip);
                    }
                }
                else {
                    cout << "MySQL Use Result Error" << mysql_error(conn) << '\n';
                    return 1;
                }
                mysql_free_result(res);
                break;

            case 'I':
                query = "SELECT Domain FROM DNS WHERE IP='" + recvbuf.substr(3) + "'";
                if (mysql_query(conn, query.c_str())) {
                    cout << "MySQL Query Error: " << mysql_error(conn) << '\n';
                    return 1;
                }

                res = mysql_use_result(conn);
                if (res) {
                    while ((row = mysql_fetch_row(res))) {
                        string ip(row[0]);
                        response += ("Domain: " + ip);
                    }
                }
                else {
                    cout << "MySQL Use Result Error" << mysql_error(conn) << '\n';
                    return 1;
                }
                mysql_free_result(res);            
                break;
               
            case 'W':   // W: www.daum.net 234.567.890.123
                istringstream iss(recvbuf);
                string s1, s2, s3;
                iss >> s1 >> s2 >> s3;
               
                query = "INSERT INTO DNS (domain, ip) VALUES ('" + s2 + "', '" + s3 + "')";
                if (mysql_query(conn, query.c_str())) {
                    cout << "MySQL Query Error: " << mysql_error(conn) << '\n';
                    return 1;
                }

                response += "Updated to database";
                break;
        }

        send(sa, response.c_str(), response.length(), 0);

        recvbuf.clear();
        query.clear();
        response.clear();
        close(sa);
    }

    mysql_close(conn);

    return 0;
}

