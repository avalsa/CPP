#ifndef STIMP
#define STIMP

#include <cstdint>
#include <fstream>
#include "Stack.h"

#define ASSERT_OK() if (!ok()){ dump(); throw "stack is corrupted";}

const size_t POISON = INT32_MAX;
const uint8_t LIMIT_DUMP = 10;

class StackImpl : public Stack
{
public:

	StackImpl(): root(nullptr), size_(0) {}

	StackImpl(StackImpl &s1): root(nullptr), size_(s1.size_)
	{
		if (!s1.ok())
			throw "Object not created";
		if (s1.root == nullptr) 
			return;
		Node * cur_root = s1.root;
		Node * first = Node::new_Node(cur_root->data, nullptr);
		Node * prev = first;
		while ( (cur_root=cur_root->next) != nullptr)
		{
			Node * n = Node::new_Node(cur_root->data, nullptr);
			prev->next = n;
			prev = n;
		}
		root = first;
	}

	~StackImpl()
	{
		while (root != nullptr)
		{
			Node * v = root;
			root = root->next;
			delete v;
		}
		size_ = POISON;
	}

	void push(value_type const elem) override
	{
		ASSERT_OK();
		size_++;
		if (root == nullptr)
		{
			root = Node::new_Node(elem, nullptr);
		}
		else
		{
			Node * ne = Node::new_Node(elem, root);
			root = ne;
		}
		ASSERT_OK();
	}

	value_type pop() override
	{
		ASSERT_OK();
		if (size_ <= 0)
		{
			throw "stack is empty";
		}
		size_--;
		value_type val = root->data;
		Node * n = root;
		root = root->next;
		delete n;
		ASSERT_OK();
		return val;
	}

	value_type top() const override
	{
		ASSERT_OK();
		if (size_ <= 0)
		{
			throw "stack is empty";
		}
		ASSERT_OK();
		return root->data;
	}

	size_t size() const override
	{
		return size_;
	}

	bool empty() const override
	{
		return (size_) ? false : true;
	}

private:
	bool ok() const 
	{
		return (size_ != POISON) ? true : false;
	}

	void dump() const
	{
		std::ofstream out("dump.txt"); 
		out << "Dump of stackimpl "<<std::endl;
		out << "size = " << size_ << std::endl;
		out << "if size = " << POISON << "then stack is broken" << std::endl;
		Node * e = root;
		for (int i=0; i<LIMIT_DUMP; i++)
		{
			if (e == nullptr) break;
			out << "Stack[" << i << "]=" << e->data<<std::endl;
			e = e->next;
		}
		out.close();
	}


private:
	struct Node
	{
		value_type data;
		Node * next;

		static Node * new_Node(value_type val, Node * next)
		{
			Node * node = new Node;
			node->data = val;
			node->next = next;
			return node;
		}
	};

	Node * root;
	size_t size_;
};

#endif


