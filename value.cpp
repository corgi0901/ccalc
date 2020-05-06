#include "value.hpp"

#include "ccalc.hpp"

using namespace std;

Value::Value(long value)
{
	this->type			= INTEGER;
	this->value.integer = value;
};

Value::Value(double value)
{
	this->type			= DECIMAL;
	this->value.decimal = value;
};

Value::Value(string value)
{
	if (value.empty()) {
		throw INVALID_INPUT;
	}

	int sign = 1;
	int i	 = 0;

	if (value[i] == '-') {
		sign = -1;
		i++;
	}
	else if (value[i] == '+') {
		sign = 1;
		i++;
	}

	if (value.find(".") == string::npos) {
		this->type = INTEGER;

		long num = 0;

		for (; i < (int)value.size(); i++) {
			char ch = value[i];
			if (false == isdigit(ch)) {
				throw INVALID_INPUT;
			}
			num = num * 10 + (ch - '0');
		}

		this->value.integer = sign * num;
	}
	else {
		this->type = DECIMAL;

		double ipart = 0;  // Integer part
		double dpart = 0;  // Decimal part

		for (; value[i] != '.'; i++) {
			char ch = value[i];
			if (false == isdigit(ch)) {
				throw INVALID_INPUT;
			}
			ipart = ipart * 10 + (ch - '0');
		}

		for (int j = (int)value.size() - 1; i < j; j--) {
			char ch = value[j];
			if (false == isdigit(ch)) {
				throw INVALID_INPUT;
			}
			dpart = (dpart + (ch - '0')) / 10;
		}

		this->value.decimal = sign * (ipart + dpart);
	}
};

Value Value::operator+(Value obj)
{
	if (this->type == INTEGER) {
		if (obj.type == INTEGER) {
			return Value(this->value.integer + obj.value.integer);
		}
		else {
			return Value(this->value.integer + obj.value.decimal);
		}
	}
	else {
		if (obj.type == INTEGER) {
			return Value(this->value.decimal + obj.value.integer);
		}
		else {
			return Value(this->value.decimal + obj.value.decimal);
		}
	}
};

Value Value::operator-(Value obj)
{
	if (this->type == INTEGER) {
		if (obj.type == INTEGER) {
			return Value(this->value.integer - obj.value.integer);
		}
		else {
			return Value(this->value.integer - obj.value.decimal);
		}
	}
	else {
		if (obj.type == INTEGER) {
			return Value(this->value.decimal - obj.value.integer);
		}
		else {
			return Value(this->value.decimal - obj.value.decimal);
		}
	}
};

Value Value::operator*(Value obj)
{
	if (this->type == INTEGER) {
		if (obj.type == INTEGER) {
			return Value(this->value.integer * obj.value.integer);
		}
		else {
			return Value(this->value.integer * obj.value.decimal);
		}
	}
	else {
		if (obj.type == INTEGER) {
			return Value(this->value.decimal * obj.value.integer);
		}
		else {
			return Value(this->value.decimal * obj.value.decimal);
		}
	}
};

Value Value::operator/(Value obj)
{
	if (obj.type == INTEGER && obj.value.integer == 0) {
		throw ZERO_DIVIDE;
	}

	if (obj.type == DECIMAL && obj.value.decimal == 0) {
		throw ZERO_DIVIDE;
	}

	if (this->type == INTEGER) {
		if (obj.type == INTEGER) {
			return Value(this->value.integer / obj.value.integer);
		}
		else {
			return Value(this->value.integer / obj.value.decimal);
		}
	}
	else {
		if (obj.type == INTEGER) {
			return Value(this->value.decimal / obj.value.integer);
		}
		else {
			return Value(this->value.decimal / obj.value.decimal);
		}
	}
};