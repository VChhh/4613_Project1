#include<iostream>
#include "Puzzle.h"

void readInput(float w, std::vector<int>& i, std::vector<int>& g) {

}

int main() {
	float weight = 1.0f;
	std::vector<int> init;
	std::vector<int> goal;
	std::string res;



	Puzzle p(weight, init, goal);

	res = p.solve();
	std::cout << res;

}