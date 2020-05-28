#include <iostream>
#include <ctype.h>
#include <algorithm>
#include <fstream>
#define BIGINT (1<<25)
#define FOR(B, i) for (i = 0; i < B; i++)

template <class T>inline  T max(T& a, T& b){
	return (a > b ? a : b);
}
int find_meetup_city(int** adj_matrix, int n, int your_city, int friend_city){
		//brute force lmao
		int d[n][n];
		for(int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d[i][j] = adj_matrix[i][j];
			//	std::cout<<d[i][j]<<" ";
			}
			//std::cout<<std::endl;
		}

		//find shortest lengths between all vertices
		//Floyd-Warshall Algorithm
		for (int k = 0; k < n; k++) {
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < n; j++) {
					d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}

		int min_distance  = BIGINT;
		int res;
		for (int i = 0; i < n; i++){
			if (min_distance > max(d[your_city][i], d[friend_city][i])) {
				min_distance = max(d[your_city][i], d[friend_city][i]);
				res = i;
			}
		}

		return res;
}
int make_cities(std::istream& in){
	using namespace std;
	cout<<"enter number of cities n\n";
	int n;
	in>>n;
	cout<<"n is : "<<n<<endl;

	cout<<"enter your city: ";
	int c1, c2;
	in>>c1;
	cout<<"enter your friend's city: ";
	in>>c2;
	int** cities = new int*[n];
	cout<<"fill in adjacency matrix: -1 means there is no distance"<<endl;
	int i =0,j=0;
	FOR(n,i) {
		cities[i] = new int[n];
		cout<<"city: "<<i<<": ";
		FOR(n, j){
			in>>cities[i][j];
			if (cities[i][j] == -1)
				cities[i][j] = BIGINT;
			if (i == j)
				cities[i][j] = 0;
		}
	}
	int res = find_meetup_city(cities, n, c1, c2);
	FOR(n, i){
		delete[] cities[i];
	}
	return res;
}

int main() {
	using namespace std;
	cout<<"enter 1 for a file, 0 for terminal input";
	int in;
	cin>>in;
	int res;
	string fname;
	fstream file;

	switch(in){
		case (0):
			 res = make_cities(cin);
			break;
		case (1):

			cout<<"enter file name: ";
			cin>>fname;
			file.open(fname);
			if (!file)
				cout<<"error!";


			res = make_cities(file);
			break;
		default:
			cout<<"no.";
			exit(-1);
	}
	cout<<"now solving problem . . . answer is city: "<<res<<endl;


	return 0;
}
