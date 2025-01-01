#pragma once
#include <string>
#include <stdexcept>
#include <ctime>

std::string generateRandomExpression(int numOperands = 3) {
    srand(time(0));
    if (numOperands < 2) {
        throw std::invalid_argument("Number of operands must be at least 2!");
    }
    if (numOperands % 2 == 1)   numOperands++;
    std::string expression = "";
    std::string operators = "+-*/";
    for (int i = 0; i < numOperands; ++i) {
        int rand_value = 0;
        if (expression != "" && (rand() % 2 == 0)) {
            while (rand_value == 0) {
                rand_value = rand() % 201 - 100;
            }
            expression = "( " + expression + " " + operators[rand() % 4] + " " + std::to_string(rand_value) + " )";
        }
        else {
            while (rand_value == 0) {
                rand_value = rand() % 201 - 100;
            }
            if (expression != "") {
                expression = expression + " " + (operators[rand() % 4]) + " ";
            }
            expression += std::to_string(rand_value);
        }
    }

    return expression;
}