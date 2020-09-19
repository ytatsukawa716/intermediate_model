#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "Calculation.h"

int main() {
	int N = 10000;
	int distribution_order;
	int strategy_method;
	std::string FileName = "C:/Users/rte19/Desktop/Š„ˆøŒ”ƒ‚ƒfƒ‹/Discount_distortion_model/VS/Discount_distortion_model/ConditonFile.txt";
	const char* F = FileName.c_str();
	std::ifstream ifs(F);
	if (!ifs) {
		std::cout << "Can not open " << FileName << std::endl;
		exit(0);
	}
	std::string F_order, F_method;
	ifs >> F_order >> F_method;
	ifs.close();
	if (F_order == "Hub") distribution_order = Distribution_order::Hub;
	else if (F_order == "Fringe") distribution_order = Distribution_order::Fringe;
	else {
		std::cout << "Can not read distribution_order" << std::endl;
		exit(0);
	}
	if (F_method == "IB_RA") strategy_method = Strategy_method::IB_RA;
	else if (F_method == "SB_RA") strategy_method = Strategy_method::SB_RA;
	else if (F_method == "DC") strategy_method = Strategy_method::DC;
	else {
		std::cout << "Can not read strategy_method" << std::endl;
		exit(0);
	}
	Calculation result(N, distribution_order, strategy_method);
	result.flow();
	getchar();
	return 0;
}