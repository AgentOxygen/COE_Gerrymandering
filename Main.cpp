/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"
#include <iostream>
#include <iomanip>
#include <math.h>

// 
int main() {

	unsigned int num_rows = 6;
	unsigned int num_cols = 6;
	unsigned int max_population = 1000;
	std::vector<std::string> parties = { "A", "B" };

	std::vector<PopulationCell> pop  = genPopGrid(max_population, num_rows, num_cols, parties);

	Districting distr(pop, num_rows, num_cols);

	printPopulationGrid(pop, num_rows, num_cols);
	std::cout << std::endl;
	printDistrictIDGrid(distr.getDistricting(), num_rows, num_cols);
	outputPopulationCells(pop, num_rows, num_cols);

	distr.outputDistricting();

	return 0;
}
