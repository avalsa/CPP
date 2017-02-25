#ifndef STACK
#define STACK

class Stack
{
public:
	Stack() :size_(0) {}
	virtual ~Stack() {}
	typedef int value_type;
	virtual void push(value_type const) = 0;
	virtual value_type pop() = 0;
	virtual value_type top() const = 0;
	

	size_t size() const
	{
		return size_;
	}

	

	bool empty() const
	{
		return size_ ? false : true;
	}

protected:
	size_t size_;
private:
	virtual bool ok() const = 0;
	virtual void dump() const = 0;
};

#endif


