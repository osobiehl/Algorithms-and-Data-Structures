//
// Created by Jose Ignacio Biehl on 11.02.20.
//

#include "Access.h"
//so, this is the shittiest "hash map" I can think of but here goes
Access::Access(int n){
	hashtable = new bool[n];
	size = n;
}
void Access::activate(unsigned int code) {
	hashtable[code] = true;
}

void Access::deactivate(unsigned int code) {
	hashtable[code] = false;
}
bool Access::isactive(unsigned int code) const {
	return hashtable[code];
}
Access::~Access(){
	delete hashtable;
};