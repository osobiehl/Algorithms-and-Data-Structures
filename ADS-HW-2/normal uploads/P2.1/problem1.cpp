#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
using namespace std;

//list iterators don't have + operators so this is ugly as hell
template<class T>
void print(std::list<T>&  input, std::ostream& out, char separator) {
	typename list<T>::iterator it;
	int count =0;
	int s = input.size();
	for (it = input.begin(); it != input.end(); it++) {
		out << *it;
		if (count < s -1)
			out<<separator;
		count++;
	}
	cout<<endl;
}

int main() {
	list<int> A, B;
	int inp;
	while (1){
		cin>>inp;
		if (inp <=0)
			break;
		B.push_front(inp);
		A.push_back(inp);
	}
	list<int>::iterator it;
	ofstream out;
	out.open("listB.txt");

	print<int>(B, out, ' ');

	print<int>(A, cout, ' ');
	cout<<endl;

	int elemA = A.front();
	int elemB = B.front();
	A.pop_front(); B.pop_front();
	A.push_back(elemA);
	B.push_back(elemB);
	print<int>(A, cout, ',');
	print<int>(B, cout, ',');
	B.merge(A);
	print<int>(B, cout, ' ');


}
/*1. Create two lists (A and B).
2. Read integers from the keyboard until the entered integer is negative or zero.
3. Insert the positive integers into list A by adding to the end.
4. Insert the same positive integers into list B by adding to the beginning.
5. Print list A (separated by spaces) on the standard output and print list B (separated by
spaces) into a file called “listB.txt”.
6. Print an empty line on the standard output.
7. Move the first element of the lists to the end (for both lists).
8. Print list A, print list B on the standard output (both separated by comma) using an iterator.
Make sure that you do not print a comma after the last element.
9. Print an empty line on the standard output.
10. Merge list B into list A.
11. Print the result of the merging as a sorted list on the standard output (separated by spaces).*/