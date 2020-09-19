#ifndef NAMEDEFINITION_H
#define NAMEDEFINITION_H

struct State {
	static const int S = 0;
	static const int I = 1;
	static const int R = 2;
	static const int V = 3;
};

struct Strategy {
	static const int C = 0;
	static const int D = 1;
};

struct Voucher {
	static const int Yes = 0;
	static const int No = 1;
};

struct Strategy_method {
	static const int IB_RA = 0;
	static const int SB_RA = 1;
	static const int DC = 2;
};

struct Distribution_order {
	static const int Hub = 0;
	static const int Middle = 1;
	static const int Fringe = 2;
};

struct End_state {
	static const int V_Self = 1;
	static const int V_Subsidy = 2;
	static const int D_Subsidy = 3;
	static const int FreeRider = 4;
	static const int Infected = 5;
};


#endif // !NAMEDEFINITION_H

