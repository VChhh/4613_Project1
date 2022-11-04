#include "Puzzle.h"

Puzzle::Puzzle(std::vector<std::vector<unsigned char>> _board, std::vector<unsigned char> _goal) {
	board = _board;
	goal = _goal;
	heuristic = 0;
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			heuristic += std::max(abs(int(_goal[_board[i][j]] / 4 - i)), abs(int(_goal[_board[i][j]] % 4 - j)));
		 }
	}
}

void Puzzle::operator=(const Puzzle& rhs) {
	board = rhs.board;
	goal = rhs.goal;
	heuristic = rhs.heuristic;
}

void Puzzle::left() {

}
void Puzzle::right() {

}

void Puzzle::up() {

}

void Puzzle::down() {

} 

void Puzzle::solve(std::vector<std::string>& path, int& d) {

}