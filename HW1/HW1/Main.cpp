#include <cstdlib>
#include <iostream>

#include "Stack.h"
#include "StackImpl.h"
int main()
{
	Stack *s = new StackImpl();
	s->push(30);
	s->push(23);
	std::cout << s->size();
	std::cout << s->empty();
	system("pause");
	delete s;
	return  0;
}
