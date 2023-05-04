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
    int ss, sa;
    struct sockaddr_in ssa;
    string recvbuf;
    vector<int> sendbuf;
    int recvsize[1];

    memset(&ssa, 0, sizeof(ssa));
    ssa.sin_family = AF_INET;
    ssa.sin_addr.s_addr = htonl(INADDR_ANY);
    ssa.sin_port = htons(11234);

    ss = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    bind(ss, (struct sockaddr *) &ssa, sizeof(ssa));

    while (1) {
        listen(ss, 10);
        sa = accept(ss, 0, 0);

        recv(sa, recvsize, sizeof(recvsize), 0); // client가 보낸 문자열의 길이를 recvsize에 할당 (recvsize[0]에 존재)

        while (1) {
            char buf[1024]; // client가 보낸 문자열을 1024 크기로 쪼개서 buf에 받음
            int len = recv(sa, buf, sizeof(buf), 0);
            if (len <= 0)   break;

            for (int i = 0; i < len; i++) {
                recvbuf += buf[i];
            }
            memset(buf, 0, sizeof(buf));

            if (recvbuf.size() == recvsize[0]) break; // server가 가장 먼저 받은 문자열 길이와 같다면, while loop 종료 (다 받았기 때문)
        }

        sendbuf.resize(recvbuf.length());
        for (int i = 0; i < recvbuf.length(); i++) {
            sendbuf[i] = (int)recvbuf[i]; // 각 문자들을 ASCII Code로 변환
        }

        send(sa, sendbuf.data(), sendbuf.size() * sizeof(int), 0); // ASCII Code로 변환한 결과 값들을 client에 전송

        recvbuf.clear();
        sendbuf.clear();
        close(sa);
    }
}