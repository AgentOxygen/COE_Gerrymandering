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

	// Pointer to next cell in linked list
	PopulationCell* next = { nullptr };
	// Pointer to previous cell in linked list
	PopulationCell* prior = { nullptr };
	/// <summary>
	/// Changes the index of this population cell and all of the population cells ahead of it in the linked list
	/// </summary>
	/// <param name="index"> index to change to</param>
	void changeUpstream(unsigned int index);
	// Returns the first cell in this cell's linked list (the cell without a "next" pointer)
	PopulationCell* getHead();
	// Updates the statistics of this population cell to account for the voters
	void updateStats();
public:
	/// <summary>
	/// Generates information on an area of voters
	/// </summary>
	/// <param name="size"> number of voters to fill this cell with</param>
	/// <param name="parties"> distribution of parties to randomly affiliate voters with</param>
	/// <param name="latest_ID"> integer variable for keeping track of new voter IDs</param>
	PopulationCell(unsigned int size, std::vector<std::string> parties, int& latest_ID);
	/// <summary>
	/// Stores information on an area of voters
	/// </summary>
	/// <param name="initial_voters"> voters to store information on</param>
	PopulationCell(std::vector<Voter>& initial_voters);
	// Returns lean of this population cell
	std::string getLean();
	// Returns the number of votes for each party
	std::map<std::string, unsigned int> getCounts();
	// Returns number of voters in this cell
	unsigned int getSize();
	// Returns vector of voters in this cell
	std::vector<Voter> getVoters();
	/// <summary>
	/// Forms double link between this cell and another
	/// </summary>
	/// <param name="population_cell"> pointer to cell to link this cell with</param>
	void linkPopulationCell(PopulationCell* population_cell);
	// Index of this cell in population grid
	unsigned int grid_index;
	// Index of the district this cell is associated with
	unsigned int district_index;
};
/// <summary>
/// Prints the lean of each cell in the population grid
/// </summary>
/// <param name="population"> population grid to print</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
/// <param name="path"> path to output to, by default it is empty (will output to this directory)</param>
/// <param name="suffix"> suffix to add to file name, by default it is empty</param>
void outputPopulationGridLean(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path = "", std::string suffix = "");
/// <summary>
/// Prints the number of voters in each cell in the population grid
/// </summary>
/// <param name="population"> population grid to print</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
/// <param name="path"> path to output to, by default it is empty (will output to this directory)</param>
/// <param name="suffix"> suffix to add to file name, by default it is empty</param>
void outputPopulationGridSize(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path = "", std::string suffix = "");
/// <summary>
/// Generates a population grid with a random voters distributed uniformly
/// </summary>
/// <param name="max_population"> max number of voters any cell can contain</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
/// <param name="parties"> distribution of parties to randomly affiliate voters with</param>
/// <param name="seed"> seed to use in random generation</param>
/// <returns> generated population grid</returns>
std::vector<PopulationCell> genPopGridUniformRandom(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, unsigned int seed = time(0));
/// <summary>
/// Generates a population grid with a random voters distributed around a center cell
/// <param name="max_population"> max number of voters any cell can contain</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
/// <param name="parties"> distribution of parties to randomly affiliate voters with</param>
/// <param name="seed"> seed to use in random generation</param>
/// <param name="density"> how densely populated the urban center should be (1.0 scale)</param>
/// <returns></returns>
std::vector<PopulationCell> genPopGridUrbanCenter(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, unsigned int seed = time(0), double density = 0.7);
/// <summary>
/// Outputs the lean of each cell in the population grid to the console
/// </summary>
/// <param name="grid"> population grid to print</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
void printPopulationLean(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
/// <summary>
/// Outputs the grid index of each cell in the population grid to the console
/// </summary>
/// <param name="grid"> population grid to print</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
void printPopulationIndex(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
/// <summary>
/// Outputs the number of voters in each cell in the population grid to the console
/// </summary>
/// <param name="grid"> population grid to print</param>
/// <param name="num_rows"> number of rows in the grid</param>
/// <param name="num_cols"> number of columns in the grid</param>
void printPopulationDensity(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols);
/// <summary>
/// Counts the number of voters in a populaton grid
/// </summary>
/// <param name="population"> population grid to count voters in</param>
/// <returns> numbre of votes in the population grid</returns>
unsigned int getPopulationSize(std::vector<PopulationCell>& population);
/// <summary>
/// Counts the number of votes for each party in the population grid
/// </summary>
/// <param name="population"> population grid to count voters in</param>
/// <returns> map of party affiliations and their respective number of affiliated voters in the population grid</returns>
std::map<std::string, unsigned int> getPopularAffiliationCounts(std::vector<PopulationCell>& population);

#endif