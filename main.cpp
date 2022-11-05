#include<iostream>
#include<fstream>
#include "Puzzle.h"


void readInput() {

	int temp;
	for (int i = 1; i <= 8; i++) {
		float weight = 1.0f;
		std::vector<int> init;
		std::vector<int> goal;
		std::string res;

		std::ifstream file("input/input" + std::to_string(i) + ".txt");
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
		p.solve();
		std::cout << p;
		file.close();
	}


}

int main() {
	readInput();

}