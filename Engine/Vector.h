#pragma once
namespace Engine {
	template <typename T>
	class Node
	{
	public:
		Node(const T & val) { _val = val; }
		~Node() { delete _val; }
		Node<T> * & next() { return _next; }
		T & val() { return _val; }
	private:
		T _val;
		Node<T> * _next;
	};

	template <typename T>
	class Vector
	{
	public:
		Vector();
		~Vector();
		void push(const T & val);
		void pop();
		void clear();
		T & operator[](const unsigned int index);
		bool removeAt(const unsigned int index);
	private:
		Node<T> * head;
		Node<T> * tail;
	};

}
