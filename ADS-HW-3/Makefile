CC = g++
CFLAGS = -std=c++11 -I. -Wall -o

Default: trace tests

trace: testSelectionSort_TRACE.cpp SelectionSort.cpp
	$(CC) $(CFLAGS) trace_example testSelectionSort_TRACE.cpp SelectionSort.cpp

tests : testSelectionSort.cpp SelectionSort.cpp
	$(CC) $(CFLAGS) algorithm_testing testSelectionSort.cpp SelectionSort.cpp