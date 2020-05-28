#include <iostream>
#include <algorithm>
#include <vector>
/*
 * Consider a triangle formed from n lines (1 < n ≤ 100), each line containing natural numbers in
the interval [0, 10000].
(a) (5 points) Use dynamic programming to determine the biggest sum of numbers existent on
the path from the number in the first line and a number from the last line and print the
respective path to the output. Each number in this path is seated to the left or to the right
of the other value above it.
(b) (2 point) Analyze the runtime of your solution and compare it to the brute force approach.
(c) (1 point) Explain why a greedy algorithm does not work for this problem.
 */
using namespace std;
int trianglesum(int**arrs, int n){
	int arr[n][n];
	//copy array to auxiliary array;
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++ )
			arr[i][j] = arrs[i][j];
	}
	for (int i = n-2; i >= 0; i--){
		for (int j = 0; j <= 1; j++){
			arr[i][j] += (arr[i+1][j] >arr[i+1][j+1]? arr[i+1][j] : arr[i+1][j+1] );
		}
	}
	//top-down printing max
	int max = 0;
	cout<<arr[0][0]<<endl;
	//start from top: can only go left or right, choose largest sum
	for(int i = 0; i < n; i++){
		if (arr[i][max] < arr[i][max+1]){
			max++;
		}
		cout<<arrs[i][max]<<" ";
	} cout<<endl;


	return arr[0][0];


}

int main() {
	int n;
	cout<<"enter n: ";
	cin>>n;
	if (n <= 1 || n > 100)
		throw logic_error("reeeeee");

	int **arr = new int*[n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	for(int i = 0; i < n; i++){
		for (int j = 0; j <= i; j++){
			arr[i][j] = 0;
			if (arr[i][j] < 0 || arr[i][j] > 10000)
				throw logic_error("number too big! or too small");
		}
	}

	for(int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cin >> arr[i][j];
		}
	}
	/*for(int i =0; i < n; i++){
		for (int j = 0; j <= i; j++)
			cout<<arr[i][j]<<" ";
		cout<<endl;
	}*/
	trianglesum(arr, n);

	return 0;
}
