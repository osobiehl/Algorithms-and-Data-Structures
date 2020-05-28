//
// Created by Jose Ignacio Biehl on 04.03.20.
//

#ifndef FIBONACCI_FIBONACCI_H
#define FIBONACCI_FIBONACCI_H

#include <iostream>
#include <cmath>



template <class T>
class Matrix2x2;

template <class T>
void print_matrix(const Matrix2x2<T>& a);
template <class T>
class Matrix2x2{
private:
	T** values;
public:
	inline T* operator[](int a) const{
		return values[a];
	}

	Matrix2x2(const T arr[2][2]){
		values = new T*[2];
		for (int i = 0; i < 2; i++)
			values[i] = new T[2];
		values[0][0] = arr[0][0];
		values[0][1] = arr[0][1];
		values[1][0] = arr[1][0];
		values[1][1] = arr[1][1];

	}
	Matrix2x2(const Matrix2x2& cpy){
		values = new T*[2];
		for (int i = 0; i < 2; i++)
			values[i] = new T[2];
		values[0][0] = cpy.values[0][0];
		values[0][1] = cpy.values[0][1];
		values[1][0] = cpy.values[1][0];
		values[1][1] = cpy.values[1][1];
	}

	Matrix2x2(T** A){
		values = A;
	}

	friend Matrix2x2 operator*(const Matrix2x2<T>& a, const Matrix2x2<T>& b) {
		/*cout<<"multiplying: \n";
		print_matrix(a);
		cout<<"and : \n";
		print_matrix(b);
		cout<<"\n";
		 */
		T **numbers = new T*[2];
		if (!numbers)
			throw std::bad_alloc();
		for (int i = 0; i < 2; i++) {
			numbers[i] = new T[2];
			if (!numbers[i]) throw std::bad_alloc();
		}
		T M1 = (a.values[0][0] + a.values[1][1]) * (b.values[0][0] + b.values[1][1]);
		T M2 = (a.values[1][0] + a.values[1][1]) * (b.values[0][0]);
		T M3 = a.values[0][0] * (b.values[0][1] - b.values[1][1]);
		T M4 = a.values[1][1] * (b.values[1][0] - b.values[0][0]);
		T M5 = (a.values[0][0] + a.values[0][1]) * b.values[1][1];
		T M6 = (a.values[1][0] - a.values[0][0]) * (b.values[0][0] + b.values[0][1]);
		T M7 = (a.values[0][1] - a.values[1][1]) * (b.values[1][0] + b.values[1][1]);

		numbers[0][0] = M1 + M4 - M5 + M7;
		numbers[0][1] = M3 + M5;
		numbers[1][0] = M2 + M4;
		numbers[1][1] = M1 - M2 + M3 + M6;
		Matrix2x2 res(numbers);


		return res;
	}
	Matrix2x2<T> operator^(const int& n){
		if (n == 0){
			T numbers[2][2];
			numbers[0][0] = 1;
			numbers[0][1] = 0;
			numbers[1] [0] = 0;
			numbers[1][1] = 1;
			Matrix2x2<T> res(numbers);
			return res;
		}
		if (n == 1)
			return *this;
		if (n % 2 == 0) {
			Matrix2x2<T> res(*this^(n/2));
			return res * res;
		}
		else {
			Matrix2x2<T> res((*this ^ ((n - 1) / 2)));
			return res * res * (*this);
		}
	}
	~Matrix2x2(){
		//cout<<"freeing:"<<endl; print_matrix(*this);
		delete [] values;
	}
};
template <class T>
void print_matrix(const Matrix2x2<T>& a){
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			std::cout << a[i][j] << " ";
		}
		std::cout<<std::endl;
	}
}

unsigned long long int naiveFibonacci(unsigned long long int n){
	if (n < 2)
		return n;
	else
		return naiveFibonacci(n-1) + naiveFibonacci(n-2);
}

unsigned long long int bottomUpFibonacci(long int n){
	unsigned long long int numbers[n];
	if( n < 2)
		return n;
	numbers[0] = 1;
	numbers[1] = 1;
	for (int i = 2; i < n; i++) {
		numbers[i] = numbers[i - 1] + numbers[i - 2];
		//cout << numbers[i] << endl;
	}
	return numbers[n-1];
}

unsigned long long int closedFormFibonacci(int n){
	long double phi =(long double) ( ( long double) (1  + sqrtl(5))) / (long double) 2;
	long double power = powl(phi, n);
	long double root = sqrtl((long double)5);
	long double res = power / root;
	unsigned long long int actual_res  = llround(res);
	return actual_res;
}

unsigned long long int matrixFibonacci(int n){
	unsigned long long int** fib = new unsigned long long int*[2];
	if (!fib)
		throw std::bad_alloc();
	fib[0] = new unsigned long long int[2];
	if (!fib[0])
		throw std::bad_alloc();
	fib[1] = new unsigned long long int[2];
	if (!fib[1]) throw std::bad_alloc();
	fib[0][0] = 1;
	fib[0][1] = 1;
	fib[1][0] = 1;
	fib[1][1] = 0;
	Matrix2x2<unsigned long long int> mat(fib);
	Matrix2x2<unsigned long long int> result(mat^n);
	unsigned long long int res = result[0][1];
	return  res;
}

#endif //FIBONACCI_FIBONACCI_H
