#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> split(string str, string delimiter) {
	vector<string> ret;
	int pos = str.find(delimiter);
	while (pos != string::npos) {
		pos = str.find(delimiter);
		ret.push_back( str.substr(0, pos) );
		str.erase(0, pos + delimiter.length());
	}
	return ret;
}

string join(vector<string>splitted, string delimiter) {
	string ret = "";
	for (unsigned int i = 0; i < splitted.size(); i++) {
		if (i != splitted.size() - 1)
			ret += splitted.at(i) + delimiter;
		else
			ret += splitted.at(i);
	}
	return ret;
}

void replace(string &str, string from, string to) {
	vector<string> splitted = split(str, from);
	str = join(splitted, to);
}

bool isLower(char ch) {
	return ((int)ch >= 97 && (int)ch <= 122) ? true : false;
}

bool isUpper(char ch) {
	return ((int)ch >= 65 && (int)ch <= 90) ? true : false;
}

bool isASCIIDigit(char ch) {
	return ((int)ch >= 48 && (int)ch <= 57) ? true : false;
}

bool isASCIILetter(char ch) {
	return (isUpper(ch) || isLower(ch)) ? true : false;
}

string upper(string str) {
	for (unsigned int i = 0; i < str.length(); i++)
		if (isLower(str[i]))
			str[i] -= 32;
	return str;
}

string lower(string str) {
	for (unsigned int i = 0; i < str.length(); i++)
		if (isUpper(str[i]))
			str[i] += 32;
	return str;
}

string title(string str) {
	if (str.length()) {
		str[0] = (isLower(str[0])) ? str[0]-32: str[0];
	}
	return str;
};

string reverseStr(string str) {
	string ret = "";
	for (int i = str.length() - 1; i >= 0; i--)
		ret += str[i];
	return ret;
}

string lstrip(string str, string to_strip) {
	int pos = str.find(to_strip);
	while(pos != string::npos) {
		pos = str.find(to_strip);
		if (pos != 0) break;
		str.erase(0, to_strip.length());
	}
	return str;
}

string rstrip(string str, string to_strip) {
	return reverseStr(
		lstrip(
			reverseStr(str),
			reverseStr(to_strip)
	));
}

string strip(string str, string to_strip) {
	return lstrip(rstrip(str, to_strip), to_strip);
}

bool startswith(string str, string start) {
	return (str.find(start) == 0) ? true:false ;
}

int main(int argc, char* argv[]) {

	return 0;
}