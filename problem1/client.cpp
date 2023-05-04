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
    string buf; // client가 입력한 문자열을 담은 변수
    int buf_size[1]; // client가 입력한 문자열의 길이를 담은 변수
    vector<int> recvbuf;
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    cout << "Input String : ";
    getline(cin, buf);

    buf_size[0] = buf.size();
    send(cs, buf_size, sizeof(buf_size), 0); // server에, client가 입력한 문자열의 길이를 우선적으로 전송

    if (buf.length() / 1024 > 0) {  // 문자열의 길이가 1024보다 크다면
        int quotient = buf.length() / 1024;
        int remainder = buf.length() % 1024;

        string tmp;
        int start_idx, end_idx;
        for (int i = 0; i < quotient; i++) {
            start_idx = 1024 * i;
            end_idx = 1024 * (i + 1) - 1;
            tmp = buf.substr(start_idx, end_idx + 1);
            send(cs, tmp.c_str(), tmp.length(), 0); // 문자열을 1024씩 쪼개서 server에 전송
        }

        tmp = buf.substr(end_idx + 1, end_idx + 1 + remainder + 1);
        send(cs, tmp.c_str(), tmp.length(), 0);
    }
    else    // 문자열의 길이가 1024보다 작다면, 문자열 그대로 server에 전송
        send(cs, buf.c_str(), buf.length(), 0);

    recvbuf.resize(buf.length());
    recv(cs, recvbuf.data(), buf.length() * sizeof(int), 0); // server가 보낸 ASCII Code 결과 값들을 받음

    // 출력 부분
    cout << "Receive ";
    for (int i = 0; i < recvbuf.size(); i++) {
        cout << recvbuf[i];
    }
    cout << "\n\n";

    cout << "Detail\n";
    for (int i = 0; i < recvbuf.size(); i++) {
        cout << buf[i] << ": " << recvbuf[i] << "\n";
    }
    cout << "\n";

    close(cs);
}