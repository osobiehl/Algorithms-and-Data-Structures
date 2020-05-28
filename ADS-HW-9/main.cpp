#include <iostream>
#include "RedBlackTree.cpp"


int main() {
	using namespace std;
	std::cout << "Hello, World!" << std::endl;
	RedBlackTreeGeneral<int> a;
	srand(0);
	for(int i = 0; i < 10; i++) {
		int r = i;
		a.insert(r);
		cout<<"inserting: "<<r<<endl;
	}
	a.print();
	//a.debug();
	cout<<"\n\n";

	a.printBackwards();
	auto ex = a.search(7);
	if (ex)
		cout<<"data of search is: "<<ex->data<<endl;
	a.remove(ex);
	cout<<"now deleting search . . . testing to see if it can be found again\n";
	ex = a.search(7);
	if (!ex)
		std::cout<<"element not found!\n";

	cout<<"now debugging tree, if no violations are printed out, then all is good\nblack height from root is: ";
	a.debug();
	cout<<"\nadding random numbers to tree: \n";
	for (int i = 0; i < 100; i++){
		a.insert(rand() % 1000);
	}
	cout<<"now printing the tree again\n";
	a.print();

	cout<<"now debugging tree, if no violations are printed out, then all is good\nblack height from root is: ";
	a.debug();

	return 0;
}
