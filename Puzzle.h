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
	float fValue;
	std::vector<Chess> board; // 0-15
	std::string path;
	std::vector<float> fValuePath;

	State() : heuristicValue(16), stepTaken(0), fValue(0.0f), path("") {};
	//State(int h, std::vector<Chess> c, int s, int f) :
	//	heuristicValue(h), board(c), stepTaken(s), fValue(f) {};
	void calculateHeuristic(const State&);
	void calculateFValue(float);
	inline bool operator==(const State&);

	bool operator<(const State& rhs) const
	{
		return fValue > rhs.fValue;
	}
};


class Puzzle {
	friend std::ostream& operator<<(std::ostream& os, const Puzzle& dt);
public:
	Puzzle(float aWeight, std::vector<int>& aInit, std::vector<int>& aGoal);
	Puzzle(const Puzzle&);
	bool isVisited(State&);
	void findNeighbors(std::vector<State>&);
	void solve();
	void printState();
	void printQueue();

private:
	std::priority_queue<State> queue;
	std::vector<State> visited;
	State init;
	State cur;
	State goal;
	float weight;
	int totalNodes;

};


#endif // !PUZZLE_H