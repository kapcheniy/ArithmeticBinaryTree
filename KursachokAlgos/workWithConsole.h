#pragma once
#include <iostream>
#include <string>
#include "genRandExp.h"

void workWithConsole(std::string& expression) {
    std::cout << "1. Enter an expression manually" << std::endl;
    std::cout << "2. Generate a random expression" << std::endl;
    std::cout << "3. Use a predefined expression" << std::endl;
    std::cout << "Choose an option:";
    int choice;
    std::cin >> choice;
    std::cout << std::endl;
    switch (choice) {
    case 1: {
        std::cout << "Enter your infix expression: ";
        std::cin.ignore();
        std::getline(std::cin, expression);
        break;
    }
    case 2: {
        std::cout << "Enter the number of operands:";
        int count;
        std::cin >> count;
        expression = generateRandomExpression(count);
        std::cout << "Generated random expression: " << expression << std::endl;
        break;
    }
    case 3: {
        const std::string variants[] = {
            "(10 + (6 / 2)) * (8 - 3)",
            "(5 + 3) * (7 - 2) / 2",
            "(10 - 8 - (7 - 5))"
        };
        std::cout << "1. " << variants[0] << std::endl;
        std::cout << "2. " << variants[1] << std::endl;
        std::cout << "3. " << variants[2] << std::endl;
        std::cout << "Choose one of the presented options: ";

        int var;
        std::cin >> var;

        if (var >= 1 && var <= 3) {
            expression = variants[var - 1];
            std::cout << "Using predefined expression: " << expression << endl;
        }
        else {
            std::cout << "Invalid choice" << std::endl;
            throw std::invalid_argument("An invalid value has been entered!");
        }
        break;
    }
    default: {
        std::cout << "Invalid choice" << std::endl;
        throw std::invalid_argument("An invalid value has been entered!");
    }
    }
    std::cout << std::endl;
}