#include <iomanip>
#include <iostream>
#include <string>

#include "ccalc.hpp"
#include "value.hpp"

using namespace std;

static bool hasLowPriorityOperator(string input, int *op_pos);
static bool hasHighPriorityOperator(string input, int *op_pos);
static string trim(string input);
static string unbracket(string input);
static Value eval(string input);

static bool hasLowPriorityOperator(string input, int *op_pos)
{
	char prev	 = '\0';
	int bkt_depth = 0;
	bool find	 = false;

	for (int i = 0; i < (int)input.size(); i++) {
		char ch = input[i];

		if (ch == '+' || ch == '-') {
			if (isdigit(prev) || prev == ')') {
				if (bkt_depth == 0) {
					*op_pos = i;
					find	= true;
				}
			}
		}

		if (ch == '(') {
			bkt_depth++;
		}

		if (ch == ')') {
			bkt_depth--;
		}

		if (ch != ' ' && ch != '\t') {
			prev = ch;
		}
	}

	return find;
};

static bool hasHighPriorityOperator(string input, int *op_pos)
{
	int bkt_depth = 0;
	bool find	 = false;

	for (int i = 0; i < (int)input.size(); i++) {
		char ch = input[i];

		if (ch == '*' || ch == '/') {
			if (bkt_depth == 0) {
				*op_pos = i;
				find	= true;
			}
		}

		if (ch == '(') {
			bkt_depth++;
		}
		else if (ch == ')') {
			bkt_depth--;
		}
	}

	return find;
};

static string trim(string input)
{
	int i, start, end;

	for (i = 0; i < (int)input.size(); i++) {
		char ch = input[i];
		if (ch != ' ' && ch != '\t') {
			start = i;
			break;
		}
	}

	for (; i < (int)input.size(); i++) {
		char ch = input[i];
		if (ch != ' ' && ch != '\t') {
			end = i;
		}
	}

	return input.substr(start, end - start + 1);
};

static string unbracket(string input)
{
	if (input[0] != '(') {
		return input;
	}

	int i;
	int bkt_depth = 0;

	for (i = 0; i < (int)input.size(); i++) {
		char ch = input[i];

		if (ch == '(') {
			bkt_depth++;
		}
		else if (ch == ')') {
			bkt_depth--;
		}

		if (bkt_depth == 0) {
			break;
		}
	}

	if (i == (int)input.size() - 1) {
		return input.substr(1, (int)input.size() - 2);
	}

	return input;
};

static Value eval(string input)
{
	int op_pos;
	int before, after;

	do {
		before = (int)input.size();
		input  = trim(input);
		input  = unbracket(input);
		after  = (int)input.size();
	} while (before != after);

	DPRINT(input);

	try {
		if (hasLowPriorityOperator(input, &op_pos)) {
			char op		 = input[op_pos];
			string lside = input.substr(0, op_pos);
			string rside = input.substr(op_pos + 1);

			if (op == '+') {
				return eval(lside) + eval(rside);
			}
			else if (op == '-') {
				return eval(lside) - eval(rside);
			}
		}

		if (hasHighPriorityOperator(input, &op_pos)) {
			char op		 = input[op_pos];
			string lside = input.substr(0, op_pos);
			string rside = input.substr(op_pos + 1);

			if (op == '*') {
				return eval(lside) * eval(rside);
			}
			else if (op == '/') {
				return eval(lside) / eval(rside);
			}
		}

		/* Operator is not exist */
		return Value(input);

	} catch (ErrorCode e) {
		throw e;
	}
};

int main(int argc, char *argv[])
{
	string input;

	if (1 < argc) {
		input = string(argv[1]);
		try {
			Value val = eval(input);
			cout << val.toString() << endl;
		} catch (ErrorCode e) {
			cout << "Err" << endl;
		}
		return 0;
	}

	while (1) {
		cout << "(ccalc): ";
		getline(cin, input);

		if (input.size() != 0) {
			if (input.compare("quit") == 0) {
				break;
			}
			try {
				Value val = eval(input);
				cout << val.toString() << endl;
			} catch (ErrorCode e) {
				cout << "Err" << endl;
			}
		}
	}

	return 0;
};