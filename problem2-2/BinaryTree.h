#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stack>
#include <string>

typedef int ElementType;
typedef struct BTreeNode* SearchTree;
typedef struct BTreeNode {
    ElementType element;
    SearchTree left;
    SearchTree right;
} BTreeNode;

int OperatorPriority (char op); // 연산자 우선 순위 함수
int CompareOperatorPriority (char op1, char op2);   // 두 개의 연산자들의 우선 순위를 비교하는 함수
void ConnectLeftRight (std::stack<BTreeNode*> &op, char opr);
BTreeNode* MakeParseTree (std::string str); // 입력받은 Infix 표기의 산술식을 parse tree 형태로 만드는 함수

#endif