#include "stdafx.h"
#include "CppUnitTest.h"
#include "../../HW1/HW1/Stack.h" 
#include "../../HW1/HW1/StackImpl.h"
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HW1_Test
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(base_empty)
		{
			Stack * s = new StackImpl();
			Assert::IsTrue(s->empty());
			delete s;
		}

		TEST_METHOD(base_push_pop_empty_size)
		{
			Stack * s = new StackImpl();
			for (int i=1; i<=5; i++)
				s->push(i);
			for (int i=5; i>=1; i--)
			{
				Assert::AreEqual(s->size(), static_cast<unsigned>(i));
				Assert::AreEqual(s->pop(), i);
			}
			Assert::IsTrue(s->empty());
			delete s;
		}

		TEST_METHOD(base_badpop)
		{
			Stack * s = new StackImpl();
			try
			{
				s->push(4);
				s->pop();
				s->pop();
				Assert::AreEqual(1, 2);
			}
			catch(const char * e)
			{
				Assert::AreEqual(e, "stack is empty");
			}
			
			delete s;
		}

		TEST_METHOD(copy_constr)
		{
			StackImpl *s = new StackImpl();
			s->push(1);
			s->push(2);
			s->push(3);
			s->push(4);

			Stack *s2 = new StackImpl(*s);
			s2->push(45);
			s->push(34);
			Assert::AreNotEqual(s->pop(), s2->pop());
			Assert::AreEqual(s->pop(), s2->pop());
			Assert::AreEqual(s->pop(), s2->pop());
			Assert::AreEqual(s->pop(), s2->pop()); 
			Assert::AreEqual(s->pop(), s2->pop());
			delete s;
			delete s2;
		}


		//don't work/ its normal
		TEST_METHOD(base_badpointer)
		{
			Stack * s = new StackImpl();
			Stack ** d = &s;
			s->push(4);
			s->push(34);
			s->~Stack();
			try
			{
				(*d)->size();
				Assert::AreEqual(1, 2);
			}
			catch(const char *e)
			{
				Assert::AreEqual(e, "stack is corrupted");
			}	
		}

		TEST_METHOD(base_top)
		{
			Stack * s = new StackImpl();
			s->push(1);
			s->push(2);
			Assert::AreEqual(s->top(), 2);
			Assert::AreEqual(s->size(), static_cast<unsigned>(2));
			Assert::AreEqual(s->pop(), 2);
			Assert::AreEqual(s->top(), 1);
			Assert::AreEqual(s->size(), static_cast<unsigned>(1));
			delete s;
		}


	};
}