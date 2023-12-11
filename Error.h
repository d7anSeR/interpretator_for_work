//#pragma once
//#include<iostream>
//class Error {
//private:
//	std::string error_name = NULL;
//	std::string error_details = NULL;
//public:
//	Error(std::string error_name = NULL, std::string error_details = NULL) {
//		this->error_name = error_name;
//		this->error_details = error_details;
//	}
//	std::string GetResult() {
//		std::string result = error_name;
//		result += ": ";
//		result += error_details;
//		return result;
//	}
//};
//class IllegalCharError : public Error {
//private:
//	std::string detail_illegal = NULL;
//public:
//	IllegalCharError(std::string detail_illegal) {
//		this->detail_illegal = detail_illegal;
//	}
//};