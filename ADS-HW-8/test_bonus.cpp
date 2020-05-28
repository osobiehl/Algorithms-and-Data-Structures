//
// Created by Jose Ignacio Biehl on 30.03.20.
//
#include "LinkedLists.h"
using namespace std;
int main(){
	LinkedList<int> bonus;
	for (int i = 0; i < 10; i++) {
		int r = rand() % 10;
		bonus.insertStart(r);
		cout<<"inserting element "<<r<<endl;
	}
	cout<<"bonus problem now\n\n";
	RedBlackTreeGeneral<int> bonustree(bonus);
	bonustree.print();
	return 0;
}