#include <iostream>
#include <ctime>
#include <set>
#include <algorithm>
using namespace std;


int main() {
	srand(time(NULL));
	set<int> container;
	int random;
	//loops searching for unique random numbers to put in.
	for (int i =0; i < 6;) {
		random = rand() % 49 +1;
		auto it = container.find(random);
		if (it == container.end()) {
			container.insert(random);
			i++;
		}

	}
	//sets are binary trees so iterating through it should be in ascending order
	for (auto const& elem: container)
		cout<<elem<<endl;
}
