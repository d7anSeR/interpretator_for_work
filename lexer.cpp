#include <string>
#include <iostream>

using namespace std;
typedef string STR;
enum TokenType {
	KEYWORD, IDENTIFIER, INTEGER, FLOAT, LEFT_BRACE, RIGHT_BRACE, LEFT_PARENTHESIS, RIGHT_PARENTHESIS,
	ASSIGNMENT_OPERATOR, LESS_THAN_TO_OPERATOR, MORE_THAN_TO_OPERATOR,
	LESS_THAN_OR_EQUAL_TO_OPERATOR, MORE_THAN_OR_EQUAL_TO_OPERATOR, ADDITION_OPERATOR, COMMA, COLON_OPERATOR,
	SEMICOLON
};

struct Token {
	TokenType type;
	string value;
};
class Tel {
public:
	Tel() :pre(NULL), next(NULL), last(NULL), first(NULL) {}
	STR text;
	Tel* parent = NULL;
	Tel* pre = NULL;
	Tel* next = NULL;
	Tel* first = NULL;
	Tel* last = NULL;
	Tel* Add(Tel* elem) {
		elem->Delete();
		if (first == NULL) {
			first = elem;
			last = first;
			first->pre = NULL;
			first->next = NULL;
			first->parent = this;
			return first;
		}
		last->next = elem;
		last->next->pre = last;
		last->next->parent = this;
		last->next->next = NULL;
		last = last->next;
		return last;
	}
	Tel* Delete() { // Удаляет элемент из списка 

		if (parent != 0) // Если удаляемый элемент являеться последним в списке 
			if (parent->last == this) parent->last = pre;

		if (parent != 0) // Если удаляемый элемент являеться Первым в списке 
			if (parent->first == this) parent->first = next;

		if (pre != 0) pre->next = next;// Отсоеденяем от предыдыщего 
		if (next != 0) next->pre = pre;// Отсоеденяем от следующего 

		next = 0;
		pre = 0;
		parent = 0;

		return this;
	}
	Tel* Add(STR istr) {
		Tel* result = NULL;
		if (istr != "") {
			result = new Tel();
			result->text = istr;
			Add(result);
		}
		return result;
	}
	void Brackets(char s1, char s2) {
		Tel* next_elem = first;
		Tel* result = NULL;
		Tel* mel = NULL;
		while (next_elem != NULL) {
			/*while (next_elem->first != NULL) {
				next_elem = next_elem->first;
			}*/
			mel = next_elem->next;
			if (next_elem->text[0] == s1) {
				if (result != NULL)
					result = result->Add(next_elem);
				else
					result = next_elem;
			}
			else if (next_elem->text[0] == s2) {
				next_elem->Delete();
				result = result->parent;
				if (result == this)
					result = NULL;
			}
			else if (result != NULL)
				result->Add(next_elem);
			next_elem = mel;
		}
	}

};
class Lexer {
private:
	int curr_pos = 0;
	string curr_str = "";
public:
	Lexer(int curr_pos = 0, string curr_str = "") : curr_pos(curr_pos), curr_str(curr_str) {}
	bool CheckLetter(char ichar) {
		if ((ichar >= 'a' && ichar <= 'z') || (ichar >= 'A' && ichar <= 'Z') || ichar == '_')
			return true;
		return false;
	}
	bool CheckDigit(char ichar) {
		if (ichar >= '0' && ichar <= '9')
			return true;
		return false;
	}
	bool CheckDigitLetter(char ichar) {
		return (CheckLetter(ichar) || CheckDigit(ichar));
	}
	string ReadWord() {
		string result = "";
		if (CheckLetter(curr_str[curr_pos])) {
			while (curr_pos < curr_str.length() && CheckDigitLetter(curr_str[curr_pos])) {
				result += curr_str[curr_pos];
				curr_pos++;
			}
		}
		return result;
	}
	string ReadDigit() {
		string result = "";
		if (CheckDigit(curr_str[curr_pos])) {
			while (curr_pos < curr_str.length() && CheckDigitLetter(curr_str[curr_pos])) {
				result += curr_str[curr_pos];
				curr_pos++;
			}
		}
		return result;
	}
	string ReadSign() {
		string result = "";
		if (curr_pos < curr_str.length()) {
			string temp_sign = "";
			temp_sign += curr_str[curr_pos];
			if (
				(temp_sign == "(") ||
				(temp_sign == ")") ||
				(temp_sign == "<") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == ">") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "=") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "!") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "{") ||
				(temp_sign == "}") ||
				(temp_sign == "[") ||
				(temp_sign == "]") ||
				(temp_sign == "+") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "-") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "^") ||
				(temp_sign == "/") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "*") && (curr_str[curr_pos + 1] != '=') ||
				(temp_sign == "%") ||
				(temp_sign == ";")
				) {
				result = temp_sign;
				curr_pos += 1;
			}
			else if ((curr_pos + 1 < curr_str.length()) && (
				(temp_sign == "<") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == ">") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "=") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "!") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "+") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "-") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "/") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == "*") && (curr_str[curr_pos + 1] == '=')
				)) {
				temp_sign += curr_str[curr_pos + 1];
				result = temp_sign;
				curr_pos += 2;
			}
		}
		return result;
	}
	string ReadTabs() {
		string result = "";
		while ((curr_str[curr_pos] == ' ' || curr_str[curr_pos] == '\n' || curr_str[curr_pos] == '\t')
			&& curr_pos < curr_str.length()) {
			result += curr_str[curr_pos];
			curr_pos++;
		}
		return result;
	}

	Tel* ReadWordTel(const string& istr) {
		curr_pos = 0;
		curr_str = istr;
		int len = istr.length();
		Tel* result = new Tel();
		while (curr_pos < len) {
			result->Add(ReadWord());
			result->Add(ReadDigit());
			ReadTabs();
			result->Add(ReadSign());
		}
		return result;
	}
	void Print(Tel* el, string elem) {
		Tel* iel = el;
		while (iel != NULL) {
			std::cout << elem << iel->text << endl;
			if (iel->first != NULL)
				Print(iel->first, elem + " ");
			iel = iel->next;
		}
	}

};

int main() {
	STR prog = "FUN (1 2) {A[2] != 3; A[2] = 20; }";
	Lexer lexer;
	Tel* pro = lexer.ReadWordTel(prog);
	pro->Brackets('(', ')');
	pro->Brackets('[', ']');
	pro->Brackets('{', '}');
	lexer.Print(pro, " ");
}