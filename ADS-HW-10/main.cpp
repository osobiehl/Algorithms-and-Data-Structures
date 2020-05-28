#include <iostream>
#include <memory>

#include "HashTable.h"


int main() {
	using namespace std;
	HashTable t(20);
	int arr[20];
	cout<< (t.isEmpty() ? "empty\n" : "not empty\n");
	srand(2);
	for (int i = 0; i < 20; i++){
		//hopefully this makes the chance of getting duplicate keys absurdly small
		arr[i] = rand() % 1000000;
		t.insertNode(arr[i], i);
	}
	for (int i = 0; i < 20; i++){
		cout<<"using key: " << arr[i] <<" value obtained: "<< t.get(arr[i]) << endl;
	}

	cout<< (t.isEmpty() ? "empty\n" : "not empty\n");
	return 0;
}
