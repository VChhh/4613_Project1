#include<iostream>
#include<fstream>
#include "Puzzle.h"


void readInput(float w, std::vector<int>& i, std::vector<int>& g) {

}

int main() {
	float weight = 1.0f;
	std::vector<int> init;
	std::vector<int> goal;
	std::string res;

	int temp;
	std::ifstream file("input/input1.txt");
	file >> weight;
	for (int i = 0; i < 16; i++) {
		file >> temp;
		init.push_back(temp);
	}

	for (int i = 0; i < 16; i++) {
		file >> temp;
		goal.push_back(temp);
	}




	Puzzle p(weight, init, goal);

	res = p.solve();
	std::cout << res;

}