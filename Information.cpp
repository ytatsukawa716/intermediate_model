#include "Information.h"

void Information::initialize_information(int N) {
	S_number = N;
	I_number = R_number = V_number = C_number = D_number = Hub_Vnum = Middle_Vnum = Fringe_Vnum = 0;
	C_gain = D_gain = 0;
	S_list.clear();
	I_list.clear();
}