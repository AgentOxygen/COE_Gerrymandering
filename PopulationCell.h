#ifndef GERRYMANDERING_POPULATION
#define GERRYMANDERING_POPULATION
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "District.h"

class PopulationCell {
private:
	// ==== Population Cell Stats ====
	// Number of votes for each party
	std::map<std::string, unsigned int> counts;
	// Party with most votes for this cell
	std::string lean = "";
	// Number of voters in this cell
	unsigned int size = 0;
	// Vector of voters in this cell
	std::vector<Voter> voters;

	PopulationCell* next = { nullptr };
	PopulationCell* prior = { nullptr };

	void changeUpstream(unsigned int index);
	PopulationCell* getHead();

	void updateStats(std::vector<Voter>& voters);
public:
	// Generates population cell with "size" number of random voters using specified parties distribution (randomly selects from "parties" vector)
	// "latest_id" refers to the last ID used to create a voter. This insures that no duplicate voters are created with the same ID across the entire project
	PopulationCell(unsigned int size, std::vector<std::string> parties, int& latest_ID);
	// Creates population cell from specified initial voters
	PopulationCell(std::vector<Voter>& initial_voters);
	// Returns lean of this population cell
	std::string getLean();
	// Returns the number of votes for each party
	std::map<std::string, unsigned int> getCounts();
	// Returns number of voters in this cell
	unsigned int getSize();
	// Returns vector of voters in this cell
	std::vector<Voter> getVoters();

	void linkPopulationCell(PopulationCell* population_cell);


	unsigned int grid_index;
	unsigned int district_index;
};
// Generates population grid
void outputPopulationGridLean(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path = "", std::string suffix = "");
void outputPopulationGridSize(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path = "", std::string suffix = "");
std::vector<PopulationCell> genPopGridUniformRandom(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties);
std::vector<PopulationCell> genPopGridUrbanCenter(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, double density = 0.7);
// Outputs population cell leans to the console
void printPopulationLean(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
void printPopulationIndex(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
void printPopulationDensity(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
// Count number of voters in vector of population cells
unsigned int getPopulationSize(std::vector<PopulationCell>& population);
// Counts the number of votes for each party for the entire vector of population cells
std::map<std::string, unsigned int> getPopularAffiliationCounts(std::vector<PopulationCell>& population);

#endif