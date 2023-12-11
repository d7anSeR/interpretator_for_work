//#pragma once
//#include <iostream>
//#include <map>
//class TokenType {
//private:
//	std::string name = "";
//	std::string regex = "";
//public:
//	TokenType(std::string name = "", std::string regex = "") : name(name), regex(regex) {}
//	std::string GetName() {
//		return name;
//	}
//	std::string GetRegex() {
//		return regex;
//	}
//};
//int main() {
//	std::map<std::string, TokenType> tockenTypeList;
//	tockenTypeList["NUMBER"] = TokenType("NUMBER", "[0-9]*");
//	tockenTypeList["VARIABLE"] = TokenType("VARIABLE", "[a-z]*");
//	tockenTypeList["SEMICOLON"] = TokenType("SEMICOLON", ";");
//	tockenTypeList["SPACE"] = TokenType("SPACE", "[ \\n\\t\\r]");
//	tockenTypeList["LOG"] = TokenType("LOG", "OUTPUT");
//	tockenTypeList["PLUS"] = TokenType("PLUS", "+");
//	tockenTypeList["MINUS"] = TokenType("MINUS", "-");
//	tockenTypeList["LPAR"] = TokenType("LPAR", "\\(");
//	tockenTypeList["RPAR"] = TokenType("RPAR", "\\)");
//}
