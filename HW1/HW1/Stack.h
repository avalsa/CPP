#ifndef STACK
#define STACK

class Stack
{
public:
	virtual ~Stack() {}
	typedef int value_type;
	virtual void push(value_type const) = 0;
	virtual value_type pop() = 0;
	virtual value_type top() const = 0;
	virtual size_t size() const = 0;
	virtual bool empty() const = 0;
};

#endif