#include <iostream>
#include <deque>
/*
Write a program which does the following using a deque object:
1. Create a deque A able to store float values.
2. Read floats from the keyboard until the entered float value is 0.
3. Insert the positive elements at the end of A and the negative elements at the beginning of A.
4. Print the elements of A on the standard output separated by spaces.
5. Print an empty line on the standard output.
6. Add the value 0 into the middle of the deque (between the last negative and before the first
positive element).
7. Print the elements of A on the standard output separated by semicolons. Make sure that
you do not print a semicolon after the last element.
You can assume that the input will be valid.
 */


using namespace std;
template <class T>
void print(deque<T>& inp, const char* separator){
	typename deque<T>::iterator it;
	for(it = inp.begin(); it != inp.end(); it++){
		cout<<*it<<(it+1 == inp.end() ?  "": separator);
	}
	cout<<endl;
}

int main() {
	deque<float> A;
	float inp;
	while (1){
		cin>>inp;
		if (inp ==0)
			break;
		if (inp > 0)
			A.push_back(inp);
		else
			A.push_front(inp);
	}
	print(A, " ");

	deque<float>::iterator it = A.begin();
	for (it; *it < 0 && it != A.end(); it++);
	A.insert(it, 0);
	print<float>(A, "; ");
	return 0;
}
