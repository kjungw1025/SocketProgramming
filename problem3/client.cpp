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
    char recvbuf[1024];
    struct sockaddr_in csa;

    memset(&csa, 0, sizeof(csa));
    csa.sin_family = AF_INET;
    csa.sin_addr.s_addr = inet_addr("192.168.35.141");
    csa.sin_port = htons(11234);

    cs = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    connect(cs, (struct sockaddr *) &csa, sizeof(csa));

    cout << "----------------------------------------------------------------------------------------" << '\n';
    cout << "If you want to find the ip corresponding to the domain, type it in the following format." << '\n';
    cout << "ex) D: www.naver.com" << '\n';
    cout << "----------------------------------------------------------------------------------------" << '\n';
    cout << "If you want to find the domain corresponding to the ip, type it in the following format." << '\n';
    cout << "ex) I: 123.456.789.123" << '\n';    
    cout << "----------------------------------------------------------------------------------------" << '\n';
    cout << "If you want to add a domain and an ip, type it in the following format." << '\n';
    cout << "ex) W: www.naver.com 123.456.789.123" << '\n';
    cout << "----------------------------------------------------------------------------------------" << '\n';
    cout << "Input request : ";
    getline(cin, buf);

    buf_size[0] = buf.size();
    send(cs, buf_size, sizeof(buf_size), 0);
    send(cs, buf.c_str(), buf.length(), 0);

    recv(cs, recvbuf, sizeof(recvbuf), 0);
    cout << "Receive: " << recvbuf << "\n\n";

    close(cs);
}

