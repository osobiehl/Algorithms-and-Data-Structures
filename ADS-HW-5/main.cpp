#include <iostream>
#include <chrono>
#include <thread>
#include "FIbonacci.h"
#include <future>
#include "my_functions.h"
#define SET_TIME 1000
#define CONTAINER_SIZE 30


#include <fstream>
using namespace std;

//deprecated, don't use
template <class INPUT>
bool testFibonacci(unsigned long long int (*func)(INPUT), Storage& container){
	future<unsigned long long int> ftr = async(*func, container.index);
	auto start = chrono::high_resolution_clock::now();
	double time_taken;
//wait_for can return
	while ( ftr.wait_for(chrono::seconds(0)) != future_status::ready && time_taken < SET_TIME*1000){
		//cout<<"time taken is: "<<time_taken<<endl;
		time_taken = chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now() - start).count();
	}
	if (time_taken >= SET_TIME){
		cout<<"took too long! waiting to exit thread, hopefully this doesn't take too long\n";
		ftr.get();
		return 0;
	}
	else{
		long double final_time = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start).count();
		unsigned long long int res = ftr.get();
		//cout<<"result is: "<<res<<endl;
		container.ptr_fib->push_back(res);
		cout<<"time taken is "<<final_time<<endl;
		container.ptr_time->push_back(final_time);
		return true;
	}





}
template <class INPUT>
void test_case(ofstream& out, Storage* container, int storage_size, unsigned long long (*func)(INPUT), int max){
	int i;
	int cont;
	double duration = 0;
	for ( i = 0, cont = 1; i < storage_size && duration < max*1000; i++){
		auto start = chrono::high_resolution_clock::now();
		unsigned long long int res = func(container[i].index);
		auto stop = chrono::high_resolution_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
		if (duration < max*1000) {
			container[i].ptr_fib->push_back(res);
			cout<<"time taken is "<<duration<<endl;
			container[i].ptr_time->push_back(duration);
			write_to_file(out, container[i]);
		}
		else
			cout<<"took too long!\n";
	}
}
void initialize_Storage(Storage* container, int size){
	if (size < 5)
		throw range_error("value must be bigger than 5");
	int j = 0, k=0;
	for (int i = 0; i < 5; i++) {
		container[i].index = i+1;
	}
	for (int i = 5, j = 5 , k = 1; i <size; i++) {
		if (i % 6 == 0)
			k++;
		j+= k;
		container[i].index = j;


	}
	for (int i =0; i < size; i++){
		//cout<<container[i].index<<endl;
	}

}
int main() {
	Storage container_naive[CONTAINER_SIZE], container_matrix[CONTAINER_SIZE], container_closedform[CONTAINER_SIZE], container_bottomup[CONTAINER_SIZE];

	initialize_Storage(container_naive, CONTAINER_SIZE); initialize_Storage(container_closedform, CONTAINER_SIZE);
	initialize_Storage(container_matrix, CONTAINER_SIZE); initialize_Storage(container_bottomup, CONTAINER_SIZE);

	float duration;
	cout<<"enter the maximum number of seconds to wait for a computation: ";
	cin>>duration;


	ofstream naive, matrix, bottomup, closedform;
	naive.open("naive_fib.txt");
	matrix.open("matrix_fib.txt");
	bottomup.open("bottomup_fib.txt");
	closedform.open("closedform_fib.txt");

	test_case(naive, container_naive, CONTAINER_SIZE, naiveFibonacci, duration*1000*1000);
	test_case(matrix, container_matrix, CONTAINER_SIZE, matrixFibonacci, duration*1000*1000);
	test_case(bottomup, container_bottomup, CONTAINER_SIZE, bottomUpFibonacci,duration*1000*1000);
	test_case(closedform, container_closedform, CONTAINER_SIZE, closedFormFibonacci,duration*1000*1000);
	cout<<matrixFibonacci(90);

}
