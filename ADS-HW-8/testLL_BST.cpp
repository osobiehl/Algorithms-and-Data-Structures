//
// Created by Jose Ignacio Biehl on 30.03.20.
//
#include "LinkedLists.h"


using namespace std;
int main(){

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

	return 0;
}
