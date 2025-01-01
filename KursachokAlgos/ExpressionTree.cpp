#include "ExpressionTree.h"

bool ExpressionTree::isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

bool ExpressionTree::isDigit(const char c) {
    return c >= '0' && c <= '9';
}

double ExpressionTree::evaluate(Node* node) {
    if (!node) throw runtime_error("Empty node in evaluation!");
    if (!isOperator(node->value)) return stod(node->value);

    double left = evaluate(node->left);
    double right = evaluate(node->right);


    if (node->value == "+") return left + right;
    if (node->value == "-") return left - right;
    if (node->value == "*") return left * right;
    if (node->value == "/") {
        if (right == 0) throw runtime_error("Division by zero!");
        return left / right;
    }

    throw runtime_error("Invalid operator!");
}

void ExpressionTree::buildSubTree(Node* operands[], string operators[], int& operandIndex, int& operatorIndex) {
    if (operandIndex < 1 || operatorIndex < 0) throw runtime_error("Invalid expression!");

    Node* right = operands[operandIndex--];
    Node* left = operands[operandIndex--];
    string op = operators[operatorIndex--];
    TREE_ALLOCATE_MEMORY(op.size());
    Node* newNode = new Node(op);
    newNode->left = left;
    newNode->right = right;

    operands[++operandIndex] = newNode;
}


void ExpressionTree::toInfix(Node* node, string& result) {
    if (!node) return;
    if (node->left || node->right) result += "( ";
    toInfix(node->left, result);
    result += node->value + " ";
    toInfix(node->right, result);
    if (node->left || node->right) result += ") ";
}

void ExpressionTree::toPrefix(Node* node, string& result) {
    if (!node) return;
    result += node->value + " ";
    toPrefix(node->left, result);
    toPrefix(node->right, result);
}

void ExpressionTree::toPostfix(Node* node, string& result) {
    if (!node) return;
    toPostfix(node->left, result);
    toPostfix(node->right, result);
    result += node->value + " ";
}

bool ExpressionTree::isValidExpression(Node* node) {
    if (!node) return true;
    if (node->value == "/" && node->right && node->right->value == "0") {
        return false;
    }
    if (!isOperator(node->value)) {
        return isdigit(node->value[0]) || node->value[0] == '-';
    }
    return isValidExpression(node->left) && isValidExpression(node->right);
}

void ExpressionTree::printTree(Node* node, string prefix, bool isRight, bool isRoot) {
    if (!node) {
        cout << prefix << (isRight ? "R-- " : "L-- ") << "null" << endl;
        return;
    }

    if (isRoot) {
        cout << "ROOT " << node->value << endl;
    }
    else {
        cout << prefix << (isRight ? "R-- " : "L-- ") << node->value << endl;
    }

    if (node->right || node->left) {
        printTree(node->right, prefix + (isRoot ? "    " : (isRight ? "|   " : "    ")), true, false);
        printTree(node->left, prefix + (isRoot ? "    " : (isRight ? "|   " : "    ")), false, false);
    }
}
ExpressionTree::ExpressionTree() : root(nullptr) {}

ExpressionTree::~ExpressionTree() {
    deleteTree(root);
    root = nullptr;
}

void ExpressionTree::print() {
    printTree(root);
}

bool ExpressionTree::isValidExpression() {
    if (!root) throw runtime_error("Empty tree");
    evaluate(root);
    return isValidExpression(root);
}

void ExpressionTree::buildFromInfix(const string& infix) {
    Node* operands[100];
    string operators[100];
    TREE_ALLOCATE_MEMORY(100);
    int operandIndex = -1, operatorIndex = -1;
    TREE_ALLOCATE_MEMORY(sizeof(int));
    TREE_ALLOCATE_MEMORY(sizeof(int));
    int length = infix.size();
    TREE_ALLOCATE_MEMORY(sizeof(int));
    int i = 0;
    TREE_ALLOCATE_MEMORY(sizeof(int));

    int openParenthesisCount = 0;
    TREE_ALLOCATE_MEMORY(sizeof(int));
    int closeParenthesisCount = 0;
    TREE_ALLOCATE_MEMORY(sizeof(int));

    char lastChar = '\0';

    while (i < length) {
        if (isSpace(infix[i])) {
            skipSpace(i);
        }
        else if (isNumberOrUnaryMinus(infix, i)) {
            processNumber(infix, i, operands, operandIndex);
            lastChar = 'n';
        }
        else if (infix[i] == '(') {
            if (lastChar == 'n') {
                throw runtime_error("Invalid syntax: number directly before '(' is not allowed!");
            }
            processOpenParenthesis(operators, operatorIndex, i, openParenthesisCount);
            lastChar = '(';
        }
        else if (infix[i] == ')') {
            if (lastChar == 'o') {
                throw runtime_error("Invalid syntax: operator before ')' are not allowed!");
            }
            if (lastChar == '(') {
                throw runtime_error("Invalid syntax: empty parentheses '()' are not allowed!");
            }
            processCloseParenthesis(operands, operators, operandIndex, operatorIndex, i, closeParenthesisCount);
            lastChar = ')';
        }
        else if (isOperator(string(1, infix[i]))) {
            if (lastChar == '(' || lastChar == 'o') {
                throw runtime_error("Invalid syntax: operator directly after '(' or another operator is not allowed!");
            }
            processOperator(infix[i], operators, operands, operandIndex, operatorIndex, i);
            lastChar = 'o';
        }
        else {
            throw runtime_error("Invalid character in expression!");
        }
    }

    if (lastChar == 'o') {
        throw runtime_error("Invalid syntax: expression cannot end with an operator!");
    }

    finalizeExpression(operands, operators, operandIndex, operatorIndex);

    validateExpression(operandIndex, openParenthesisCount, closeParenthesisCount);

    root = operands[operandIndex];
}


bool ExpressionTree::isSpace(char c) {
    return c == ' ';
}

void ExpressionTree::skipSpace(int& i) {
    i++;
}

bool ExpressionTree::isNumberOrUnaryMinus(const string& infix, int i) {
    return isDigit(infix[i]) || (infix[i] == '-' && (i + 1 < infix.size() && isDigit(infix[i + 1])));
}

void ExpressionTree::processNumber(const string& infix, int& i, Node* operands[], int& operandIndex) {
    int start = i;
    TREE_ALLOCATE_MEMORY(sizeof(int));
    if (infix[i] == '-') i++;
    while (i < infix.size() && isDigit(infix[i])) {
        i++;
    }
    string token = infix.substr(start, i - start);
    TREE_ALLOCATE_MEMORY(token.size());
    operands[++operandIndex] = new Node(token);
}

void ExpressionTree::processOpenParenthesis(string operators[], int& operatorIndex, int& i, int& openParenthesisCount) {
    operators[++operatorIndex] = "(";
    openParenthesisCount++;
    i++;
}

void ExpressionTree::processCloseParenthesis(Node* operands[], string operators[], int& operandIndex, int& operatorIndex, int& i, int& closeParenthesisCount) {
    closeParenthesisCount++;
    while (operatorIndex >= 0 && operators[operatorIndex] != "(") {
        buildSubTree(operands, operators, operandIndex, operatorIndex);
    }
    if (operatorIndex < 0) {
        throw runtime_error("Mismatched parentheses!");
    }
    operatorIndex--;
    i++;
}

void ExpressionTree::processOperator(char op, string operators[], Node* operands[], int& operandIndex, int& operatorIndex, int& i) {
    string token(1, op);
    TREE_ALLOCATE_MEMORY(1);
    while (operatorIndex >= 0 && precedence(operators[operatorIndex]) >= precedence(token)) {
        buildSubTree(operands, operators, operandIndex, operatorIndex);
    }
    operators[++operatorIndex] = token;
    i++;
}

void ExpressionTree::finalizeExpression(Node* operands[], string operators[], int& operandIndex, int& operatorIndex) {
    while (operatorIndex >= 0) {
        buildSubTree(operands, operators, operandIndex, operatorIndex);
    }
}

void ExpressionTree::validateExpression(int operandIndex, int openParenthesisCount, int closeParenthesisCount) {
    if (operandIndex != 0) {
        throw runtime_error("Invalid expression!");
    }
    if (openParenthesisCount != closeParenthesisCount) {
        throw runtime_error("Mismatched parentheses: open and close counts do not match!");
    }
}

string ExpressionTree::toInfix() {
    string result;
    toInfix(root, result);
    ALLOCATE_MEMORY(result.size());
    return result;
}

string ExpressionTree::toPrefix() {
    string result;
    toPrefix(root, result);
    ALLOCATE_MEMORY(result.size());
    return result;
}

string ExpressionTree::toPostfix() {
    string result;
    toPostfix(root, result);
    ALLOCATE_MEMORY(result.size());
    return result;
}

double ExpressionTree::evaluate() {
    if (!root) throw runtime_error("Empty tree");
    return evaluate(root);
}

int ExpressionTree::precedence(const string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}
void ExpressionTree::deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}