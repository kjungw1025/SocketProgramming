#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "ExpressionTree.h"
using namespace std;

int main()
{
    int ss, sa;
    struct sockaddr_in ssa;
    string recvbuf;
    int recvsize[1];
    int sendbuf[1];

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

        BTreeNode* nd = MakeParseTree(recvbuf);
        postOrder(nd);

        string formula = returnFormular();
        stack<int> s;
        for (int i = 0; i < formula.size(); i++) {
            if (formula[i] - '*' == 0 || formula[i] - '*' == 1 || formula[i] - '*' == 3 || formula[i] - '*' == 5) {
                int operand2 = s.top();
                s.pop();
                int operand1 = s.top();
                s.pop();

                switch (formula[i] - '*') {
                    case 0:
                        s.push(operand1 * operand2);
                        break;
                    case 1:
                        s.push(operand1 + operand2);
                        break;
                    case 3:
                        s.push(operand1 - operand2);
                        break;
                    case 5:
                        s.push(operand1 / operand2);
                        break;
                }
            }
            else
                s.push(formula[i] - '0');
        }        

        sendbuf[0] = s.top();
        s.pop();

        send(sa, sendbuf, sizeof(sendbuf), 0);

        recvbuf.clear();
        close(sa);
    }
}