#ifndef INFECTION_H
#define INFECTION_H
#include "Discount.h"

class Infection :public Discount {
public:
	double beta;
	void initialize_infection();
	void change_state();
private:
	double x;
	void initialize_transition_p();
	void change_S_to_I();
	void change_I_to_R();
};

#endif // !INFECTION_H