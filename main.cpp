#include<iostream>
#include<fstream>
#include<format>
#include<string>
#include<string_view>
#include "Puzzle.h"


void readInput() {
	int temp;
	for (int i = 1; i <= 8; i++) {
		std::cout << "\n[ Input" << std::to_string(i) << " ]";
		float weight = 1.0f;
		std::vector<int> init;
		std::vector<int> goal;
		std::string res;

		// read file with name input(i).txt
		std::ifstream file("input/input" + std::to_string(i) + ".txt");
		// store weight
		file >> weight;

		// store initial state data
		for (int i = 0; i < 16; i++) {
			file >> temp;
			init.push_back(temp);
		}

		// store goal state data
		for (int i = 0; i < 16; i++) {
			file >> temp;
			goal.push_back(temp);
		}

		// declare Puzzle object and solve it
		Puzzle p(weight, init, goal);
		p.solve();

		// print the output
		std::cout << p;
		file.close();
	}
}

int main() {
	readInput();
}