#ifndef DISCOUNT_H
#define DISCOUNT_H
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Agent.h"
#include "Data_in.h"
#include "Information.h"
#include "random.h"

struct Parameter {
	static const int Io = 5;
	double ganma;
	double kappa;
	static const int ensemble = 1;
	static const int season = 100;
};

class Discount {
public:
	Agent agent;
	Information information;
	Parameter parameter;
	int N;
	int distribution_order;
	double Cr;
	double sigma;
	double rate;
	void distribute_voucher();
private:
	std::vector<int> target;
	std::vector<int> comparison;
	void shuffle(const int size, std::vector<int>& number);
	void C_Hub();
	void C_Fringe();
};



#endif // ! DISCOUNT_H
