#include <vector>

#ifndef KNIGHTS_HORSES_H
#define KNIGHTS_HORSES_H
class HorseBoard{
private:
	bool** table;
	int boardSize;
	int n;

public:
	HorseBoard(int n){
		boardSize = n;
		table = new bool*[n];

		for (int i = 0; i < boardSize; i++){
			table[i] = new bool[n];
			for (int j = 0; j < boardSize; j++)
				table[i][j] = false;
		}
		this->n= n;
	}
	//1 1 1 1 1 1 1 1

	std::vector<int> adjacent(int r,int c){
		//case down
		std::vector<int> res;
		int METADATA;
		if (r - 1 >= 0){
			//consider right up and left up
			if (c + 2 < boardSize)
				res.push_back((r-1) * boardSize + c + 2);
			if (c -2 >= 0)
				res.push_back((r- 1) * boardSize + c - 2);
		}
		if (r + 1 < boardSize){
			//consider right up and left up
			if (c + 2 < boardSize)
				res.push_back((r+1) * boardSize + c + 2);
			if (c -2 >= 0)
				res.push_back((r+ 1) * boardSize + c - 2);
		}

		if ( c + 1 < boardSize){
			if (r -2 >= 0)
				res.push_back((r-2) * boardSize + c + 1);
			if (r +2 < boardSize)
				res.push_back((r+2) * boardSize + c + 1);
		}
		if (c -1 >= 0 ){
			if (r -2 >= 0)
				res.push_back((r-2) * boardSize + c - 1);
			if (r +2 < boardSize)
				res.push_back((r+2) * boardSize + c - 1);
		}
		return res;
	}
	bool isSafe(int r, int c){
		auto v = adjacent(r, c);
		for (auto& i : v){
			//std::cout<<"considering adjacency of: ("<<r<<", "<<c<<") to: ("<<i/boardSize<<", "<<i % boardSize<<")\n";
			if (isOccupied(i / boardSize, i % boardSize ))
				return false;
		}
		return true;
	}

	inline bool isOccupied(int r, int c){
		return (table[r][c]);
	}
	void print(){
		for (int i = 0; i < boardSize; i++){
			for (int j = 0; j < boardSize; j++)
				std::cout<<table[i][j]<<" ";
			std::cout<<"\n";
		}
		std::cout<<'\n';

	}
	void solve(){
		if (n == 2) {
			std::cout << "there is no solution !\n";
			return;
		}

		std::vector<int> out;
		solve_recursive(n, 0, out);


	}
	/**
	 *
	 * @param remaining the remaining number of knights to place
	 * @param counter_pos row and column along the diagonal we are inspecting
	 * @param sol_vec a solution vector TODO implement
	 * @return returns true if there is a solution
	 */



	void solve_recursive(int remaining, int counter_pos, std::vector<int>& sol_vec){
		using namespace std;
		//std::cout<<"counter is: "<<counter_pos<<"remaining is: "<< remaining<<std::endl;
		if (remaining == 0) { // check if we have considered all columns
			print();
			return;
		}
		if (counter_pos >= boardSize)
			return;

		for (int i = 0; i < boardSize; i++){
			if (isSafe(i, counter_pos) && !table[i][counter_pos]) {
				table[i][counter_pos] = 1;
				//sol_vec.push_back((i*boardSize + counter_pos));
				(solve_recursive(remaining -1, counter_pos+1, sol_vec));
				table[i][counter_pos] = 0;
				//sol_vec.pop_back();
			}
			if (isSafe(counter_pos, i && !table[counter_pos][i])) {
				table[counter_pos][i] = 1;
				//sol_vec.push_back((i*boardSize + counter_pos));
				(solve_recursive(remaining -1, counter_pos+1, sol_vec));
				table[counter_pos][i] = 0;
				//sol_vec.pop_back();
			}

		}
		return;
	}

	~HorseBoard(){
		for (int i = 0; i < boardSize; i++)
			delete[] table[i];
	}





};
#endif //KNIGHTS_HORSES_H
