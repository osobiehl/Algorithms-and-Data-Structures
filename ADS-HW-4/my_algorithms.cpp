#include <iostream>
//selection sort
template<class T> void SelectionSort(T* arr, int start, int max);
//implementation of mergesort
template<class T> void merge(T* arr, int left, int middle, int right);
//swaps two elements
template<class T>int swap (T& A, T&B);
//prints an array
template <class T> void print(T* arr, int size);
template <class T> void print(T* arr, int min, int max);
//implements InsertionSort
template <class T> void InsertionSort(T* arr, int start, int end);

//implements mergesort

template <class T> void MyMergeSort(T* arr, int left, int right, int k){

	if (right - left > k-1){
		int middle = (left+right)/2;
		MyMergeSort<T>(arr, left, middle, k);
		MyMergeSort<T>(arr, middle + 1, right, k);


		merge<T>(arr, left, middle, right);

	}
	else {
		InsertionSort<T>(arr, left, right+1);
	}
}


template<class T> void merge(T* arr, int left, int middle, int right) {
	int i, j, k;
	int arr_left_size = middle - left + 1;
	int arr_right_size = right - middle;
	T arr_l[arr_left_size], arr_r[arr_right_size];
	for (i = 0; i < arr_left_size; i++)
		arr_l[i] = arr[left + i];
	for (j = 0; j < arr_right_size; j++)
		arr_r[j] = arr[middle + 1 + j];
	i = 0;
	j = 0;
	k = left;
	while (i < arr_left_size && j < arr_right_size) {
		if (arr_l[i] < arr_r[j]) {
			arr[k] = arr_l[i];
			i++;
		} else {
			arr[k] = arr_r[j];
			j++;
		}
		k++;
	}
	while (i < arr_left_size) {
		arr[k++] = arr_l[i++];

	}
	while (j < arr_right_size) {
		arr[k++] = arr_r[j++];
	}

}
template <class T> void NormalMergeSort(T* arr, int left, int right){

	if (right > left ){
		int middle = (left+right)/2;
		NormalMergeSort<T>(arr, left, middle);
		NormalMergeSort<T>(arr, middle + 1, right);
		//std::cout<<"merging the following two arrays:"; print<T>(arr, left, middle);
		//std::cout<<"arr2: "; print<T>(arr, middle+1, right);

		merge<T>(arr, left, middle, right);

	}
}

template <class T> void InsertionSort(T* arr, int start, int end){
	int outerloop, cursor;
	T key;
	for (outerloop = start+1; outerloop < end; outerloop++)
	{
		key = arr[outerloop];
		cursor = outerloop - 1;

		// shift the elements ofthe sub-array if they are greater than key
		while (cursor >= start && arr[cursor] > key)
		{
			arr[cursor + 1] = arr[cursor];
			cursor = cursor - 1;
		}
		//insert element where it belongs in sub-array
		arr[cursor + 1] = key;
	}
}

template<class T>int swap (T& A, T&B){

	T temp = A;
	A = B;
	B = temp;
	return 1;

}
template<class T> void SelectionSort(T* arr, int start, int max){
	if (max == 0)
		return;


	int comparison_index;
	int numswaps = 0;
	for (int outer_loop =start; outer_loop < max-1; outer_loop++){
		comparison_index = outer_loop;
		for (int right_hand_searcher = outer_loop+1; right_hand_searcher < max; right_hand_searcher++){
			//if the comparison of our current min/max is less/more than our current min/max,
			//it becomes our new comparison index
			// I had a functor here but it more than doubled running time so we use normal > comp...
			if ( arr[comparison_index] > arr[right_hand_searcher])
				comparison_index = right_hand_searcher;
		}
		if (arr[comparison_index] != arr[outer_loop] )
			numswaps += swap<T>(arr[outer_loop], arr[comparison_index]);
		// print<T>(arr, start, max);
	}
	//std::cout<<"number of swaps for array: "<<numswaps<<std::endl;


}

template <class T> void print(T* arr, int size){
	for (int i =0; i < size; i++)
		std::cout<<arr[i]<<std::endl;
	std::cout<<std::endl;
}
template <class T> void print(T* arr, int min, int max){
	for (int i =min; i < max; i++)
		std::cout<<arr[i]<<std::endl;
}