//#include <iostream>
//#include <string>
//#include <vector>
//#include <cctype>
//#include <fstream>
//
//using namespace std;
//
//enum TokenType {
//    KEYWORD, IDENTIFIER, INTEGER, FLOAT, LEFT_BRACE, RIGHT_BRACE, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
//    ASSIGNMENT_OPERATOR, LESS_THAN_TO_OPERATOR, MORE_THAN_TO_OPERATOR, 
//    LESS_THAN_OR_EQUAL_TO_OPERATOR, MORE_THAN_OR_EQUAL_TO_OPERATOR, ADDITION_OPERATOR, COMMA, COLON_OPERATOR,
//    SEMICOLON
//};
//
//struct Token {
//    TokenType type;
//    string value;
//};
//
//bool whitespace(char c) {
//    return isspace(c);
//}
//
//vector<Token> tokenize(string input) {
//    vector<Token> tokens; 
//    string current = "";
//    for (char c : input) {
//        if (current == "main") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "var") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "if") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "else") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "for") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "while") {
//            tokens.push_back({ KEYWORD, current });
//            current = "";
//        }
//        else if (current == "<=") {
//            tokens.push_back({ LESS_THAN_OR_EQUAL_TO_OPERATOR, current });
//            current = "";
//        }
//        else if (current == ">=") {
//            tokens.push_back({ MORE_THAN_OR_EQUAL_TO_OPERATOR, current });
//            current = "";
//        }
//        else if (isalpha(c)) {
//            current += c;
//        }
//        else if (current != "") {
//            tokens.push_back({ IDENTIFIER, current });
//            current = "";
//        }
//        else if (isdigit(c)) {
//            current += c;
//        }
//        else if (current != "") {
//            tokens.push_back({ INTEGER, current });
//            current = "";
//        }
//        else if (c == '.') {
//            current += c;
//        }
//        else if (current != "") {
//            tokens.push_back({ FLOAT, current });
//            current = "";
//        }
//        else if (c == '{') {
//            tokens.push_back({ LEFT_BRACE, "{" });
//        }
//        else if (c == '}') {
//            tokens.push_back({ RIGHT_BRACE, "}" });
//        }
//        else if (c == '(') {
//            tokens.push_back({ LEFT_PARENTHESIS, "(" });
//        }
//        else if (c == ')') {
//            tokens.push_back({ RIGHT_PARENTHESIS, ")" });
//        }
//        else if (c == '=') {
//            tokens.push_back({ ASSIGNMENT_OPERATOR, "=" });
//        }
//        else if (c == '<') {
//            tokens.push_back({ LESS_THAN_TO_OPERATOR, "<" });
//        }
//        else if (c == '>') {
//            tokens.push_back({ MORE_THAN_TO_OPERATOR, ">" });
//        }
//        else if (c == '+') {
//            tokens.push_back({ ADDITION_OPERATOR, "+" });
//        }
//        else if (c == ',') {
//            tokens.push_back({ COMMA, "," });
//        }
//        else if (c == ':') {
//            tokens.push_back({ COLON_OPERATOR, ":" });
//        }
//        else if (c == ';') {
//            tokens.push_back({ SEMICOLON, ";" });
//        }
//    }
//
//    return tokens;
//}
//
//int main() {
//    ifstream in("course_.txt");
//    if (in.is_open()) {
//        string input;
//        while (getline(in, input))
//        {
//            vector<Token> tokens = tokenize(input);
//            for (Token token : tokens) {
//                cout << token.value << ": ";
//                switch (token.type) {
//                case KEYWORD:
//                    cout << "KEYWORD";
//                    break;
//                case IDENTIFIER:
//                    cout << "IDENTIFIER";
//                    break;
//                case INTEGER:
//                    cout << "INTEGER";
//                    break;
//                case FLOAT:
//                    cout << "FLOAT";
//                    break;
//                case LEFT_BRACE:
//                    cout << "LEFT_BRACE";
//                    break;
//                case RIGHT_BRACE:
//                    cout << "RIGHT_BRACE";
//                    break;
//                case LEFT_PARENTHESIS:
//                    cout << "LEFT_PARENTHESIS";
//                    break;
//                case RIGHT_PARENTHESIS:
//                    cout << "RIGHT_PARENTHESIS";
//                    break;
//                case ASSIGNMENT_OPERATOR:
//                    cout << "ASSIGNMENT_OPERATOR";
//                    break;
//                case LESS_THAN_OR_EQUAL_TO_OPERATOR:
//                    cout << "LESS_THAN_OR_EQUAL_TO_OPERATOR";
//                    break;
//                case LESS_THAN_TO_OPERATOR:
//                    cout << "LESS_THAN_TO_OPERATOR";
//                    break;
//                case MORE_THAN_OR_EQUAL_TO_OPERATOR:
//                    cout << "MORE_THAN_OR_EQUAL_TO_OPERATOR";
//                    break;
//                case MORE_THAN_TO_OPERATOR:
//                    cout << "MORE_THAN_TO_OPERATOR";
//                    break;
//                case ADDITION_OPERATOR:
//                    cout << "ADDITION_OPERATOR";
//                    break;
//                case COMMA:
//                    cout << "COMMA";
//                    break;
//                case COLON_OPERATOR:
//                    cout << "COLON_OPERATOR";
//                    break;
//                case SEMICOLON:
//                    cout << "SEMICOLON";
//                    break;
//                }
//
//                cout << endl;
//            }
//        }
//    }
//    return 0;
//}