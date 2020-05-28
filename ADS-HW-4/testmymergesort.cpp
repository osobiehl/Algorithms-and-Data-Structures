
#include "my_algorithms.cpp"
#include <ctime>
#include "my_functions.h"

void worst_Case(int n, int k, ofstream& out, Storage& container) {
	int worst_case[n];
	int mid = n / 2;
	for (int i = 0; i < n; i++) {
		worst_case[i] = n-i;
	}
	//cout<<"printing array before: "<<std::endl; print<int>(worst_case, 0, n);
	auto start = chrono::high_resolution_clock::now();
	MyMergeSort<int>(worst_case, 0, n - 1, k);
	auto stop = chrono::high_resolution_clock::now();
	//cout<<"printing array after : \n"<<std::endl; print<int>(worst_case, 0, n);
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << k << " " << duration.count() << endl;

}
void best_Case(int n, int k, ofstream& out, Storage& container) {
	int best_case[n];
	for (int i = 0; i < n; i++) {
		best_case[i] = i;
	}
	auto start = chrono::high_resolution_clock::now();
	MyMergeSort<int>(best_case, 0, n - 1, k);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << k << " " << duration.count() << endl;

}

void average_Case(int n, int k, ofstream& out, Storage& container){

	int avg_case[n];
	srand(time(NULL));
	for (int i = 0; i < n; i++)
		avg_case[i] = rand();
	auto start = chrono::high_resolution_clock::now();
	MyMergeSort<int>(avg_case, 0, n - 1, k);
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
	container.ptr->push_back(duration.count());
	out << k << " " << duration.count() << endl;

}

int main(){

	long unsigned int repetitions;
	cout << "enter the number of repetitions to be done for each case: ";
	cin >> repetitions;

	long unsigned int n, intervals, start_value, stop_value;
	string bestres, worstres, avgres;
	bestres ="results_best";
	worstres="results_worst";
	avgres = "results_average";

	ofstream out_best[repetitions], out_worst[repetitions], out_average[repetitions];
	cout << "enter n: ";
	cin >> n;
	cout<<"enter starting value for k: ";
	cin>>start_value;

	cout<<"enter stop value: WARNING, stop value might not be included in calculations: ";
	cin>>stop_value;

	cout << " enter increasing integer interval for k: ";
	cin >> intervals;
	if (intervals < 1)
		throw runtime_error("you want to watch the world burn");

	Storage container_avg[n/intervals+1], container_bst[n/intervals+1], container_worst[n/intervals+1];
	for (int i = 0; start_value + i*intervals <= stop_value; i++){
		int increase_interval = i*intervals + start_value;
		container_bst[i].index = increase_interval;
		container_avg[i].index = increase_interval;
		container_worst[i].index = increase_interval;

	}
	for (int j = 0; j < repetitions; j++) {

		out_best[j].open(bestres + to_string(j) + ".txt");
		out_worst[j].open(worstres + to_string(j) + ".txt");
		out_average[j].open(avgres + to_string(j) + ".txt");


		for (int i = 0; start_value + i*intervals <= stop_value; i++) {
			int increase_interval = i*intervals;
			best_Case(n, start_value + increase_interval, out_best[j], container_bst[i]);
			worst_Case(n, start_value + increase_interval, out_worst[j], container_worst[i]);
			average_Case(n, start_value + increase_interval,out_average[j], container_avg[i]);
		}
	}

	ofstream final_results_avg; final_results_avg.open("final_results_avg.txt");
	ofstream final_results_worst; final_results_worst.open("final_results_worst.txt");
	ofstream final_results_bst; final_results_bst.open("final_results_bst.txt");

	for (int i = 0;  start_value + i*intervals <= stop_value; i++){
		write_to_file(final_results_avg, container_avg[i]);
		write_to_file(final_results_bst, container_bst[i]);
		write_to_file(final_results_worst, container_worst[i]);
	}
	//reference frame
	cout<<"running an average case comparison to normal mergesort with the same amount of repetitions"<<endl;
	Storage merge_store;
	merge_store.index = n;
	for  (int i =0; i < repetitions; i++){
		int arr[n];
		srand(time(NULL));
		for(int j = 0; j < n; j++)
			arr[j] = rand();
		auto start = chrono::high_resolution_clock::now();
		NormalMergeSort<int>(arr, 0, n - 1);
		auto stop = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(stop - start);
		merge_store.ptr->push_back(duration.count());
	}
	ofstream out;
	out.open("mergesort_results.txt");
	out<<merge_store.index<<" "<<accumulate(merge_store.ptr->begin(),  merge_store.ptr->end(), 0) / (float) merge_store.ptr->size()<<endl;

	return 0;
}