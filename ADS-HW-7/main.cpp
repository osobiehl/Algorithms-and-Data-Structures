#include <iostream>
#include "Algorithms.h"
#include <array>
using namespace std;




int main() {
	int problem1[] =  {9, 1, 6, 7, 6, 2, 1};
	CountingSort(problem1, 9, 7 );

	print_arr(problem1, 7);
	//wrapper class for array cuz we java now
	std::array<double, 7> problem2 = {0.9, 0.1, 0.6, 0.7, 0.6, 0.3, 0.1};
	BucketSort<double, std::array<double, problem2.size() >::iterator> (problem2.begin(), problem2.end());
	for (auto i : problem2){
		cout<<i<<endl;
	}
	cout<<endl;

	std::array<double, 10> thing = {39, 0, 0.01, 22, 34, 19,100,2, 0.5, 0.9};
	BucketSort<double, std::array<double, problem2.size() >::iterator> (thing.begin(), thing.end());
	for (auto i : thing)
		cout<<i<<endl;

//	std::array<int, 7> problem1dot5 =  {'!', '2', '3', '4', 'c', 'C', 'd'};
//	KeyIteratorCountingSort<int, std::array<int, problem1dot5.size()>::iterator>(problem1dot5.begin(), problem1dot5.end(), 109);
//	for (auto i : problem1dot5)
//		cout<<i<<endl;
//

	std::vector<string> problem4 = {"word", "category", "cat", "new", "news", "world", "bear", "at", "work", "time"};

	cout<<endl;
	Radix_String<vector<string>::iterator>(problem4.begin(), problem4.end());
	for (auto i : problem4)
		cout<<i<<endl;

	std::vector<int> problem7dot2a = {99, 120,1,33,400,203,110};
	
	OGRadix(problem7dot2a);
	for (auto i : problem7dot2a)
		cout<<i<<endl;

	return 0;
}
