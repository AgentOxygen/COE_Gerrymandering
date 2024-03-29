/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"

int main() {

	unsigned int num_rows = 10;
	unsigned int num_cols = 10;
	unsigned int max_population = 10000;
	std::vector<std::string> parties = { "R", "D", "T" };

	std::vector<PopulationCell> pop = genPopGridUrbanCenter(max_population, num_rows, num_cols, parties, 1);

	Districting leanAlgorithm(pop, num_rows, num_cols);
	Districting targetAlgorithm(pop, num_rows, num_cols, 1, "T");
	std::cout << "=== Population Lean ===" << std::endl;
	printPopulationLean(pop, num_rows, num_cols);
	std::cout << "=== Population Density ===" << std::endl;
	printPopulationDensity(pop, num_rows, num_cols);
	std::cout << "=== Population Index ====" << std::endl;
	printPopulationIndex(pop, num_rows, num_cols);
	std::cout << "=== Target Districts ===" << std::endl;
	printDistrictIDGrid(targetAlgorithm.getDistricting(), num_rows, num_cols);
	std::cout << "=== Lean Algorithm Districts ====" << std::endl;
	printDistrictIDGrid(leanAlgorithm.getDistricting(), num_rows, num_cols);
	std::cout << std::endl;


	outputPopulationGridSize(pop, num_rows, num_cols);
	leanAlgorithm.outputDistricting("lean");
	targetAlgorithm.outputDistricting("target");

	std::cout << "====== Lean Algorithm ======" << std::endl;
	printAlgorithmResults(leanAlgorithm);

	std::cout << "====== Target Algorithm ======" << std::endl;
	printAlgorithmResults(targetAlgorithm);



	return 0;
}
