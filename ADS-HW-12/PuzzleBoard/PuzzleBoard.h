//
// Created by Jose Ignacio Biehl on 28.04.20.
//

#ifndef PUZZLEBOARD_PUZZLEBOARD_H
#define PUZZLEBOARD_PUZZLEBOARD_H
#include <algorithm>
#include <iostream>
#include <queue>


class PuzzleBoard {
private:
// your choice
	int boardSize;
	int CX, CY;
	int** fields;

	int __makemove(int direction, int ref_position){
		int rx = ref_position / boardSize;
		int ry = ref_position % boardSize;

		if (!isValid(rx, ry))
			return -1;

		int tempx, tempy;
		int coeffx, coeffy;
		switch(direction){
			case(0):
				coeffx = -1;
				coeffy = 0;
				break;
			case(1):
				coeffx = 0;
				coeffy = 1;
				break;
			case(2):
				coeffx = 1;
				coeffy = 0;
				break;
			case(3):
				coeffx = 0;
				coeffy = -1;
				break;

		}

		tempx = rx  +coeffx*fields[rx][ry];
		tempy = ry + coeffy*fields[rx][ry];
		if (!isValid(tempx, tempy))
			return -1;
		return tempx * boardSize + tempy;
	}

public:
	// Subpoint (b)
	PuzzleBoard(int boardSize, int** fields = nullptr){
		this->boardSize = boardSize;
		if (fields == nullptr) {
			srand(time(NULL));
			fields = new int*[boardSize];
			for (int i = 0; i < boardSize; i++){
				fields[i] = new int[boardSize];
				for(int j = 0; j < boardSize; j++){
					fields[i][j] = 1 + (rand() % (boardSize-1));
				}
			}
			this->fields = fields;
		} else{
			this->fields = new int*[boardSize];
			for(int i = 0; i < boardSize; i++){
				this->fields[i] = new int[boardSize];
				for(int j = 0; j < boardSize; j++)
					this->fields[i][j] = fields[i][j];
			}
		}

		CX = CY = 0;
		}

	bool makemove(int direction){
		int tempx, tempy;
		int coeffx, coeffy;
		switch(direction){
			case(0):
				coeffx = -1;
				coeffy = 0;
				break;
			case(1):
				coeffx = 0;
				coeffy = 1;
				break;
			case(2):
				coeffx = 1;
				coeffy = 0;
				break;
			case(3):
				coeffx = 0;
				coeffy = -1;
				break;

		}

		tempx = CX  +coeffx*fields[CX][CY];
		tempy = CY + coeffy*fields[CX][CY];
		if (!isValid(tempx, tempy))
			return false;
		CX = tempx;
		CY = tempy;
		return true;
	}

	bool isValid(int x, int y){
		return (x >= 0 && y >= 0 && x < boardSize && y < boardSize);
	}

	bool getresult(){
		return(CX == boardSize-1 && CY == boardSize-1);
	}
	friend std::ostream& operator<<(std::ostream& os, PuzzleBoard const& m){
		for(int i  = 0; i < m.boardSize; i++){
			for (int j = 0; j < m.boardSize; j++) {
				if (i == m.CX && j == m.CY)
					os<<"[]";
				os << m.fields[i][j] <<"  ";
			}
			os<<"\n";
		}
		return os;
	}

	//transform table to actual graph
	int solve(){
		using namespace std;
		// keeps track of steps relative  to start
		int numNodes = boardSize * boardSize;
		int steps[numNodes];
		//keeps track of where each number came from
		int camefrom[numNodes];
		for(int i = 0; i < numNodes; i++ ) {
			steps[i] = -1;

		}
		steps[0] = 0;
		std::queue<int> container;
		container.push(0);
		while (!container.empty()){
			int current_container_value = container.front();
			container.pop();
			//cout<<"considering number: "<<current_container_value<<" steps value are "<<steps[current_container_value]<<endl;
			for(int i =0; i < 4; i++) {
				int temp = __makemove(i, current_container_value);
			//	cout<<"temp is: "<<temp<<endl;
				if (temp == -1)
					continue;
				if (steps[temp] == -1){
					steps[temp] = steps[current_container_value] +1;
					container.push(temp);
					camefrom[temp] = current_container_value;
				}
			}
		}
		if (steps[numNodes-1] == -1){
			std::cout<<"no solution was found!\n";
			return -1;
		}
		vector<int> path;
		int indx, val;
		val = numNodes-1;
		while (val != 0){
			path.push_back(val);
			val = camefrom[val];
		}
		path.push_back(0);
		std::reverse(path.begin(), path.end());
		cout<<"printing an optimal path: \n";
		for (auto i : path)
			cout<<"("<< i / boardSize<< ","<<i % boardSize<<")\n";

		return steps[numNodes-1];

	}
	~PuzzleBoard(){
		for (int i = 0; i < boardSize; i++){
			delete[] fields[i];
		}
	}


};


#endif //PUZZLEBOARD_PUZZLEBOARD_H
