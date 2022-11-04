#include<vector>
#include<string>
#include<queue>

#ifndef PUZZLE_H
#define PUZZLE_H



struct Chess {
	int value;
	int x;
	int y;
	Chess(int v, int x, int y) : value(v), x(x), y(y) {};
};

struct State {
	int heuristicValue;
	int stepTaken;
	int fValue;
	std::vector<Chess> board;
	std::string path;

	State() : heuristicValue(16), stepTaken(0), fValue(0), path("") {};
	State(int h, std::vector<Chess> c, int s, int f) : heuristicValue(h), board(c), stepTaken(s), fValue(f) {};
	void calculateHeuristic(const State&);
	inline bool operator==(const State&);
};

struct CompareState {
	bool operator()(State const& p1, State const& p2)
	{
		return p1.fValue < p2.fValue;
	}
};

class Puzzle{
public:
	Puzzle(int aWeight, std::vector<int>& aInit, std::vector<int>& aGoal);
	Puzzle(const Puzzle&);
	bool isVisited(State&);
	std::string solve();
	
private:
	std::priority_queue<State, std::vector<State>, CompareState> queue;
	std::vector<State> visited;
	State cur;
	State goal; // 0 - 15 represents the position on the board
	int weight;
	
};


#endif // !PUZZLE_H