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
    int ss, sa;
    struct sockaddr_in ssa;
    string recv_filename;
    vector<string> sendbuf;
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

        recv(sa, recvsize, sizeof(recvsize), 0); // 파일 이름의 길이 받음

        // client가 보낸 파일 이름 받기
        while (1) {
            char buf[1024];
            int len = recv(sa, buf, sizeof(buf), 0);
            if (len <= 0)   break;

            for (int i = 0; i < len; i++) {
                recv_filename += buf[i];
            }
            memset(buf, 0, sizeof(buf));

            if (recv_filename.size() == recvsize[0]) break;
        }

        // ex) "R: Lyrics.txt"
        string filename = recv_filename.substr(3);

        if (recv_filename[0] == 'R') {
            ifstream file(filename);

            if (file.is_open()) {
                string line;
                while (getline(file, line)) {
                    sendbuf.push_back(line);
                }
                file.close();
            }
            else {
                sendbuf.push_back("The file does not exist.");
            }
        }
        else if (recv_filename[0] == 'W') {
            ofstream file(filename);

            vector<string> recvcontent = receiveVector(sa);

            if (file.is_open()) {
                for (const string& str : recvcontent) {
                    file << str << endl;
                }
                file.close();
                sendbuf.push_back("The file was created successfully.");
            }
            else {
                sendbuf.push_back("Unable to open file.");
            }
        }

        sendVector(sa, sendbuf);

        recv_filename.clear();
        sendbuf.clear();
        close(sa);
    }

    return 0;
}
