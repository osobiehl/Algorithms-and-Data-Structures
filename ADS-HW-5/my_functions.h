//
// Created by Jose Ignacio Biehl on 03.03.20.
//

#ifndef FIBONACCI_MY_FUNCTIONS_H
#define FIBONACCI_MY_FUNCTIONS_H
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <numeric>

class Storage{
public:
	Storage(){
		ptr_time = new std::vector<long double>;
		ptr_fib = new std::vector<unsigned long long int>;
		index = 0;
	}
	int index;
	std::vector<long double>* ptr_time;
	std::vector<unsigned long long int>* ptr_fib;
	~Storage(){
		delete ptr_time;
		delete ptr_fib;
	}
};

void write_to_file(std::ofstream& out, Storage& container){
	long double time = container.ptr_time->back();
	//std::cout<<"fib number->"<<container.index<<"\n";
	//std::cout<<"value in vector ->"<<container.ptr_fib->back()<<"\n";
	long double fib = container.ptr_fib->back();
	out<<container.index<<" "<<time<<" "<<fib<<std::endl;

}


using namespace std;
#endif //FIBONACCI_MY_FUNCTIONS_H
