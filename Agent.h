#ifndef AGENT_H
#define AGENT_H
#include <vector>
#include "NameDefinition.h"

class Agent {
public:
	std::vector<double> gain;
	std::vector<std::vector<int> > neighbor;
	std::vector<int> NI;
	std::vector<int> state;
	std::vector<int> strategy;
	std::vector<int> voucher;
	void initialize_agent_season(int N);
};

#endif // !AGENT_H

