#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include "BinaryTree.h"
using namespace std;

int OperatorPriority (char op)      // 연산자 우선 순위 함수
{
    switch (op)
    {
        case '*':
        case '/':
            return 3;
        case '+':
        case '-':
            return 2;
        case '(':
            return 1;
    }
    return -1;
}

int CompareOperatorPriority (char op1, char op2)    // 두 개의 연산자들의 우선 순위를 비교하는 함수
{
    int op1priority = OperatorPriority(op1);
    int op2priority = OperatorPriority(op2);

    if (op1priority > op2priority)      // 우선순위 op1 > op2인 경우
        return 1;
    else if (op1priority < op2priority)     // 우선순위 op1 < op2인 경우
        return -1;
    else    // 우선순위가 같은 경우
        return 0;
}

void ConnectLeftRight (stack<BTreeNode*> &op, char opr) 
{
    BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));
    BTreeNode* rightnd = op.top();
    op.pop();
    BTreeNode* leftnd = op.top();
    op.pop();
    nd->element = opr;
    nd->left = leftnd;
    nd->right = rightnd;
    op.push(nd);
}

BTreeNode* MakeParseTree (string str)     // 입력받은 Infix 표기의 산술식을 parse tree 형태로 만드는 함수
{
    stack<char> opr; // 연산자 스택
    stack<BTreeNode*> op;   // 피연산자 스택

    int i = 0;
    char topOpr;
    while (i < str.size())
    {
        if (isdigit(str[i]))
        {
            BTreeNode* nd = (BTreeNode*)malloc(sizeof(BTreeNode));
            nd->element = str[i] - '0';
            nd->left = NULL;
            nd->right = NULL;
            op.push(nd);
            i++;
        }
        else
        {
            switch (str[i])
            {
                case '(':
                    opr.push(str[i]);
                    i++;
                    break;
                case ')':
                    while (1)
                    {
                        topOpr = opr.top();
                        opr.pop();
                        if (topOpr == '(')  
                        {
                            i++;
                            break;
                        }

                        ConnectLeftRight (op, topOpr); // 닫힌 괄호 )가 아닌 경우의 과정
                    }
                    break;
                case '+': case '-':
                case '*': case '/':
                    if (opr.empty())    opr.push(str[i]);
                    else if (!opr.empty() && CompareOperatorPriority(str[i], opr.top()) == 1) // 입력 opr가 opr.stack의 opr보다 연산 순위가 큰 경우
                    {
                        opr.push(str[i]);
                    }
                    else if (!opr.empty() && CompareOperatorPriority(str[i], opr.top()) <= 0) // 그렇지 않은 경우 (작거나 같은)
                    {
                        while (!opr.empty() && CompareOperatorPriority(str[i], opr.top()) <= 0) //연산자 스택에 + *가 있는 상태에서 str[i]가 -일 때, *와 +를 스택에서 먼저 내보내고 마지막에 -를 넣어야함 
                        {
                            topOpr = opr.top();
                            opr.pop();

                            ConnectLeftRight (op, topOpr);
                        }
                        opr.push(str[i]);
                    }
                    i++;
                    break;
            }
        }
    }

    while (!opr.empty())    // 산술식에 접근하는 인덱스 i가 범위를 벗어났을 때 연산자 스택에 아직 연산자가 남아있는 경우, 차례로 두 개의 피연산자와 함께 연산
    {
        topOpr = opr.top();
        opr.pop();

        ConnectLeftRight (op, topOpr);
    }

    return op.top();    // 최종 Parse tree
}