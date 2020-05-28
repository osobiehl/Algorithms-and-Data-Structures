//
// Created by Jose Ignacio Biehl on 11.02.20.
//
#include "WindGauge.h"
#include <iostream>
#include <list>

WindGauge::WindGauge(int period){
	history = new std::list<int>;
	size = period;

}
void WindGauge::currentWindSpeed(int speed){
	if (history->size() == size)
		history->pop_front();
	history->push_back(speed);

}
//self explanatory
int WindGauge::highest() const{
	int hi = *history->begin();
	for (auto const & el : *history ){
		if (el > hi)
			hi = el;
	}
	return hi;
}
int WindGauge::lowest() const{
	int lo = *history->begin();
	for (auto const & el : *history ){
		if (el < lo)
			lo = el;
	}
	return lo;
}
//look ma a comment
int WindGauge::average() const{
	if (size ==0) {
		std::cout << "math error!" << std::endl;
		return -1;
	}
	int sum = 0;
	//uses foreach loop to go through history list
	for (auto const & el: *history){
		sum += el;
	}
	return sum / history->size();
}
void WindGauge::dump() const{
	std::cout<<"lowest: "<<lowest()<<std::endl;
	std::cout<<"highest: "<<highest()<<std::endl;
	std::cout<<"average: "<<average()<<std::endl;
}
//deleting allocated memory
WindGauge::~WindGauge(){
	delete history;
}


