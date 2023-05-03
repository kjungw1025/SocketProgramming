#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
    int cs;
    char buf[5];
    int recvbuf[5];
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    cout << "Input String : ";
    cin >> buf;
    send(cs, buf, 5, 0);

    recv(cs, recvbuf, sizeof(recvbuf) / sizeof(char), 0);
    cout << "Receive ";
    for (int i = 0; i < 5; i++) {
        cout << recvbuf[i];
    }
    cout << '\n';

    close(cs);
}
