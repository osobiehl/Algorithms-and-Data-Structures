#include <iostream>
#include <algorithm>
#include "TestCase.h"


using namespace std;
template <class T>  void Max_Heapify(T* arr, const int i, const int size);


inline int left(const int i){
	return (i<<1) +1;
}
inline int right(const int i) {
	return (i<<1) + 2;
}
inline int parent(const int i){
	return (i-1)>>1;
}
//shamelessly inspired by wikipedia's bottom down heapsort,
// puts the old root in the correct position
template <class T>void FixHeap(T* arr, int pos, int size){
	int navigator = pos;

	while (arr[0] > arr[navigator]){
		navigator = parent(navigator);
	}
	T temp = arr[navigator];
	arr[navigator] = arr[0];

	while (navigator > 0){
		swap(temp, arr[parent(navigator)]);
		navigator = parent(navigator);

	}
}

//quickly sinks the topmost element to the bottom, then returns position of sunk element.

template <class T> int FastSink(T* arr, int size){
	int current = 0;
	int l = left(current);
	int r = right(current);

	while (l < size && r < size){
		if (arr[l] > arr[r]) {
			current = l;
		}
		else{
			current = r;
		}
		l = left(current);
		r = right(current);
	}
	//corner case: r is not part of heap but l is
	if (l < size) {
		current = l;
	}
	return current;


}



template <class T>
void Build_Max_Heap(T* arr, const int size) {
	for (int i = (size-1) / 2; i >= 0; i--)
		Max_Heapify(arr, i, size);
}
template <class T> void Max_Heapify(T* arr, const int i, const int size){
	int l = left(i);
	int r = right(i);
	int largest;
	if (l < size && arr[l] > arr[i])
		largest = l;
	else
		largest = i;
	if (r < size && arr[r] > arr[largest])
		largest = r;
	if (largest != i){
		T temp;
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		Max_Heapify<T>(arr, largest, size);
 	}
}
template<class T>
void HeapSort(T* arr, int size){
	Build_Max_Heap<T>(arr, size);
	for (int i = size-1; i > 0; i--) {
		T temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		//cout<<"i is: "<<i<<" value taken from max is: "<<arr[i]<<endl;
		Max_Heapify<T>(arr, 0, i);
	}
}

template <class T> void NewHeapSort(T* arr, int size){
	Build_Max_Heap<T>(arr, size);
	for ( int i = size-1; i > 0; i--){
		T temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
		int pos = FastSink(arr, i);
		FixHeap(arr, pos, i-1);
	}
}


template <class T> void print(T* arr, int size){
	for (int i = 0; i < size; i++)
		std::cout<<arr[i]<<std::endl;
}


/// @author The wonderful people at wikipedia :)
template <class T> void heapsort_bu( T * data, int n ) // zu sortierendes Feld und seine Länge
{
	int val, parent, child;
	int root= n >> 1;                  // erstes Blatt im Baum
	int count= 0;                      // Zähler für Anzahl der Vergleiche

	for ( ; ; )
	{
		if ( root ) {                    // Teil 1: Konstruktion des Heaps
			parent= --root;
			val= data[root];               // zu versickernder Wert
		}
		else
		if ( --n ) {                     // Teil 2: eigentliche Sortierung
			val= data[n];                  // zu versickernder Wert vom Heap-Ende
			data[n]= data[0];              // Spitze des Heaps hinter den Heap in
			parent= 0;                     //   den sortierten Bereich verschieben
		}
		else                             // Heap ist leer; Sortierung beendet
			break;

		while ( (child= (parent + 1) << 1) < n )  // zweites (!) Kind;
		{                                         // Abbruch am Ende des Heaps
			if ( ++count, data[child-1] > data[child] )  // größeres Kind wählen
				--child;

			data[parent]= data[child];     // größeres Kind nach oben rücken
			parent= child;                 // in der Ebene darunter weitersuchen
		}

		if ( child == n )                // ein einzelnes Kind am Heap-Ende
		{                                //   ist übersprungen worden
			if ( ++count, data[--child] >= val ) {  // größer als der zu versick-
				data[parent]= data[child];   //   ernde Wert, also noch nach oben
				data[child]= val;            // versickerten Wert eintragen
				continue;
			}

			child = parent;                 // 1 Ebene nach oben zurück
		}
		else
		{
			if ( ++count, data[parent] >= val ) {  // das Blatt ist größer als der
				data[parent]= val;           //   zu versickernde Wert, der damit
				continue;                    //   direkt eingetragen werden kann
			}

			child= (parent - 1) >> 1;      // 2 Ebenen nach oben zurück
		}

		while ( child != root )          // maximal zum Ausgangspunkt zurück
		{
			parent= (child - 1) >> 1;      // den Vergleichswert haben wir bereits
			//   nach oben verschoben
			if ( ++count, data[parent] >= val )  // größer als der zu versickernde
				break;                             //   Wert, also Position gefunden

			data[child]= data[parent];     // Rückverschiebung nötig
			child= parent;                 // 1 Ebene nach oben zurück
		}

		data[child]= val;                // versickerten Wert eintragen
	}

	return;
}







int main() {
	int choice;
	cout<<"enter number for heapsort algorithm to be tested: 1 is standard\n 2 is my implementation of bottom up\n 3 is wikipedia's implementation of bottom up: ";
	cin>>choice;
	switch (choice){
		case (1):
			TestSubRoutine(HeapSort<int>);
			break;
		case (2):
			TestSubRoutine(NewHeapSort<int>);
			break;
		case (3):
			TestSubRoutine(heapsort_bu<int>);
		default:
			cout<<"wrong choice fool";
			break;
	}


	return 0;
}
