#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <string>
#include "Data_in.h"
//#include "String.h"//スパコン用

void input_neighbor(int N, std::vector<std::vector<int>>& neighbor, int & H_num, int& M_num, int& F_num) {
	neighbor = std::vector<std::vector<int>>(N);
	std::string file_name = "C:/Users/rte19/Desktop/参照データ/base_BA_SF_N" + std::to_string(N) + "_K8.dat";
	std::ifstream ifs(file_name);
	if (!ifs) {
		std::cout << "Can not open " << file_name << std::endl;
		exit(0);
	}
	std::string str;
	int num, Hn, Mn, Fn;
	num = Hn = Mn = Fn = 0;
	while (std::getline(ifs, str)) {
		std::string figure = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',') figure += str[i];
			else {
				neighbor[num].push_back(std::stoi(figure));
				figure = "";
			}
		}
		neighbor[num].push_back(std::stoi(figure));
		if (neighbor[num].size() >= 10) Hn++;
		else if (neighbor[num].size() < 10 and neighbor[num].size() >= 6) Mn++;
		else  Fn++;
		num++;
	}
	H_num = Hn;
	M_num = Mn;
	F_num = Fn;
}

void input_beta(int N, double& beta) {
	std::string file_name = "C:/Users/rte19/Desktop/参照データ/base_beta_BA_SF_N" + std::to_string(N) + "_K8.dat";
	std::ifstream ifs(file_name);
	if (!ifs) {
		std::cout << "Can not open " << file_name << std::endl;
		exit(0);
	}
	ifs >> beta;
}

//スパコン用
/*
void input_neighbor(int N, std::vector<std::vector<int> >& neighbor, int & H_num, int& M_num, int& F_num) {
	neighbor = std::vector<std::vector<int> >(N);
	std::string file_name = "../Data/base_BA_SF_N10000_K8.dat";
	const char* _file_name = file_name.c_str();
	int Hn, Mn, Fn;
	Hn = Mn = Fn = 0;
	std::ifstream ifs(_file_name);
	if (!ifs) {
		std::cout << "Can not open " << file_name << std::endl;
		exit(0);
	}
	std::string str;
	int num = 0;
	while (std::getline(ifs, str)) {
		std::string figure = "";
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',') figure += str[i];
			else {
				neighbor[num].push_back(stoi(figure));
				figure = "";
			}
		}
		neighbor[num].push_back(stoi(figure));
		if (neighbor[num].size() >= 10) Hn++;
		else if (neighbor[num].size() < 10 and neighbor[num].size() >= 6) Mn++;
		else  Fn++;
		num++;
	}
	H_num = Hn;
	M_num = Mn;
	F_num = Fn;
}

void input_beta(int N, double& beta) {
	std::string file_name = "../Data/base_beta_BA_SF_N10000_K8.dat";
	const char* _file_name = file_name.c_str();
	std::ifstream ifs(_file_name);
	if (!ifs) {
		std::cout << "Can not open " << file_name << std::endl;
		exit(0);
	}
	ifs >> beta;
}
*/