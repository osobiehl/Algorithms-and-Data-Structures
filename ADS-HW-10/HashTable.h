//
// Created by Jose Ignacio Biehl on 20.04.20.
//

#ifndef HASHTABLES_HASHTABLE_H
#define HASHTABLES_HASHTABLE_H

#include <iostream>
class Node {
public:
	int key;
	int value;

	Node(int key, int value) : key(key), value(value){}
};
class HashTable {
private:


	Node ** arr;

	int maxSize;
	int currentSize;

public:


	HashTable(){
		currentSize = 0;
		maxSize = 10;
		arr = new Node*[10];
		std::cout<<"initializing default hash table: size is 10 by default \n";
	}

	HashTable(int m){
		currentSize = 0;
		maxSize = m;
		arr = new Node*[m];
	}

	inline int hashCode(int key){
		return key % maxSize;
	}
	void insertNode(int key, int value){
		int hash = hashCode(key);
		int start = hash;
		if (arr[hash] != nullptr ){
			hash = (hash +1)% maxSize;
			while (hash != start && arr[hash] != nullptr)
				hash = (hash +1)% maxSize;
			if (hash == start){
				std::cout<<"could not insert element in table!";
				return;
			}
		}
		arr[hash] = new Node(key, value);
		currentSize++;
	}
	int get(int key){
		int hash = hashCode(key);
		if (arr[hash] == nullptr){
			std::cout<<"key not found!\n";
			return -1;
		}
		if (arr[hash]->key != key){
			int start = hash;
			hash = (hash +1) % maxSize;
			while (arr[hash] != nullptr && arr[hash]->key != key && hash != start)
				hash = (hash + 1) % maxSize;
			if (hash == start|| arr[hash] == nullptr){
				std::cout<<"key not found!\n";
				return -1;
			}
		}
		return arr[hash]->value;
	}

	inline bool isEmpty(){
		return currentSize == 0;
	}
};


#endif //HASHTABLES_HASHTABLE_H
