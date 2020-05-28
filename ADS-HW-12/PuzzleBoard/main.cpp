

#include <iostream>
#include "PuzzleBoard.h"
#include <fstream>

int main() {
	using namespace std;
	int mode;
	cout<<"enter 0 for random board; 1 to enter board, 2 for a file ";
	cin>>mode;
	int** fields = nullptr;
	int bsize;
	if (mode == 1 || mode == 0) {
		cout << "enter board size: ";
		cin >> bsize;
	}
	bool b;

	if (mode == 1){
		cout<<"enter value for each tile \n";
		fields = new int*[bsize];
		for(int i = 0; i < bsize; i++){
			fields[i] = new int[bsize];
			for (int j = 0; j < bsize; j++){
				cin>>fields[i][j];
			}
		}
		b = true;
	}
	if (mode == 2){
		cout<<"enter file name: "; string n;
		cin>>n;
		ifstream file;
		file.open(n);
		file>>bsize;
		fields = new int*[bsize];
		for(int i = 0; i < bsize; i++){
			fields[i] = new int[bsize];
			for (int j = 0; j < bsize; j++){
				file>>fields[i][j];
			}
		}
		b = true;
	}


	PuzzleBoard test(bsize, fields);
	cout<<"printing board . . .\n";
	cout<<test<<endl;

	std::cout<<" answer is:  "<<endl;
	int steps = test.solve();
	cout<<"number of steps is "<<steps<<endl;
	if (b)
		for(int i = 0; i <bsize; i++)
			delete[] fields[i];

	return 0;
}
