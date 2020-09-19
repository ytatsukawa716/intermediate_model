#include "Agent.h"

void Agent::initialize_agent_season(int N) {
	gain = std::vector<double>(N, 0);
	NI = std::vector<int>(N, 0);
	state = std::vector<int>(N, State::S);
	voucher = std::vector<int>(N, Voucher::No);
}