#ifndef INFORMATION_H
#define INFORMATION_H
#include <vector>

struct Degree {
	int number;
	int V_num;
	double rate;
};

class Information {
public:
	int Hub_number;
	int Middle_number;
	int Fringe_number;
	int S_number;
	int I_number;
	int R_number;
	int V_number;
	int C_number;
	int D_number;
	int Hub_Vnum;
	int Middle_Vnum;
	int Fringe_Vnum;
	double C_gain;
	double D_gain;
	double SI_probability;
	double IR_probability;
	std::vector<int> S_list;
	std::vector<int> I_list;
	void initialize_information(int N);
private:
};


#endif // !INFORMATION_H

