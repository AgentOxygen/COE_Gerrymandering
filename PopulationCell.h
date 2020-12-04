#ifndef GERRYMANDERING_POPULATION
#define GERRYMANDERING_POPULATION
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include "Voter.h"
#include <iostream>
#include <iomanip>

class PopulationCell {
private:
	// Voters in this population cell
	std::vector<Voter> voters;
	// Number of votes for each party
	std::map<std::string, unsigned int> counts;
	// Code for party with most votes
	std::string first_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	unsigned int first_party_count = 0;
	// Code for party with second most votes
	std::string second_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	unsigned int second_party_count = 0;

public:
	// Generates population cell with "size" number of random voters using specified parties distribution (randomly selects from "parties" vector)
	// "latest_id" refers to the last ID used to create a voter. This insures that no duplicate voters are created with the same ID across the entire project
	PopulationCell(unsigned int size, std::vector<std::string> parties, int& latest_ID);
	// Creates population cell from specified initial voters
	PopulationCell(std::vector<Voter> initial_voters);

	// Updates population statistics
	void updateStats();

	// Returns lean of this population cell
	std::string lean();
	// Returns code of second most popular party
	std::string getSecondPartyCode();
	// Returns number of votes for second most popular party
	unsigned int getSecondPartyCount();

	// Adds specified voter and returns whether or not it was successful in doing so (Voters cannot have same ID)
	bool addVoter(Voter voter_to_add);
	// Removes voter by ID and returns whether or not it was successful in doing so (can't remove Voter if one with specified ID doesn't exist)
	bool removeVoterByID(int id);
};


// Outputs population cells to a text file
void outputPopulationCells(std::vector<PopulationCell>& population, unsigned int width, unsigned int height, std::string path = "");
// Generates population grid
std::vector<PopulationCell> genPopGrid(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, std::string rand_majority = "");
// Outputs population cells to the console
void printPopulationGrid(std::vector<PopulationCell> grid, unsigned int row, unsigned int col);
#endif
