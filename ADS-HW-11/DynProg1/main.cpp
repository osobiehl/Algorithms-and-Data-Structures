#include <iostream>
#include <memory>
#include <vector>
#include <stack>
#include <string>
/*
 *
 * Consider the array A = (a1, a2, ..., an). We call a subarray a succession of numbers in A where
the position of any value in the subarray in the array is always bigger than the value of the previous one.
 Use dynamic programming to find a subarray of maximal ordered length of the array
A. You can assume there are no duplicate values in the array. Your algorithm should find one
optimal solution if multiple exist.
 *
 *
 *
 */
void print(int* arr, int n){
	for (int i =0; i < n; i++){
		std::cout<<arr[i]<<" ";
	}
	std::cout<<"\n";
}
int findMax(int* arr, int n){
	int max = 0;
	for (int i = 1; i < n; i++){
		if (arr[max] < arr[i])
			max = i;
	}
//	std::cout<<"max position is: "<<max<<std::endl;
	return max;

}

using namespace std;

std::vector<int> longest_sub_array(int* arr, int n){
	vector<vector<int> > V(n);

	V[0].push_back(arr[0]);


	for (int i = 1; i < n; i++){

		for (int j = 0; j < i; j++){
			//constructs maximum sub-arrays and finds the global optimum optimum by trying
			//to add a new element i in each iteration. the second part of the
			//if statement ensures that we don't 'double dip' with the same subsequence
			if ((arr[i] > arr[j]) && V[i].size() < V[j].size() + 1)
				V[i] = V[j];
		}
		V[i].push_back(arr[i]);
	}


	vector<int> maxSubArray = V[0];

	//find the resulting largest sub-array and return it
	for (vector<int> v : V)
		if (v.size() > maxSubArray.size())
			maxSubArray = v;

	return maxSubArray;

}

int main() {
	char in[150];

	fgets(in, 149, stdin);
	int count = 1;
	for(int i = 0; i < 150; i++){
		if (in[i] == '\n')
			in[i] = ' ';
	}

	auto token = strtok(in, " ");
	string temp[70];

		temp[0] = token;

	int j = 1;
	while (1) {
		token = strtok(NULL, " ");
		if (token == NULL)
			break;
		temp[j] = token;

		count++;
		j++;
	}

	int fina_fuckin_lly[count];
	for(int i = 0; i < count; i++){
		fina_fuckin_lly[i] = stoi(temp[i]);
	}
	// print(fina_fuckin_lly, count);

	auto end = longest_sub_array(fina_fuckin_lly, count);
	for (auto it = end.begin(); it != end.end(); it++)
		cout<<*it<<" ";
	return 0;
}
