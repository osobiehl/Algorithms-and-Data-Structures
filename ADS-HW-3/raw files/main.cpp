#include "SelectionSort.cpp"
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>
//VIEW AS VECTOR CONTAINING A VALUE AND ANOTHER VECTOR

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

using namespace std;
void best_Case(int n, ofstream& out, Storage& container){
	int best_case[n];

	for (int i =0; i < n; i++)
		best_case[i] = i;
	auto start = chrono::high_resolution_clock::now();
	SelectionSort(best_case, n);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << n << " " << duration.count() << endl;
	//cout<< n << " " << duration.count() << endl;

}
void worst_Case(int n, ofstream& out, Storage& container){
	int worst_case[n];
	worst_case[0] = n;
	for (int i = 1; i < n; i++)
		worst_case[i] = i;
	auto start = chrono::high_resolution_clock::now();
	SelectionSort(worst_case, n);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << n << " " << duration.count() << endl;
	//cout<< n << " " << duration.count() << endl;

}
void average_Case(int n, ofstream& out, Storage& container){
	srand(time(NULL));
	int average_case[n];
	for(int i =0; i < n; i++){
		average_case[i] = rand();
	}
	auto start = chrono::high_resolution_clock::now();
	SelectionSort(average_case, n);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << n << " " << duration.count() << endl;
	//cout<< n << " " << duration.count() << endl;
	//for (auto i: average_case) cout<< i<<endl;



}

int main() {

	long unsigned int repetitions;
	cout << "enter the number of repetitions to be done for each case: ";
	cin >> repetitions;

	long unsigned int n, intervals;
	string bestres, worstres, avgres;
	bestres ="results_best";
	worstres="results_worst";
	avgres = "results_average";

	ofstream out_best[repetitions], out_worst[repetitions], out_average[repetitions];
	cout << "enter n: ";
	cin >> n;
	cout << " enter increasing integer interval for n: ";
	cin >> intervals;

	Storage container_avg[n/intervals+1], container_bst[n/intervals+1], container_worst[n/intervals+1];



	for (int j = 0; j < repetitions; j++) {

		out_best[j].open(bestres + to_string(j) +".txt");
		out_worst[j].open(worstres + to_string(j)+".txt");
		out_average[j].open(avgres + to_string(j)+".txt");


		for (int i = 0; i < n/intervals+1; i++) {
			int increase_interval = i*intervals;
			container_bst[i].index = increase_interval;
			container_avg[i].index = increase_interval;
			container_worst[i].index = increase_interval;

			best_Case(increase_interval, out_best[j], container_bst[i]);
			worst_Case(increase_interval, out_worst[j], container_worst[i]);
			average_Case(increase_interval, out_average[j], container_avg[i]);
		}

	}

	ofstream final_results_avg; final_results_avg.open("final_results_avg.txt");
	ofstream final_results_worst; final_results_worst.open("final_results_worst.txt");
	ofstream final_results_bst; final_results_bst.open("final_results_bst.txt");

	float sum_avg=0, sum_bst=0, sum_worst=0;

	for (int i = 0; i < n/intervals+1; i++){
		write_to_file(final_results_avg, container_avg[i]);
		write_to_file(final_results_bst, container_bst[i]);
		write_to_file(final_results_worst, container_worst[i]);
	}

}
