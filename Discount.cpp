#include "Discount.h"
#include "sort.h"

void Discount::distribute_voucher() {
	agent.initialize_agent_season(N);
	information.initialize_information(N);
	target.clear();
	comparison.clear();
	for (int i = 0; i < N; i++) {
		if (agent.strategy[i] == Strategy::C) {
			information.C_number++;
			target.push_back(i);
			comparison.push_back(agent.neighbor[i].size());
			int degree = agent.neighbor[i].size();
			if (degree >= 10) information.Hub_Vnum++;
			else if (degree < 10 and degree >= 6) information.Middle_Vnum++;
			else information.Fringe_Vnum++;
		}
		else {
			information.D_number++;
			information.S_list.push_back(i);
		}
	}
	switch (distribution_order) {
	case Distribution_order::Hub:
		C_Hub();
		break;
	case Distribution_order::Fringe:
		C_Fringe();
		break;
	default:
		std::cout << "Don't distribute Voucher." << std::endl;
		exit(0);
		break;
	}
}

void Discount::shuffle(const int size, std::vector<int>& number) {
	//同じ次数の人をシャッフルする．ただしシャッフルするのは，補助金サイズsigmaによってはもらえたり，もらえなかったりする人たち．
	if (size > 1) {
		int last = size;
		if (last > comparison.size()) last = comparison.size();
		int last_comparison = comparison[last - 1];
		std::vector<int> same_comparison_agent(1, number[last - 1]);
		bool ufg, lfg;
		int un = last;
		int ln = last - 2;
		int begin_number = last - 1;
		if (un > comparison.size() - 1) ufg = false;
		else ufg = true;
		if (ln < 0) lfg = false;
		else lfg = true;
		while (ufg or lfg) {
			if (ufg) {
				if (comparison[un] == last_comparison) same_comparison_agent.push_back(number[un]);
				else ufg = false;
			}
			if (lfg) {
				if (comparison[ln] == last_comparison) {
					same_comparison_agent.push_back(number[ln]);
					begin_number--;
				}
				else lfg = false;
			}
			un++;
			ln--;
			if (un == comparison.size()) ufg = false;
			if (ln < 0) lfg = false;
		}
		while (same_comparison_agent.size() > 0) {
			int ssize = same_comparison_agent.size();
			int xs = random(ssize - 1);
			int num = same_comparison_agent[xs];
			std::iter_swap(same_comparison_agent.begin() + xs, same_comparison_agent.end() - 1);
			same_comparison_agent.pop_back();

			number[begin_number] = num;
			begin_number++;
			if (same_comparison_agent.empty()) break;	//保険，実際は記述不要
		}
	}
}

//歪のつけ方は財政をCの次数で等分
void Discount::C_Hub() {
	std::string filename = "C:/Users/rte19/Desktop/論文関係/割引券モデル/Degree_r_Cr0.50sigma0.50.csv";
	std::ofstream ofs1(filename);
	ofs1 << "Degree,rate" << std::endl;
	rate = 0;
	if (comparison.size() > 0 and !comparison.empty()) {
		int size = information.C_number;
		Sort sort;
		sort.descending_sort(comparison);
		int ar_num = 0;
		std::vector<std::vector<int>> DegreeClass;
		std::vector<int> Degree;
		int pD = comparison[0];
		Degree.push_back(target[sort.number[0]]);
		for (int i = 1; i < comparison.size(); i++) {
			int cD = comparison[i];
			int num = target[sort.number[i]];
			if (pD == cD) Degree.push_back(num);
			else {
				DegreeClass.push_back(Degree);
				Degree.clear();
				Degree.push_back(num);
			}
			pD = cD;
		}
		DegreeClass.push_back(Degree);
		double f = sigma * N;
		for (int i = 0; i < DegreeClass.size(); i++) {
			if (f == 0) rate = 0;
			else {
				int distortion = DegreeClass.size() - i;
				double fk = f / distortion;
				rate = fk / DegreeClass[i].size();
				if (rate >= 1.0) rate = 1.0;
				std::cout << "Degree:" << agent.neighbor[DegreeClass[i][0]].size() << "  rate:" << rate << std::endl;
				ofs1 << agent.neighbor[DegreeClass[i][0]].size() << "," << rate << std::endl;
				//getchar();
			}
			for (int j = 0; j < DegreeClass[i].size(); j++) {
				int num = DegreeClass[i][j];
				agent.state[num] = State::V;
				agent.voucher[num] = Voucher::Yes;
				agent.gain[num] = -(1.0 - rate) * Cr;
				f -= rate;
				information.C_gain += agent.gain[num];
				information.S_number--;
				information.V_number++;
			}
		}
	}
}

//Fringeに関しては未完成（Fringeの割引率を大きくするには歪のつけ方を工夫する必要あり）
void Discount::C_Fringe() {
	rate = 0;
	if (comparison.size() > 0 and !comparison.empty()) {
		int size = information.C_number;
		std::vector<std::vector<int>> DegreeClass;
		Sort sort;
		sort.ascending_sort(comparison);
		int kmax = comparison[sort.number[0]];
		int ar_num = 0;
		DegreeClass[ar_num].push_back(target[sort.number[0]]);
		for (int i = 1; i < target.size(); i++) {
			int cnum = sort.number[i];
			int pnum = sort.number[i - 1];
			if (comparison[cnum] != comparison[pnum]) ar_num++;
			DegreeClass[ar_num].push_back(target[cnum]);
		}
		double f = sigma * N;
		for (int i = 0; i < DegreeClass.size(); i++) {
			int distortion = DegreeClass.size() - i;
			double fk = f / distortion;
			rate = fk / DegreeClass[i].size();
			if (rate >= 1.0) rate = 1.0;
			for (int j = 0; j < DegreeClass[i].size(); j++) {
				int num = DegreeClass[i][j];
				agent.state[num] = State::V;
				agent.voucher[num] = Voucher::Yes;
				agent.gain[num] = -(1.0 - rate) * Cr;
				f -= rate;
				information.C_gain += agent.gain[num];
				information.S_number--;
				information.V_number++;
			}
		}
	}
}
