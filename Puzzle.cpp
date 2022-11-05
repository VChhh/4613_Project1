#include "Puzzle.h"

using namespace std;



void State::calculateHeuristic(const State& g) {
	int res = 0;
	for (const Chess& i : board) {
		for (const Chess& j : g.board) {
			if (i.value == j.value) {
				res += max(abs(i.x - j.x), abs(i.y - j.y));
			}
		}
	}
	heuristicValue = res;
}

bool State::operator==(const State& rhs) {
	for (int i = 0; i < 16; i++) {
		if (board[i].value != rhs.board[i].value) {
			return false;
		}
	}
	return true;
}

// constructor store weight, init, and goal from input
Puzzle::Puzzle(int aWeight, vector<int>& aInit, vector<int>& aGoal): weight(aWeight) {
	cur = State();
	goal = State();
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cur.board.push_back(Chess(aInit[x + y * 4], x, y));
			goal.board.push_back(Chess(aGoal[x + y * 4], x, y));
		}
	}
	cur.calculateHeuristic(goal);
	goal.calculateHeuristic(goal);
	queue.push(cur);
}

// copy constructor
Puzzle::Puzzle(const Puzzle& rhs) {
	queue = rhs.queue;
	visited = rhs.visited;
	cur = rhs.cur;
	goal = rhs.goal;
	weight = rhs.weight;
}

// check if a state is visited
bool Puzzle::isVisited(State& p1) {
	for (State& p2 : visited) {
		if (p1 == p2) {
			return true;
		}
	}
	return false;
}

void Puzzle::findNeighbors(vector<State>& nbs) {
	bool canL = true, canR = true, canU = true, canD = true;
	int x0, y0;
	// g(n)
	int g = cur.stepTaken + 1;

	// find empty
	for (Chess& c : cur.board) {
		if (c.value == 0) {
			x0 = c.x;
			y0 = c.y;
			if (x0 == 0) canR = false;
			if (x0 == 3) canL = false;
			if (y0 == 0) canD = false;
			if (y0 == 3) canU = false;
			break;
		}
	}
	// left
	if (canL) {

	}
	// right
	if (canR) {

	}
	// up
	if (canU) {

	}
	// down
	if (canD) {

	}
}


// solve puzzle and return the string a path
string Puzzle::solve() {
	//is-goal
	if (cur.heuristicValue == 0) return cur.path;
	while (!queue.empty()) {
		// extract min
		cur = queue.top();
		visited.push_back(cur);
		queue.pop();
		// TODO: add states into neighbors
		std::vector<State> neighbors;


		// add unvisited neighbors into priority queue
		for (State& n : neighbors) {
			if (!isVisited(n)) {
				queue.push(n);
			}
		}
	}

}

//void Puzzle::operator=(const Puzzle& rhs) {
//	board = rhs.board;
//	goal = rhs.goal;
//	heuristic = rhs.heuristic;
//}

//void Puzzle::left() {
//
//}
//void Puzzle::right() {
//
//}
//
//void Puzzle::up() {
//
//}
//
//void Puzzle::down() {
//
//} 
//
//void Puzzle::solve(std::vector<std::string>& path, int& d) {
//
//}