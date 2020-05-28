#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main() {
	vector<int> test;
	for (int i =1; i <=30; i++)
		test.push_back(i);
	test.push_back(5);
	reverse(test.begin(), test.end());

	for (vector<int>::iterator it =test.begin(); it != test.end(); it++)
		cout<<*it<<endl;
	replace(test.begin(), test.end(), 5, 129);
	cout<<endl;
	for (auto it = test.begin(); it != test.end(); it++)
		cout<<*it<<endl;



	return 0;
}
