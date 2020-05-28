#include <iostream>
#include "Stack.h"
#include "LinkedLists.h"
#include <ctime>
int main() {
int trash;
using namespace std;
	Stack<int> test2(4);
	test2.push(5);
	test2.push(4);
	test2.push(3);
	test2.push(2);
	test2.push(1);
	test2.push(0);
	for (int i = 0; i < 7; i++)
		test2.pop(trash);

	StackQueue<int> test3;
	for (int i = 0; i < 10; i++)
		test3.enqueue(i);
	for (int i = 0; i < 10; i++) {
		if(test3.dequeue(trash))
			cout << trash << endl;
	}
	cout<<"\n\n\n\n";
	StackQueue<int> test4(5);
	for (int i = 0; i < 10; i++)
		test4.enqueue(i);
	cout<<"\n\n\n\n\n";
	for (int i = 0; i < 5; i++) {
		if( test4.dequeue(trash) )
			cout<<trash<<endl;
	}

	LinkedList<int> bonus;
	for (int i = 0; i < 10; i++)
		bonus.insertStart(rand() % 10);


	cout<<"\n\n\n\n\n\n";
	BST<int> tree;
	srand(1);
	for (int i = 0; i < 10; i++){
		int r = rand() % 10;
		cout<<"random element: "<<r<<endl;
		tree.insert(r);
	}
	tree.print();


	cout<<"now making a list using the binary tree\n";
	LinkedList<int> BST_TO_LL(tree);
	BST_TO_LL.print();

	cout<<"bonus problem now\n\n";
	RedBlackTreeGeneral<int> bonustree(bonus);
	bonustree.print();
	return 0;
}
