#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> receiveVector(int socket) {
    vector<string> data;

    // 벡터의 크기를 수신
    uint32_t dataSize;
    recv(socket, &dataSize, sizeof(dataSize), 0);
    dataSize = ntohl(dataSize);

    // 각 문자열을 수신
    for (int i = 0; i < dataSize; i++) {
        uint32_t strSize;
        recv(socket, &strSize, sizeof(strSize), 0);
        strSize = ntohl(strSize);

        string str(strSize, ' ');
        recv(socket, &str[0], strSize, 0);
        data.push_back(str);
    }

    return data;
}

void sendVector(int socket, const vector<string>& data) {
    // 벡터의 크기를 전송
    uint32_t dataSize = htonl(data.size());
    send(socket, &dataSize, sizeof(dataSize), 0);

    // 각 문자열을 전송
    for (const string& str : data) {
        uint32_t strSize = htonl(str.size());
        send(socket, &strSize, sizeof(strSize), 0);
        send(socket, str.c_str(), str.size(), 0);
    }
}

int main()
{
    int cs;
    string buf;
    int buf_size[1];
    vector<string> sendcontent;
    vector<string> recvbuf;
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("127.0.0.1");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    cout << "If you want to read the file, please write 'R: ' before it" << '\n';
    cout << "If you want to write the file, please write 'W: ' before it" << '\n';
    cout << "Ex) R: Lyrics.txt" << '\n';
    cout << "Please enter a file name : ";
    getline(cin, buf);

    if (buf[0] == 'R') {
        buf_size[0] = buf.length();
        send(cs, buf_size, sizeof(buf_size), 0); // server에, client가 입력한 문자열의 길이를 우선적으로 전송
        send(cs, buf.c_str(), buf.length(), 0);
    }
    else if (buf[0] == 'W') {
        string content;
        while (1) {
            bool flag;
            cout << "Enter 1 or 0 to continue writing : ";
            cin >> flag;

            if (!flag) break;

            cout << "Please enter what you want to write in the file" << '\n';
            cin.ignore();
            getline(cin, content, '\n');
            sendcontent.push_back(content);
        }

        buf_size[0] = buf.length();
        send(cs, buf_size, sizeof(buf_size), 0); // server에, client가 입력한 문자열의 길이를 우선적으로 전송
        send(cs, buf.c_str(), buf.length(), 0);

        sendVector(cs, sendcontent);
    }
    else {
        cout << "Please fill out the form." << '\n';
        return 1;
    }

    recvbuf = receiveVector(cs);

    for (int i = 0; i < recvbuf.size(); i++) {
        cout << recvbuf[i] << '\n';
    }

    close(cs);
}
