#include<iostream>

#include "Puzzle.h"

using namespace std;


// calculate h(n)
void State::calculateHeuristic(const State& g) {
	int res = 0;
	for (const Chess& i : board) {
		for (const Chess& j : g.board) {
			if (i.value == j.value && i.value != 0) {
				res += max(abs(i.x - j.x), abs(i.y - j.y));
			}
		}
	}
	heuristicValue = res;
}

// calculate f(n)
void State::calculateFValue(float weight) {
	fValue = (float)stepTaken + weight * (float)heuristicValue;
}

// check if two board are the same
bool State::operator==(const State& rhs) {
	for (int i = 0; i < 16; i++) {
		if (board[i].value != rhs.board[i].value) {
			return false;
		}
	}
	return true;
}

// output the result in format
ostream& operator<<(ostream& os, const Puzzle& p) {
	os << "**************************************" << endl;
	// init
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			os << p.init.board[x + 4 * y].value << " ";
		}
		os << endl;
	}
	os << endl;
	// goal
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			os << p.goal.board[x + 4 * y].value << " ";
		}
		os << endl;
	}
	os << endl;
	// weight
	os << p.weight << endl;
	// shallowest depth
	os << p.cur.path.length() / 2 << endl;
	// total nodes
	os << p.totalNodes << endl;
	// solution
	os << p.cur.path << endl;
	// f(n) value path
	for (float i : p.cur.fValuePath) os << i << " ";
	os << endl;
	return os;
}

// constructor store weight, init, and goal state from input
Puzzle::Puzzle(float aWeight, vector<int>& aInit, vector<int>& aGoal):
	weight(aWeight), totalNodes(0)
{
	cur = State();
	goal = State();
	// store init, current, and goal state
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			init.board.push_back(Chess(aInit[x + y * 4], x, y));
			cur.board.push_back(Chess(aInit[x + y * 4], x, y));
			goal.board.push_back(Chess(aGoal[x + y * 4], x, y));
		}
	}
	// calculate h(n), f(n) for current(initial) state
	cur.calculateHeuristic(goal);
	cur.calculateFValue(weight);
	cur.fValuePath.push_back(cur.fValue);
	goal.calculateHeuristic(goal);

	// push initial state into priority queue
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

// find neighbor states
void Puzzle::findNeighbors(vector<State>& nbs) {
	// flag represents if the current state can move to ( ) state
	bool canL = true, canR = true, canU = true, canD = true;
	// postion of empty block
	int x0 = 0, y0 = 0;

	// calculate g(n) for neighbors
	int g = cur.stepTaken + 1;

	// find empty
	for (Chess& c : cur.board) {
		if (c.value == 0) {
			x0 = c.x;
			y0 = c.y;
			if (x0 == 0) canL = false;
			if (x0 == 3) canR = false;
			if (y0 == 0) canU = false;
			if (y0 == 3) canD = false;
			break;
		}
	}
	// left
	if (canL) {
		State LState(cur);
		// swap empty block with the block in the next position
		LState.board[x0 + y0 * 4].x = x0 - 1;
		LState.board[x0 + y0 * 4 - 1].x = x0;
		swap(LState.board[x0 + y0 * 4], LState.board[x0 + y0 * 4 - 1]);
		// calculate g(n), h(n), f(n) for the next state
		// append action path and vector of f(n)
		LState.stepTaken = g;
		LState.calculateHeuristic(goal);
		LState.calculateFValue(weight);
		LState.path += "L ";
		LState.fValuePath.push_back(LState.fValue);
		// append new state into the vector
		nbs.push_back(LState);
	}
	// right
	if (canR) {
		State RState(cur);
		// swap empty block with the block in the next position
		RState.board[x0 + y0 * 4].x = x0 + 1;
		RState.board[x0 + y0 * 4 + 1].x = x0;
		swap(RState.board[x0 + y0 * 4], RState.board[x0 + y0 * 4 + 1]);
		// calculate g(n), h(n), f(n) for the next state
		// append action path and vector of f(n)
		RState.stepTaken = g;
		RState.calculateHeuristic(goal);
		RState.calculateFValue(weight);
		RState.path += "R ";
		RState.fValuePath.push_back(RState.fValue);
		// append new state into the vector
		nbs.push_back(RState);
	}
	// up
	if (canU) {
		State UState(cur);
		// swap empty block with the block in the next position
		UState.board[x0 + y0 * 4].y = y0 - 1;
		UState.board[x0 + y0 * 4 - 4].y = y0;
		swap(UState.board[x0 + y0 * 4], UState.board[x0 + y0 * 4 - 4]);
		// calculate g(n), h(n), f(n) for the next state
		// append action path and vector of f(n)
		UState.stepTaken = g;
		UState.calculateHeuristic(goal);
		UState.calculateFValue(weight);
		UState.path += "U ";
		UState.fValuePath.push_back(UState.fValue);
		// append new state into the vector
		nbs.push_back(UState);
	}
	// down
	if (canD) {
		State DState(cur);
		// swap empty block with the block in the next position
		DState.board[x0 + y0 * 4].y = y0 + 1;
		DState.board[x0 + y0 * 4 + 4].y = y0;
		swap(DState.board[x0 + y0 * 4], DState.board[x0 + y0 * 4 + 4]);
		// calculate g(n), h(n), f(n) for the next state
		// append action path and vector of f(n)
		DState.stepTaken = g;
		DState.calculateHeuristic(goal);
		DState.calculateFValue(weight);
		DState.path += "D ";
		DState.fValuePath.push_back(DState.fValue);
		// append new state into the vector
		nbs.push_back(DState);
	}
}


// solve puzzle and return the string a path
void Puzzle::solve() {
	//is-goal
	while (!queue.empty()) {
		// count nodes number
		totalNodes++;
		// extract min
		cur = queue.top();	
		visited.push_back(cur);
		queue.pop();
		// if goal is met, return
		if (cur.heuristicValue == 0) return;
		// add states into neighbors
		std::vector<State> neighbors;
		findNeighbors(neighbors);

		// add unvisited neighbors into priority queue
		for (State& n : neighbors) {
			if (!isVisited(n)) {
				queue.push(n);
			}
		}
	}
}


// helper function: print chessboard, print priority queue(fvalue)
void Puzzle::printState() {
	cout << endl;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			
			cout << cur.board[x + 4 * y].value << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Puzzle::printQueue() {
	priority_queue<State> g = queue;
	while (!g.empty()) {
		cout << " " << g.top().fValue;
		g.pop();
	}
	cout << '\n';
}
