#include "ExpressionTree.h"
#include "genRandExp.h"
#include "workWithConsole.h"

size_t cur_mem = 0;
size_t max_mem = 0;
size_t tree_cur_mem = 0;
size_t tree_max_mem = 0;

using namespace std;
    

int main() {
    try {
        string expression;
        workWithConsole(expression);

        ExpressionTree tree;

        tree.buildFromInfix(expression);
        cout << "Tree structure:" << endl;
        tree.print();
        if (tree.isValidExpression())
        {
            cout << "Is valid expression: Yes" << endl;
            cout << "Infix: " << tree.toInfix() << endl;
            cout << "Prefix: " << tree.toPrefix() << endl;
            cout << "Postfix: " << tree.toPostfix() << endl;
            cout << "Evaluated value: " << tree.evaluate() << endl << endl;
        }
        else
        {
            cout << "Is valid expression: No" << endl;
        }
        
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
    }
    cout << "\nMemory usage statistics for tree:" << endl;
    cout << "Current memory used (cur_mem): " << tree_cur_mem << " bytes" << endl;
    cout << "Maximum memory allocated (max_mem): " << tree_max_mem << " bytes" << endl;
    cout << "\nMemory usage statistics for output formats:" << endl;
    cout << "Current memory used (cur_mem): " << cur_mem << " bytes" << endl;
    cout << "Maximum memory allocated (max_mem): " << max_mem << " bytes" << endl;
    return 0;
}

