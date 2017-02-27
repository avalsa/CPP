#include <cstdlib>
#include <iostream>

#include "Stack.h"
#include "StackImpl.h"
int main()
{
	StackImpl *s = new StackImpl();
	s->push(1);
	s->push(2);
	s->push(3);
	s->push(4);

	Stack *s2 = new StackImpl(*s);
	s2->push(45);
	s->push(34);
	std::cout<<s->pop()<<"\n";
	std::cout << s->pop() << "\n";
	std::cout << s->pop() << "\n";
	std::cout << s->pop() << "\n";

	std::cout << s2->pop() << "\n";
	std::cout << s2->pop() << "\n";
	std::cout << s2->pop() << "\n";
	std::cout << s2->pop() << "\n";

	system("pause");
	delete s;
	return  0;
}
