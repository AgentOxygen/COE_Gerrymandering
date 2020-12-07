#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING

#include "PopulationCell.h"

class Districting {
private:
	// Number of columns in the population cell grid
	unsigned int pop_num_cols;
	// Number of rows in the population cell grid
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
	// Runs "lean" districting algorithm
	void districtLean(std::vector<PopulationCell>& population);
	// Runs "targeting" districting algorithm
	void districtTarget(std::vector<PopulationCell>& population, std::string target_party);

public:
	/// <summary>
	/// Creates mapping of districts for a given population cell grid
	/// </summary>
	/// <param name="population"> vector of population cells</param>
	/// <param name="width"> number of columns in the population cell grid</param>
	/// <param name="height"> number of rows in the population cell grid</param>
	/// <param name="algorithm"> equal to 1 selects targeting algorithm, anything not equal to 1 selcets the lean algorithm</param>
	/// <param name="args"> only relevant to targeting algorithm; specifies party to target</param>
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
/// <summary>
/// Outputs formatted print of the district IDs of each member in the grid to the console.
/// </summary>
/// <param name="grid"> vector of IDs in grid</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
void printDistrictIDGrid(std::vector<unsigned int> grid, unsigned int num_rows, unsigned int num_cols);
/// <summary>
/// Prints the tally of districts and voters affiliated with each party in the districting
/// </summary>
/// <param name="districting_algorithm"> districting to print</param>
void printAlgorithmResults(Districting districting_algorithm);
#endif