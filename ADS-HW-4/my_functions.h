//
// Created by Jose Ignacio Biehl on 25.02.20.
//

#ifndef MYMERGESORT_MY_FUNCTIONS_H
#define MYMERGESORT_MY_FUNCTIONS_H

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


using namespace std;




#endif //MYMERGESORT_MY_FUNCTIONS_H
