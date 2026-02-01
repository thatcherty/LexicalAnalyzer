#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

class Tokens
{
public:
	void tokenize(string& code);
	Tokens();
private:
	unordered_map<string,string> token_list;

};

