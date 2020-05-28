//
// Created by Jose Ignacio Biehl on 11.02.20.
//

#include "Access.h"
void Access::activate(unsigned int code, unsigned int level){
	hashmap[code] = level;
}
void Access::deactivate(unsigned int code){
	hashmap[code] = 0;
}
bool Access::isactive(unsigned int code, unsigned int level) const{
	return hashmap[code] >= level;
}
Access::Access(int n){
	hashmap = new int[n];
	size = n;
}
int Access::getSize() const {return size;}
Access::~Access(){delete hashmap;}