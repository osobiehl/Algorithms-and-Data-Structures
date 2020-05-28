//
// Created by Jose Ignacio Biehl on 17.03.20.
//

#ifndef COUNTINGSORT_ALGORITHMS_H
#define COUNTINGSORT_ALGORITHMS_H
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include <cmath>

template <class T, class Iterator> void InsertionSort(Iterator start, Iterator end){
	Iterator cursor;
	T key;
	for (Iterator outerloop = start+1; outerloop < end; outerloop++){
		key = *outerloop;
		cursor = outerloop - 1;

		// shift the elements ofthe sub-array if they are greater than key
		while (cursor != start && *cursor > key){
			*(cursor + 1) = *cursor;
			cursor = cursor - 1;
		}
		// decouple this so non-random access iterators can also do this
		if (cursor == start && *cursor > key){
			*(cursor + 1) = *cursor;
			*cursor = key;
		}
		else
		*(cursor + 1) = key;//insert element where it belongs in sub-array
	}
}

	template<class T>
	void print_arr(T *arr, int size) {
		using namespace std;
		for (int i = 0; i < size; i++)
			cout << arr[i] << endl;
		cout << endl;
	}

	/// @param takes an array of type int, a range (from zero to highest number), and size of array
	void CountingSort(int *arr, int range, int size) {
		using namespace std;

		if (size == 1)
			return;
		int final_arr[size];

		int aux_array[range + 1];
		//set all values to zero
		for (int i = 0; i < range + 1; i++) {
			aux_array[i] = 0;
		}

		//if our count of the number found in the auxiliary array is increased by 1
		for (int i = 0; i < size; i++) {

			aux_array[arr[i]] += 1;
		}
		//print_arr(aux_array, range + 1);
		cout << "\n\n";
		for (int i = 1; i <= range; i++) {
			aux_array[i] += aux_array[i - 1];
		}

		for (int i = size - 1; i >= 0; --i) {
			final_arr[aux_array[arr[i]] - 1] = arr[i];
			aux_array[arr[i]] -= 1;
		}
		for (int i = 0; i < size; i++)
			arr[i] = final_arr[i];
	}
	/**
	 * @brief uses bucketsort on a positive valued container using 2 bidirectional iterators.
	 * @tparam T :class, don't be dumb and use something that can't have floating point numbers.
	 * @tparam Iterator : BIDIRECTIONAL ITERATOR of Class T
	 * @param begin :beginning of the iterator
	 * @param end :end of the iterator
	 */

	template <class T, class Iterator> void BucketSort(Iterator begin, Iterator end){
		using namespace std;
		int size = 0;
		T largest = *begin;
		for (Iterator i = begin+1; i != end; i++) {
			size++;
			if (*i > largest)
				largest = *i;
		}
		//divides the numbers to make them from 0 to 1
		if (largest > 1) {
			for (Iterator i = begin; i != end; i++) {
				*i /= largest;
			}
		} else
			largest = 1;
		/*the total number of buckets is of size [size], our "partitions" go up to size,
		 * since all of the values are normalized up to 1
		 */

		typename std::vector<T> vector_arr[size+1];
		for (auto i = begin; i != end; i++){
			int vector_arr_index = *i * size;
			vector_arr[vector_arr_index].push_back(*i);
		}
		for (int i =0; i < size; i++){
			InsertionSort<T, typename std::vector<T>::iterator>(vector_arr[i].begin(), vector_arr[i].end());
		}


		for (int i = 0; i < size; i++){
			for(int j = 0; j < vector_arr[i].size(); j++) {
				*begin = vector_arr[i][j] * largest;
				begin++;
			}
		}
		//last case: being inclusive of the one because why not :)
		for (T elem : vector_arr[size]) {
			*begin = elem * largest;
			begin++;
		}

	}

template <class T, class Iterator> void IteratorCountingSort(Iterator begin, Iterator end, int range, int exp) {
	using namespace std;
	int size  = std::distance(begin, end);
	T final_arr[size];

	T aux_array[range + 1];
	//set all values to zero
	for (int i = 0; i < range + 1; i++) {
		aux_array[i] = 0;
	}

	//if our count of the number found in the auxiliary array is increased by 1
	for (Iterator i = begin; i != end; i++) {
		aux_array[*i] += 1;
	}
	//print_arr<T>(aux_array, range + 1);
	cout << "\n\n";
	for (int i = 1; i <= range; i++) {
		aux_array[i] += aux_array[i - 1];
	}

	for (Iterator i = end - 1; i != begin; --i) {
		final_arr[aux_array[*i] - 1] = *i;
		aux_array[*i] -= 1;
	}
	final_arr[aux_array[*begin]-1] = *begin;
	aux_array[*begin] -= 1;


	for (int i = 0; i < size; i++, begin++) {
		*begin = final_arr[i];
	}
}

//STANDARD CLASS FOR POSITION EVALUATION
/// @brief StdClass standard comparison class for key based generic counting sortq
template <class T, class Iterator> class StdClass{

public:
	StdClass(){};
	inline T operator () (Iterator iterator){
		return *iterator;
	}
};

template <class Iterator> class StringClass{
private:
	int index;
public:
	StringClass(int i) : index (i) {};
	inline int operator() (Iterator iterator){
		if ((*iterator).size() < index)
			return 0;
		return (*iterator)[index];
	}
};
/**
 *
 * @tparam T class used
 * @tparam Iterator of any container of the same class
 * @tparam Key , comparison key, standard one is stdKey, you can implement your own if you want
 * @param begin , start of iterator
 * @param end  , end of iterator
 * @param range , range of iterator
 * @param key  , pass functor
 */
template <class T, class Iterator, class Key = StdClass<T, Iterator> > void KeyIteratorCountingSort(Iterator begin, Iterator end, int range, Key key = Key() ) {
	using namespace std;
	int size  = std::distance(begin, end);
	T final_arr[size];

	int aux_array[range + 1];
	//set all values to zero
	for (int i = 0; i < range + 1; i++) {
		aux_array[i] = 0;
	}

	//if our count of the number found in the auxiliary array is increased by 1
	for (Iterator i = begin; i != end; i++) {
		aux_array[key(i)] += 1;
	}
	//print_arr<T>(aux_array, range + 1);
	for (int i = 1; i <= range; i++) {
		aux_array[i] += aux_array[i - 1];
	}

	for (Iterator i = end - 1; i != begin; --i) {
		final_arr[aux_array[key(i)] - 1] = *i;
		aux_array[key(i)] -= 1;
	}
	final_arr[aux_array[key(begin)]-1] = *begin;
	aux_array[key(begin)] -= 1;


	for (int i = 0; i < size; i++, begin++) {
		*begin = final_arr[i];
	}
}
/**
 *
 * @tparam Iterator class
 * @param begin of container
 * @param end of container
 */
	template <class Iterator> void Radix_String(Iterator begin, Iterator end) {
	using namespace std;
	int k = (*begin).size();
	int radix  = 128;
	for (Iterator i = begin + 1; i != end; i++) {
		if ((*i).size() > k)
			k = (*i).size();
	}
	for (int i = k-1 ; i >= 0; i--) {
		KeyIteratorCountingSort<std::string, Iterator, StringClass<Iterator> >(begin, end, radix,
																			   StringClass<Iterator>(i));

	}
}
//same as string class, but offsets by 48 to only get digits from 1 to 10
/// @brief functor class for radixSort on strings
template <class Iterator> class StringClassNumeric{
private:
	int index;
public:
	StringClassNumeric(int i) : index (i) {};
	inline int operator() (Iterator iterator){
		return (*iterator)[index] - 48 ;
	}
};



	/**
	 * @brief Most Significant digit recursive "bucket-like" sort
	 * @param arr vector of int
	 * @param exponent
	 */


void GhettoBucketSort(std::vector<int>& arr, int exponent, std::vector<int>& out){
	using namespace std;
	if (exponent == 0){
		return;
	}
	vector<int> b[10];
	for (int i = 0; i < arr.size(); i++){
		int b_index = (arr[i] / exponent) % 10;
		b[b_index].push_back(arr[i]);
	}
	for (int i = 0; i < 10; i++){
		if (b[i].size() > 1)
			GhettoBucketSort(b[i], exponent / 10, out);
	}
//PUSHES EXACTLY N sorted elements to the out vector
	arr.clear();
	for (int i = 0; i < 10; i++){
		for (int j = 0; j < b[i].size(); j++){
			out.push_back(b[i][j]);
		}
	}
}
/**
 *
 * @param arr array to be sorted
 */
void OGRadix(std::vector<int>& arr){
		using namespace std;
		int radix  = 10;

		std::vector<int> iterate_thing;
		int greatest = arr[0];
		iterate_thing.push_back(arr[0]);
		for (auto i = arr.begin() +1; i != arr.end(); i++) {
			if (*i > greatest)
				greatest = *i;
			iterate_thing.push_back(*i);

		}
		int exp = (log10(greatest));
		int exponential =  pow(10, exp);
		//cout<<"exponential is: "<<exponential<<endl;
		arr.clear();
		GhettoBucketSort(iterate_thing, exponential, arr);
	}

#endif //COUNTINGSORT_ALGORITHMS_H
