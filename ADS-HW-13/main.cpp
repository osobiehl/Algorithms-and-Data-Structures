#include <iostream>
#include "Horses.h"

//
// Created by Jose Ignacio Biehl on 10.05.20.
//
#include <iostream>






int main() {
	std::cout << "Hello, World!" << std::endl;
	std::cout<<"enter size of chessboard: be careful because this will print all of the solutions so don't go too crazy: "; int n;
	std::cin>>n;
	HorseBoard a (n);
	a.solve();

}
/*
previous version

	bool solve_recursive(int remaining, int counter_pos, std::vector<int>& sol_vec){
		using namespace std;
		std::cout<<"counter is: "<<counter_pos<<"remaining is: "<< remaining<<std::endl;
		if (remaining == 0) { // check if we have considered all columns
			print();
			return true;
		}
		if (counter_pos >= boardSize)
			return false;

		for (int i = counter_pos; i < boardSize; i++){
			if (isSafe(i, counter_pos)) {
				table[i][counter_pos] = 1;
				sol_vec.push_back((i*boardSize + counter_pos));
				if (solve_recursive(remaining -1, counter_pos+1, sol_vec))
					return true;					//return true if there is a
				table[i][counter_pos] = 0;
				sol_vec.pop_back();

			}
			if (counter_pos != i && isSafe(counter_pos, i)){
				table[counter_pos][i] = 1;
				sol_vec.push_back((counter_pos * boardSize)+ i);
				if (solve_recursive(remaining -1, counter_pos+1, sol_vec))
					return true;					//return true if there is a
				table[i][counter_pos] = 0;
				sol_vec.pop_back();

			}
			//backtrack, make this zero so other solutions don't consider it
		}
		return false;
	}
 */