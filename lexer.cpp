#include <map>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;
typedef string STR;
std::map<unsigned, std::string> TokenType
{
	{1, "DIGIT_INT"}, {2, "DIGIT_DOUBLE"} , {3, "WORD"}, {4, "SIGN"}
};

class Lexer;
class Tel {
	STR text = "";
	STR result = "";
	STR token_type;
	Tel* parent = NULL;
	Tel* pre = NULL;
	Tel* next = NULL;
	Tel* first = NULL;
	Tel* last = NULL;
	friend class Lexer;
	friend class Parser;
public:
	Tel() : text(""), result(""), parent(NULL), pre(NULL), next(NULL), last(NULL), first(NULL) {}
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
	Tel* Add(STR istr, STR type) {
		Tel* result = NULL;
		if (istr != "") {
			result = new Tel();
			result->text = istr;
			result->token_type = type;
			Add(result);
		}
		return result;
	}
	void Brackets(char s1, char s2) {
		Tel* next_elem = first;
		Tel* result = NULL;
		Tel* mel = NULL;
		while (next_elem != NULL) {
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
class Parser {
private:
	Tel* cur;
public:
	Parser() {}
	void Operation(Tel* node) {
		try {
			if (node->first != NULL) {
				Operation(node->first);
			}
			if (node->next != NULL) {
				Operation(node->next);
			}
			if (node->first == NULL) {

				if (node->first->token_type == "DIGIT_INT" && node->first->next->token_type == "DIGIT_INT")
				{
					if (node->text == "^")
						node->result = to_string(pow(stoi(node->first->text), stoi(node->first->next->text)));
					if (node->text == "%")
						node->result = to_string(stoi(node->first->text) % stoi(node->first->next->text));
					if (node->text == "*")
						node->result = to_string(stoi(node->first->text) * stoi(node->first->next->text));
					if (node->text == "/" && stoi(node->first->next->text) != 0)
						node->result = to_string(stoi(node->first->text) / stoi(node->first->next->text));
					if (node->text == "+")
						node->result = to_string(stoi(node->first->text) + stoi(node->first->next->text));
					if (node->text == "-")
						node->result = to_string(stoi(node->first->text) - stoi(node->first->next->text));
					node->token_type = "DIGIT_INT";
				}
				else if ((node->first->token_type == "DIGIT_DOUBLE" && node->first->next->token_type == "DIGIT_DOUBLE") ||
					(node->first->token_type == "DIGIT_DOUBLE" && node->first->next->token_type == "DIGIT_INT") ||
					(node->first->token_type == "DIGIT_INT" && node->first->next->token_type == "DIGIT_DOUBLE")
					) {
					if (node->text == "^")
						node->result = to_string(pow(stod(node->first->text), stod(node->first->next->text)));
					if (node->text == "%")
						node->result = to_string(stoi(node->first->text) % stoi(node->first->next->text));
					if (node->text == "*")
						node->result = to_string(stod(node->first->text) * stod(node->first->next->text));
					if (node->text == "/")
						node->result = to_string(stod(node->first->text) / stod(node->first->next->text));
					if (node->text == "+")
						node->result = to_string(stod(node->first->text) + stod(node->first->next->text));
					if (node->text == "-")
						node->result = to_string(stod(node->first->text) - stod(node->first->next->text));
					node->token_type = "DIGIT_DOUBLE";
				}
				else if (node->text == "(") {
					Runs(node);
					node->token_type = node->first->token_type;
					node->result = node->first->result;
				}
				else
					throw std::string{ "an attempt was made to perform an operation with numbers on other data types..." };
			}
			else
				throw std::string{ "an attempt was made to access the NULL pointer..." };
		}
		catch (std::string error_message) {
			std::cout << error_message << endl;
		}

	}
	void Print(Tel* node) {
		Tel* iel = node->first;
		if (iel != NULL && iel->next->text == "(") {
			Runs(iel->next);
			Tel* elem = NULL;
			if (iel->next != NULL) elem = iel->next->first;
			while (elem != NULL) {
				cout << elem->result;
				elem = elem->next;
			}
		}

	}
	void Runs(Tel* node) {
		Tel* elem = node->first;
		while (elem != NULL) {
			Operation(elem);
			elem = elem->next;
		}

	}

};
class Lexer {
private:
	int curr_pos = 0;
	string curr_str = "";
	friend class Parser;
public:
	Lexer(int curr_pos = 0, string curr_str = "") : curr_pos(curr_pos), curr_str(curr_str) {}
	bool CheckLetter(char ichar) {
		if ((ichar >= 'a' && ichar <= 'z') || (ichar >= 'A' && ichar <= 'Z') || ichar == '_')
			return true;
		return false;
	}
	bool CheckDigit(char ichar) {
		if ((ichar >= '0' && ichar <= '9'))
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
			while (curr_pos < curr_str.length() &&
				(CheckDigitLetter(curr_str[curr_pos]) ||
					(curr_str[curr_pos] == '.' && curr_pos != curr_str.length())
					)) {
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
				(temp_sign == "*") && (curr_str[curr_pos + 1] == '=') ||
				(temp_sign == ":") && (curr_str[curr_pos + 1] == '=')
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
			result->Add(ReadWord(), TokenType[3]);
			std::string digit = ReadDigit();
			if (digit.find(".") == true)
				result->Add(digit, TokenType[2]);
			else if (digit != "")
				result->Add(digit, TokenType[1]);
			ReadTabs();
			result->Add(ReadSign(), TokenType[4]);
		}
		return result;
	}
	void Print(Tel* el, string elem) {
		Tel* iel = el;
		while (iel != NULL) {
			std::cout << elem << iel->text << " - " << iel->token_type << endl;
			if (iel->first != NULL)
				Print(iel->first, elem + "    ");
			iel = iel->next;
		}
	}
	void ParamInFunc(Tel* iel, char ichar) {
		Tel* next_elem_first = iel->first;
		while (next_elem_first != NULL) {
			Tel* next_elem_second = next_elem_first->first;
			while (next_elem_second != NULL) {
				if (next_elem_second->token_type == TokenType[1])
					if ((next_elem_second->next != NULL) && (next_elem_second->next->text[0] == ichar))
						next_elem_second->Add(next_elem_second->next);
				next_elem_second = next_elem_second->first;
			}
			next_elem_first = next_elem_first->next;

		}
	}
	//void SignIn(Tel* iel) {
	//	Tel* tmp = iel;
	//	SignIn_(tmp);
	//}
	void SignInFirst(Tel* iel) {
		Tel* elem = iel->first;
		while (elem != NULL) {
			if (elem->next != NULL && elem->pre != NULL && ((elem->text == "^") || (elem->text == "%") || (elem->text == "*") || (elem->text == "/"))) {
				elem->Add(elem->pre);
				elem->Add(elem->next);
			}
			if (elem->first != NULL) SignInFirst(elem);
			elem = elem->next;
		}
	}
	void SignInSecond(Tel* iel) {
		Tel* elem = iel->first;
		while (elem != NULL) {
			if (elem->next != NULL && elem->pre != NULL && ((elem->text == "+") || (elem->text == "-"))) {
				elem->Add(elem->pre);
				elem->Add(elem->next);
			}
			if (elem->first != NULL) SignInSecond(elem);
			elem = elem->next;
		}
	}
	void AssignmentIn(Tel* iel) {
		Tel* elem = iel->first;
		while (elem != NULL) {
			if (elem->next != NULL && elem->pre != NULL && (elem->text == ":=")) {
				elem->Add(elem->pre);
				elem->Add(elem->next);
			}
			if (elem->first != NULL) AssignmentIn(elem);
			elem = elem->next;
		}
	}
};

int main() {
	STR prog = "print( 1 + 2 * 3)";
	Lexer lexer;
	Tel* pro = lexer.ReadWordTel(prog);
	pro->Brackets('[', ']');
	pro->Brackets('(', ')');
	pro->Brackets('{', '}');
	lexer.ParamInFunc(pro, '(');
	lexer.ParamInFunc(pro, '{');
	lexer.SignInFirst(pro);
	lexer.SignInSecond(pro);
	lexer.AssignmentIn(pro);
	Parser parser;
	parser.Print(pro);
	/*lexer.Print(pro, " ");*/
}