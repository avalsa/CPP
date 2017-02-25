#include <cstdlib>
#include <iostream>

#include "Stack.h"
#include "StackImpl.h"
int main()
{
	Stack *s = new StackImpl();
	s->push(30);
	s->push(23);
	Stack * e = s;
	std::cout << s;
	free(s);
	try {
		e->pop();
	}
	catch(std::bad_exception * m)
	{
		std::cout << "sd";
	}
	catch(const char * s)
	{
		std::cout << "sd";
	}
	
	system("pause");
	delete s;
	return  0;
}
