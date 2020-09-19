#ifndef CALCULATION_H
#define CALCULATION_H
#include "Strategy_update.h"

class Calculation {
public:
	Calculation(int Nsize, int _distribution_order, int _strategy_method);
	void flow();
private:
	int N;
	int distribution_order;
	int strategy_method;
	std::vector<std::vector<int>> neighbor;
	int Hub_number;
	int Middle_number;
	int Fringe_number;
	double B;
};

#endif // !CALCULATION_H

