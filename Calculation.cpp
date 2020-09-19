#include "Calculation.h"
//#include "String.h"//スパコン用

Calculation::Calculation(int Nsize, int _distribution_order, int _strategy_method) {
	N = Nsize;
	distribution_order = _distribution_order;
	strategy_method = _strategy_method;
	input_neighbor(N, neighbor, Hub_number, Middle_number, Fringe_number);
	input_beta(N, B);
} 

void Calculation::flow() {
	std::string str_order, str_method;
	switch (distribution_order){
	case Distribution_order::Hub:
		str_order = "Hub";
		break;
	case Distribution_order::Middle:
		str_order = "Middle";
		break;
	case Distribution_order::Fringe:
		str_order = "Fringe";
		break;
	default:
		std::cout << "Order name is wrong";
		break;
	}
	switch (strategy_method){
	case Strategy_method::IB_RA:
		str_method = "IB_RA";
		break;
	case Strategy_method::SB_RA:
		str_method = "SB_RA";
		break;
	case Strategy_method::DC:
		str_method = "DC";
		break;
	default:
		std::cout << "Method name is wrong";
		break;
	}
	/*
	std::string ResultDirectory = "C:/Users/rte19/Desktop/割引券モデル/Discount_distortion_model/VS/Result/";
	std::string FileName = ResultDirectory + str_method + "/C_" + str_order + "/result.csv";
	std::ofstream ofs(FileName);
	ofs << "Cr,sigma,VC,FES,SAP,VCH,VCM,VCF" << std::endl;
	*/
	//std::vector<int> n(11 * 101);
	//int n_size = 0;
//#pragma omp parallel for
	//for (int i = 0; i < n.size(); i++) n[i] = i;
//#pragma omp parallel for
	//for (int t = 0; t < n.size(); t++) {
		//int i = n[t] / 101;
		//int j = n[t] % 101;
		int i = 5;
		int j = 5;
		double Cr = i * 0.1;
		double sigma = j * 0.01;
		int season_num = 0;
		double cVC, pVC, FES, SAP, C_Hub, C_Middle, C_Fringe;
		cVC = pVC = FES = SAP = C_Hub = C_Middle = C_Fringe = 0;
		Strategy_update* SU = new Strategy_update(N, distribution_order, strategy_method, neighbor, Hub_number, Middle_number, Fringe_number, B, Cr, sigma);
		SU->initialize_strategy();
		for (int q = 0; q < 20; q++) {
			season_num++;
			SU->distribute_voucher();
			SU->initialize_infection();
			while (SU->information.I_number > 0) SU->change_state();
			SU->update_strategy();
		}
		do {
			pVC = cVC;
			cVC = FES = C_Hub = C_Middle = C_Fringe = 0;
			int season = SU->parameter.season;
			for (int q = 0; q < season; q++) {
				season_num++;
				SU->distribute_voucher();
				SU->initialize_infection();
				while (SU->information.I_number > 0) SU->change_state();
				SU->update_strategy();
				cVC += double(SU->information.V_number) / N;
				FES += double(SU->information.R_number) / N;
				C_Hub += double(SU->information.Hub_Vnum) / Hub_number;
				C_Middle += double(SU->information.Middle_Vnum) / Middle_number;
				C_Fringe += double(SU->information.Fringe_Vnum) / Fringe_number;
			}
			cVC /= season;
			FES /= season;
			C_Hub /= season;
			C_Middle /= season;
			C_Fringe /= season;
		} while (abs(cVC - pVC) > 0.01);
		SAP = (-Cr) * cVC - FES;
//#pragma omp critical
		{
			//n_size++;
			//ofs << Cr << "," << sigma << "," << cVC << "," << FES << "," << SAP << "," << C_Hub << "," << C_Middle << "," << C_Fringe << std::endl;
			//std::cout << "Cr:" << Cr << "  s:" << sigma << "  VC:" << cVC << "  FES:" << FES << "  SAP:" << SAP << " " << n_size << std::endl;
		}
		delete SU;
	//}
	//ofs.close();
}
