#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include "MemoryCounter.h"

extern size_t cur_mem;
extern size_t max_mem;
extern size_t tree_cur_mem;
extern size_t tree_max_mem;

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;
    Node(string val) : value(val), left(nullptr), right(nullptr) {
        TREE_ALLOCATE_MEMORY(sizeof(Node));
    }

    ~Node() {
        TREE_FREE_MEMORY(sizeof(Node));
    }
};

class ExpressionTree {
private:
    Node* root;

    bool isOperator(const string& s);
    bool isDigit(const char c);
    double evaluate(Node* node);
    void buildSubTree(Node* operands[], string operators[], int& operandIndex, int& operatorIndex);
    void toInfix(Node* node, string& result);
    void toPrefix(Node* node, string& result);
    void toPostfix(Node* node, string& result);
    bool isValidExpression(Node* node);
    void printTree(Node* node, string prefix = "", bool isRight = true, bool isRoot = true);
    int precedence(const string& op);
    void deleteTree(Node* node);

public:
    ExpressionTree();
    ~ExpressionTree();

    void print();
    bool isValidExpression();
    void buildFromInfix(const string& infix);

    bool isSpace(char c);
    void skipSpace(int& i);
    bool isNumberOrUnaryMinus(const string& infix, int i);
    void processNumber(const string& infix, int& i, Node* operands[], int& operandIndex);
    void processOpenParenthesis(string operators[], int& operatorIndex, int& i, int& openParenthesisCount);
    void processCloseParenthesis(Node* operands[], string operators[], int& operandIndex, int& operatorIndex, int& i, int& closeParenthesisCount);
    void processOperator(char op, string operators[], Node* operands[], int& operandIndex, int& operatorIndex, int& i);
    void finalizeExpression(Node* operands[], string operators[], int& operandIndex, int& operatorIndex);
    void validateExpression(int operandIndex, int openParenthesisCount, int closeParenthesisCount);

    string toInfix();
    string toPrefix();
    string toPostfix();
    double evaluate();
};

