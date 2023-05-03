#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
using namespace std;

int main()
{
    int ss, sa;
    struct sockaddr_in ssa;
    char recvbuf[5];
    int sendbuf[5];

    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(ss, (struct sockaddr *) &ssa, sizeof(ssa));

    while (1) {
        listen(ss, 10);
        sa = accept(ss, 0, 0);
        recv(sa, recvbuf, 5, 0);

        for (int i = 0; i < 5; i++) {
            sendbuf[i] = (int)recvbuf[i];
        }

        send(sa, sendbuf, sizeof(sendbuf) / sizeof(char), 0);
        close(sa);
    }
}