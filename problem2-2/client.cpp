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
    send(cs, buf_size, sizeof(buf_size), 0); // server에, client가 입력한 문자열의 길이를 우선적으로 전송

    send(cs, buf.c_str(), buf.length(), 0);

    recvbuf.resize(1);
    recv(cs, recvbuf.data(), sizeof(recvbuf), 0);
    cout << "Receive ";
    cout << recvbuf[0] << "\n\n";

    close(cs);
}
