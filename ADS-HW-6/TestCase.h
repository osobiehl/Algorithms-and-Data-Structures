//
// Created by Jose Ignacio Biehl on 14.03.20.
//

#ifndef HEAPSORT_TESTCASE_H
#define HEAPSORT_TESTCASE_H


#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>

class Storage{
public:
	Storage(){
		ptr = new std::vector<int>;
		index = 0;
	}
	int index;
	std::vector<int>* ptr;
	~Storage(){
		delete ptr;
	}
};

void write_to_file(std::ofstream& out, Storage& container){
	float average = accumulate(container.ptr->begin(), container.ptr->end(), 0) / (float)container.ptr->size();
	out<<container.index<<" "<<average<<std::endl;
}

void TestSubRoutine(void (*fct) (int*, int) ){
	using namespace std;
	std::cout<<"enter the number of repetitions to be done\n";
	int rep;
	std::cin>>rep;
	std::cout<<"enter the file name root to identify the test runs\n";
	std::string root_name;
	cin>>root_name;
	std::ofstream files[rep];
	cout<<"enter the max n of the array to be sorted\n";
	int n, start, interval;
	cin>>n;
	cout<<"enter the starting value for n\n";
	cin>>start;
	cout<<"enter the increasing intervals for n: ";
	cin>>interval;
	// initializes storage container
	Storage container[n/interval + 1];
	for (int i =0; start + i*interval <= n; i++) {
		container[i].index = start + i*interval;
	}

	for (int k = 0; k< rep; k++){
		files[k].open(root_name + to_string(k) + ".txt");

		//iterate through each n for each file
		for (int i = 0; start + i* interval <= n; i ++) {
			int increment = start + i*interval;

			srand(time(NULL));
			int arr[increment];
			for (int j = 0; j < increment; j++)
				arr[j] = rand() % 100;
			auto start  = chrono::high_resolution_clock::now();
			fct(arr, increment);
			auto stop = chrono::high_resolution_clock::now();
			auto duration = chrono::duration_cast<chrono::microseconds>(stop- start).count();

			files[k] << increment << " " << duration << endl;
			container[i].ptr->push_back(duration);
		}
	}
	ofstream results;
	results.open( root_name + "_FINAL.txt");

	for (int i =0; start + i*interval <= n; i++) {
		write_to_file(results, container[i]);
	}

}


#endif //HEAPSORT_TESTCASE_H
