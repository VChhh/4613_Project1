#include<vector>
#include<string>
#include<queue>

#ifndef PUZZLE_H
#define PUZZLE_H


struct Chess {
	int value;
	int x;
	int y;
	// Chess constructor
	Chess(int v, int x, int y) : value(v), x(x), y(y) {};
};

struct State {
	int heuristicValue;				// h(n)
	int stepTaken;					// g(n)
	float fValue;					// f(n) = g(n) + W * h(n)
	std::vector<Chess> board;		// vector of Chess with value and location
	std::string path;				// a path of string storing movement {L R U D}
	std::vector<float> fValuePath;	// a vector of float storing f(n) of each nodes in the path

	State() : heuristicValue(16), stepTaken(0), fValue(0.0f), path("") {};	// default constructor
	void calculateHeuristic(const State&);									// calculate h(n)
	void calculateFValue(float);											// calculate f(n)
	inline bool operator==(const State&);

	// operator< overload for prioritize state
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
	bool isVisited(State&);						// check if a state(node) is visited
	void findNeighbors(std::vector<State>&);	// find the neighbors of the current state
	void solve();								// method for solving the 15 puzzle

	// helper function
	void printState();
	void printQueue();

private:
	std::priority_queue<State> queue;			// priority queue for unvisited states
	std::vector<State> visited;					// visited states
	State init;									// initial state
	State cur;									// current state
	State goal;									// goal state
	float weight;								// weight
	int totalNodes;								// total nodes generated

};


#endif // !PUZZLE_H