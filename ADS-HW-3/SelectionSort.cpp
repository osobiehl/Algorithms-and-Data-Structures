#include <iostream>

template<class T>int swap (T& A, T&B){

	T temp = A;
	A = B;
	B = temp;
	return 1;

}
template<class T> void SelectionSort(T* arr, int size){
	if (size == 0)
		return;


	int comparison_index;
	for (int outer_loop =0; outer_loop < size-1; outer_loop++){
		comparison_index = outer_loop;
		for (int right_hand_searcher = outer_loop+1; right_hand_searcher < size; right_hand_searcher++){
			//if the comparison of our current min/max is less/more than our current min/max,
			//it becomes our new comparison index
			// I had a functor here but it more than doubled running time so we use normal > comp...
			if ( arr[comparison_index] > arr[right_hand_searcher])
				comparison_index = right_hand_searcher;
		}
		if (arr[comparison_index] != arr[outer_loop] )
			swap<T>(arr[outer_loop], arr[comparison_index]);
	}
}

template <class T> void print_array_TRACE(const T* arr, const T& outer_loop, const int & size) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == outer_loop)
			std::cout << "*" << arr[i] << "   ";
		else
			std::cout << arr[i] << "    ";
	}
	std::cout<<std::endl;
}

template<class T> void SelectionSort_TRACE(T* arr, int size){
	if (size == 0)
		return;


	int comparison_index;
	for (int outer_loop =0; outer_loop < size-1; outer_loop++){
		comparison_index = outer_loop;
		for (int right_hand_searcher = outer_loop+1; right_hand_searcher < size; right_hand_searcher++){
			//if the comparison of our current min/max is less/more than our current min/max,
			//it becomes our new comparison index
			// I had a functor here but it more than doubled running time so we use normal > comp...
			if ( arr[comparison_index] > arr[right_hand_searcher])
				comparison_index = right_hand_searcher;
		}

		if (arr[comparison_index] != arr[outer_loop] )
			swap<T>(arr[outer_loop], arr[comparison_index]);
		print_array_TRACE(arr, arr[outer_loop], size);
	}
}
