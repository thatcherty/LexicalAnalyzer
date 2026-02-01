#include "Tokens.h"

int main()
{
	string code = "int calculate() {\n"
		" int count = 0, value = 10;\n"
		" for (; value > count;) {\n"
		" count += 2; /* Increment count by 2 */\n"
		" }\n"
		" return count;\n"
		"}\n";
	
	Tokens text{};

	text.tokenize(code);

	return 0;
}