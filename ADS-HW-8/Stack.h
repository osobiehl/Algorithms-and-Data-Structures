//
// Created by Jose Ignacio Biehl on 24.03.20.
//
#include <iostream>
#ifndef STACKSANDQUEUES_STACK_H
#define STACKSANDQUEUES_STACK_H

template <class T> class StackQueue;
template <class T> class Stack {

private:
	struct StackNode { // linked list
		T data;
		std::shared_ptr<StackNode> next;
	};
	std::shared_ptr<StackNode> top; // top of stack
	int size; // -1 if not set, value otherwise
	int current_size; // unused if size = -1
public:

	void push(T x){
		if (current_size == size && size > 0){
			std::cout<<"stack overflow!\n";
			//throw std::logic_error("stack overflow!");
			return;
		}

		std::shared_ptr<StackNode> newel = std::make_shared<StackNode>();
		if (!newel)
			throw std::bad_alloc();
		newel->data = x;
		newel->next = top;
		top = newel;
		current_size++;
		//std::cout<<"inserting element "<<x<<" in stack!\n";
	}

	bool pop(T& out){
		if (current_size > 0) {
			if (top == nullptr){
				std::cout<<"null pointer! stack underflow!";
				return false;
			}
			out = top->data;
			std::shared_ptr<StackNode> next = top->next;
			current_size--;
			top = next;
			//std::cout<<"popping element "<< out << " from stack\n";

		}
		else{
			std::cout<<"stack underflow!\n";

			//throw std::logic_error("stack underflow!");
			return false;
		}
		return true;
	}

	bool isEmpty(){
		return current_size == 0;
	} // true if empty, false otherwise
	//Stack(int new_size)

	Stack(){
		size = -1;
		current_size = 0;
		top = nullptr;
	}
	Stack(int max){
		size = max;
		current_size = 0;
		top = nullptr;
	}

	friend class StackQueue<T>;

};



template <class T> class StackQueue{
private:
	Stack<T> exit;
	Stack<T> entrance;
	int current_size;
	int max_size;
public:
	StackQueue(){
		exit = Stack<T>();
		entrance = Stack<T>();

		current_size =0;
		max_size= -1;
	}

	StackQueue(int max){
		exit = Stack<T>(max);
		entrance = Stack<T>(max);
		current_size =0;
		max_size= max;
	}
	void enqueue(T& x){
		if(current_size < max_size || max_size < 0) {
			T trash;
			while (!entrance.isEmpty()){
				exit.push(entrance.top->data);
				entrance.pop(trash);
			}
			entrance.push(x);
			while(!exit.isEmpty()){
				entrance.push(exit.top->data);
				exit.pop(trash);
			}
			current_size++;
		}
		else{
			std::cout<<"queue overflow!\n";
		}
	}
	bool dequeue(T& out){
		if (!entrance.isEmpty()) {
			entrance.pop(out);
			current_size--;
			return true;

		}
		else{
			std::cout<<"queue underflow!\n";
			return false;
		}
	}
	bool isEmpty(){
		return current_size == 0;
	}


};
#endif //STACKSANDQUEUES_STACK_H
