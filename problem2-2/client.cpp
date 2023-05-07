#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
using namespace std;

int main()
{
    int cs;
    string buf;
    int buf_size[1];
    vector<int> recvbuf;
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    cout << "Input Calculation Formula : ";
    getline(cin, buf);

    buf_size[0] = buf.size();
    send(cs, buf_size, sizeof(buf_size), 0);

    if (buf.length() / 1024 > 0) {
        int quotient = buf.length() / 1024;
        int remainder = buf.length() % 1024;

        string tmp;
        int start_idx, end_idx;
        for (int i = 0; i < quotient; i++) {
            start_idx = 1024 * i;
            end_idx = 1024 * (i + 1) - 1;
            tmp = buf.substr(start_idx, end_idx + 1);
            send(cs, tmp.c_str(), tmp.length(), 0);
        }

        tmp = buf.substr(end_idx + 1, end_idx + 1 + remainder + 1);
        send(cs, tmp.c_str(), tmp.length(), 0);
    }
    else
        send(cs, buf.c_str(), buf.length(), 0);

    recvbuf.resize(1);
    recv(cs, recvbuf.data(), sizeof(recvbuf), 0);
    cout << "Receive ";
    cout << recvbuf[0] << "\n\n";

    close(cs);
}