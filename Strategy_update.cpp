#include "Strategy_update.h"

Strategy_update::Strategy_update(int Nsize, int _distribution_order, int _strategy_method, std::vector<std::vector<int>> &neighbor,
	int Hub_number,int Middle_number, int Fringe_number, double B,
	double Cr, double sigma) {
	N = Nsize;
	distribution_order = _distribution_order;
	strategy_method = _strategy_method;
	agent.neighbor = neighbor;
	information.Hub_number = Hub_number;
	information.Middle_number = Middle_number;
	information.Fringe_number = Fringe_number;
	beta = B;
	parameter.ganma = 1.0 / 3.0;
	parameter.kappa = 0.1;
	this->Cr = Cr;
	this->sigma = sigma;
}

void Strategy_update::record_state() {
	for (int i = 0; i < N; i++) {
		int ES;
		if (agent.strategy[i] == Strategy::C) {
			if (agent.voucher[i] == Voucher::Yes) ES = End_state::V_Subsidy;
			else ES = End_state::V_Self;
		}
		else {
			if (agent.gain[i] == 0) ES = End_state::FreeRider;
			else ES = End_state::Infected;
		}
		StateTransition[i].push_back(ES);
	}
}

void Strategy_update::initialize_strategy() {
	StateTransition = std::vector<std::vector<int> >(N);
	agent.strategy = std::vector<int>(N, Strategy::D);
	int n = N / 2;
	std::vector<int> list(N);
	for (int i = 0; i < N; i++) list[i] = i;
	for (int i = 0; i < n; i++) {
		int size = list.size() - 1;
		int xsize = random(size);
		int number = list[xsize];
		std::iter_swap(list.begin() + xsize, list.end() - 1);
		list.pop_back();
		agent.strategy[number] = Strategy::C;
	}
}

void Strategy_update::update_strategy() {
	switch (strategy_method) {
	case Strategy_method::IB_RA: IB_RA();
		break;
	case Strategy_method::SB_RA: SB_RA();
		break;
	case Strategy_method::DC: DC();
		break;
	default:
		std::cout << "Don't update strategy." << std::endl;
		break;
	}
}

void Strategy_update::IB_RA() {
	std::vector<int> previous_strategy = agent.strategy;
	for (int i = 0; i < N; i++) {
		int size = agent.neighbor[i].size() - 1;
		int xsize = random(size);
		int number = agent.neighbor[i][xsize];
		if (agent.strategy[i] != previous_strategy[number]) {
			double random_number = random(1.0);
			double pai = agent.gain[i] - agent.gain[number];
			double p_itoj = 1 / (1 + exp(pai / parameter.kappa));
			if (random_number <= p_itoj) agent.strategy[i] = previous_strategy[number];
		}
	}
}

void Strategy_update::SB_RA() {
	std::vector<int> previous_strategy = agent.strategy;
	for (int i = 0; i < N; i++) {
		int size = agent.neighbor[i].size() - 1;
		int xsize = random(size);
		int number = agent.neighbor[i][xsize];
		double random_number = random(1.0);
		if (agent.strategy[i] != previous_strategy[number]) {
			double pai;
			if (agent.strategy[number] == Strategy::C) pai = agent.gain[i] - (-Cr);
			else pai = agent.gain[i] - (information.D_gain / information.D_number);
			double p_itoj = 1 / (1 + exp(pai / parameter.kappa));
			if (random_number <= p_itoj) agent.strategy[i] = previous_strategy[number];
		}
	}
}

void Strategy_update::DC() {
	std::vector<int> previous_strategy = agent.strategy;
	for (int i = 0; i < N; i++) {
		int nC_number = 0;
		int nD_number = 0;
		double nC_gain = 0;
		double nD_gain = 0;
		double pai;
		for (int j = 0; j < agent.neighbor[i].size(); j++) {
			int an = agent.neighbor[i][j];
			if (previous_strategy[an] == Strategy::C) {
				nC_number++;
				nC_gain += agent.gain[an];
			}
			else {
				nD_number++;
				nD_gain += agent.gain[an];
			}
		}
		if (nC_number > 0 and nD_number > 0) {
			pai = -(nC_gain / nC_number - nD_gain / nD_number);
			double p_i = 1 / (1 + exp(pai / parameter.kappa));
			double random_number = random(1.0);
			if (random_number <= p_i) agent.strategy[i] = Strategy::C;
			else agent.strategy[i] = Strategy::D;
		}
		else {
			if (nC_number == 0) agent.strategy[i] = Strategy::D;
			else agent.strategy[i] = Strategy::C;
		}
	}
}
