#include "Infection.h"

void Infection::initialize_infection() {
	for (int i = 0; i < parameter.Io; i++) {
		if (information.S_list.size() == 0) break;
		int size = information.S_list.size() - 1;
		int xsize = random(size);
		int number = information.S_list[xsize];
		std::iter_swap(information.S_list.begin() + xsize, information.S_list.end() - 1);
		information.S_list.pop_back();
		information.I_list.push_back(number);
		agent.state[number] = State::I;
		agent.gain[number] = -1.0;
		information.D_gain += agent.gain[number];
		for (int j = 0; j < agent.neighbor[number].size(); j++) {
			int num = agent.neighbor[number][j];
			agent.NI[num]++;
		}
		information.S_number--;
		information.I_number++;
	}
	initialize_transition_p();
}

void Infection::change_state() {
	x = random(1.0);
	double state_boundary_p = information.SI_probability / (information.SI_probability + information.IR_probability);
	if (x <= state_boundary_p) {
		x /= state_boundary_p;
		change_S_to_I();
	}
	else {
		x = (x - state_boundary_p) / (1 - state_boundary_p);
		change_I_to_R();
	}
}

void Infection::initialize_transition_p() {
	information.SI_probability = information.IR_probability = 0;
	for (int i = 0; i < N; i++) {
		switch (agent.state[i]) {
		case State::S:
			information.SI_probability += beta * agent.NI[i];
			break;
		case State::I:
			information.IR_probability += parameter.ganma;
			break;
		default:
			break;
		}
	}
}

void Infection::change_S_to_I() {
	double agent_select_p = 0;
	for (int i = 0; i < information.S_list.size(); i++) {
		int num = information.S_list[i];
		agent_select_p += beta * agent.NI[num] / information.SI_probability;
		if (x <= agent_select_p) {
			agent.state[num] = State::I;
			agent.gain[num] -= 1.0;
			information.D_gain += agent.gain[num];
			information.SI_probability -= beta * agent.NI[num];
			information.IR_probability += parameter.ganma;
			std::iter_swap(information.S_list.begin() + i, information.S_list.end() - 1);
			information.S_list.pop_back();
			information.I_list.push_back(num);
			for (int j = 0; j < agent.neighbor[num].size(); j++) {
				int an = agent.neighbor[num][j];
				if (agent.state[an] == State::S) {
					agent.NI[an]++;
					information.SI_probability += beta;
				}
			}
			information.S_number--;
			information.I_number++;
			break;
		}
	}
}

void Infection::change_I_to_R() {
	double agent_select_p = 0;
	for (int i = 0; i < information.I_list.size(); i++) {
		int num = information.I_list[i];
		agent_select_p += parameter.ganma / information.IR_probability;
		if (x <= agent_select_p) {
			agent.state[num] = State::R;
			information.IR_probability -= parameter.ganma;
			std::iter_swap(information.I_list.begin() + i, information.I_list.end() - 1);
			information.I_list.pop_back();
			for (int j = 0; j < agent.neighbor[num].size(); j++) {
				int an = agent.neighbor[num][j];
				if (agent.state[an] == State::S) {
					agent.NI[an]--;
					information.SI_probability -= beta;
				}
			}
			information.I_number--;
			information.R_number++;
			break;
		}
	}
}
