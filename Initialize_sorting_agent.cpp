#include "Initialize_sorting_agent.h"

struct Sort_Order {
	static const int Hub = 0;
	static const int Fringe = 1;
};


void initializing_sorting_agent(const int Order, std::vector<std::vector<int>>& neighbor) {
	Sort sort;
	int N = neighbor.size();
	std::vector<int> degree(N);
	for (int i = 0; i < N; i++) degree[i] = neighbor[i].size();
	switch (Order) {
	case Sort_Order::Hub:
		sort.descending_sort(degree);
		break;
	case Sort_Order::Fringe:
		sort.ascending_sort(degree);
		break;
	default:
		std::cout << "ERROR ORDER" << std::endl;
		getchar();
		exit(EXIT_FAILURE);
	}
	std::vector<int> next_number(N);	//next_number[current agent number] = next agent number
	for (int i = 0; i < N; i++) next_number[sort.number[i]] = i;
	std::vector<std::vector<int>> next_neighbor(N);
	for (int i = 0; i < N; i++) {
		int number = next_number[i];
		next_neighbor[number] = std::vector<int>(neighbor[i].size());
		for (int j = 0; j < next_neighbor[number].size(); j++) next_neighbor[number][j] = next_number[neighbor[i][j]];
		Sort s;
		s.ascending_sort(next_neighbor[number]);
	}
	neighbor = next_neighbor;
}