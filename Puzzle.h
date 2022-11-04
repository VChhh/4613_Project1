#pragma once

#include<vector>
#include<string>

class Puzzle{
public:
	Puzzle(std::vector<std::vector<unsigned char>>, std::vector<unsigned char>);
	void operator=(const Puzzle& rhs);
	void solve(std::vector<std::string>&, int& d);

	void left();
	void right();
	void up();
	void down();

private:
	std::vector<std::vector<unsigned char>> board;
	std::vector<unsigned char> goal; // 0 - 15 represents the position on the board
	unsigned char heuristic; // the heuristic value of current state
};
