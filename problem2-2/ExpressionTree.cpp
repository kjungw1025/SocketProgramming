#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "ExpressionTree.h"
using namespace std;

string calculationFormula;

void postOrder (SearchTree T)
{
    if (T != NULL)
    {
        postOrder(T->left);
        postOrder(T->right);
        if (T->element - '*' == 0 || T->element - '*' == 1 || T->element - '*' == 3 || T->element - '*' == 5) {
            calculationFormula += T->element;
        }
        else {
            calculationFormula += to_string(T->element);
        }
    }
}

string returnFormular () {
    return calculationFormula;
}