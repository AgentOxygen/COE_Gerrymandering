/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"
#include <iostream>
#include <iomanip>
#include <math.h>

// Creates two-party district with specified distribution
District createDistrict(std::string major_party_code, unsigned int major_party_count, std::string minor_party_code, unsigned int minor_party_count) {
	// Keep track of next voter ID
	int next_unique_id = 1;
	// Create vector to store voters in
	std::vector<Voter> voters;
	// Reserve memory
	voters.reserve(major_party_count + minor_party_count);

	// Add major party voters
	for (unsigned int index = 0; index < major_party_count; index++) {
		Voter voter(major_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Add minor party voters
	for (unsigned int index = 0; index < minor_party_count; index++) {
		Voter voter(minor_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Return filled-district
	District ret(voters);
	return ret;
}

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
