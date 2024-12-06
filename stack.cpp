#include <iostream>

#include <stack>

#include <string>

#include <cctype>

#include <sstream>

 

using namespace std;

 

int performOperation(int a, int b, char op) {

    switch(op) {

        case '+': return a + b;

        case '-': return a - b;

        case '*': return a * b;

        case '/': return a / b;

        default: return 0;

    }

}

 

int evalpost(const string& expression) {

    stack<int> operands;

    stringstream ss(expression);

    string token;

 

    while (ss >> token) {

        if (isdigit(token[0])) {

            operands.push(stoi(token));

        } else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {

            int b = operands.top(); operands.pop();

            int a = operands.top(); operands.pop();

            int result = performOperation(a, b, token[0]);

            operands.push(result);

        }

    }

    return operands.top();

}

 

int main() {

    string expression;

    cout << "Enter an expression (e.g., 1 9 + 23 *): ";

    getline(cin, expression);

 

    int result = evalpost(expression);

    cout << "Result: " << result << endl;

 

    return 0;

}