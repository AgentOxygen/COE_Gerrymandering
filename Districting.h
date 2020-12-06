#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING

#include "District.h"
#include "PopulationCell.h"

class Districting {
private:

	unsigned int pop_num_cols;
	unsigned int pop_num_rows;

	// All districts in this districting
	std::vector<District> districts;
	// Map of index of a cell in the population vector to the index of a district in the "districts" vector
	std::map<unsigned int, unsigned int> population_to_district;
	// Map of party to the number of districts voting for it
	std::map<std::string, unsigned int> party_district_counts;
	// Map of party to the number of voters voting for it
	std::map<std::string, unsigned int> party_voter_counts;
	// Number of voters in this districting
	unsigned int num_of_voters = 0;

	// Load districts from the population grid
	void loadDistricts(std::vector<PopulationCell>& population);
	// Count the number of district and popular votes for each party
	void countVotes();
	// Runs "lean" algorithm
	void districtLean(std::vector<PopulationCell>& population);
	// Runs "targeting" algorithm
	void districtTarget(std::vector<PopulationCell>& population, std::string target_party);

public:
	// Generate Districting out of provided population
	// population -> population cells to generate districts from
	// width -> number of columns in the population grid
	// height -> number of rows in the population grid
	// algorithm -> algorithm to use: (1) Majority   (2) Balanced   (Default/0) Lean
	// args -> arguments to pass to targeting algorithm
	Districting(std::vector<PopulationCell> population, unsigned int width, unsigned int height, int algorithm = 0, std::string args = "");

	// Returns a vetor of all districts in this districting
	std::vector<District> getDistricts();
	// Returns a vector of the same structure as the "population" vector, but with the index of their corresponding district found in "getDistricts()"
	std::vector<unsigned int> getDistricting();

	// Output districting array to a text file
	void outputDistricting(std::string path = "");
	// Returns map of each party's number of districts
	std::map<std::string, unsigned int> getPartyCounts();
	// Returns map of each party's number of voters in this entire districting
	std::map<std::string, unsigned int> getPopularCounts();
	// Returns number of voters in this districting
	unsigned int getNumOfVoters();
};

void printDistrictIDGrid(std::vector<unsigned int> grid, unsigned int num_rows, unsigned int num_cols);
#endif