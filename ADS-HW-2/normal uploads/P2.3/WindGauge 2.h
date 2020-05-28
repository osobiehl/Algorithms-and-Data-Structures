//
// Created by Jose Ignacio Biehl on 11.02.20.
//
#include <iostream>
#include <list>

#ifndef P2_3_WINDGAUGE_H
#define P2_3_WINDGAUGE_H
class WindGauge {
public:
	WindGauge(int period = 12);
	void currentWindSpeed(int speed);
	int highest() const;
	int lowest() const;
	int average() const;
	~WindGauge();
	void dump() const;
private:
	std::list<int>* history;
	int size;

// add properties and/or method(s) here
};

#endif //P2_3_WINDGAUGE_H
