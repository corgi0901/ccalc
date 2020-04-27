#ifndef _VALUE_HPP_
#define _VALUE_HPP_

#include <string>

typedef enum {
	INTEGER = 0,
	DECIMAL,
} VALUE_TYPE;

typedef union {
	long integer;
	double decimal;
} VALUE;

class Value
{
public:
	VALUE_TYPE type;
	VALUE value;

	Value(long value);
	Value(double value);
	Value(std::string value);

	Value operator+(Value obj);
	Value operator-(Value obj);
	Value operator*(Value obj);
	Value operator/(Value obj);

	std::string toString(void);
};

#endif /* _VALUE_HPP_ */