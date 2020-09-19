#ifndef STRATEGY_UPDATE_H
#define STRATEGY_UPDATE_H
#include "Infection.h"

class Strategy_update :public Infection {
public:
	Strategy_update(int Nsize, int _distribution_order, int _strategy_method, std::vector<std::vector<int>>& neighbor,
		int Hub_number, int Middle_number, int Fringe_number, double B,
		double Cr, double sigma);
	std::vector<std::vector<int>> StateTransition;
	void record_state();
	int strategy_method;
	void initialize_strategy();
	void update_strategy();
private:
	void IB_RA();
	void SB_RA();
	void DC();
};

#endif // !STRATEGY_UPDATE_H

