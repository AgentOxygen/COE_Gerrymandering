#ifndef GERRYMANDERING_POPULATION
#define GERRYMANDERING_POPULATION
#include <vector>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Voter.h"

class PopulationCell {
private:
	// Voters in this population cell
	std::vector<Voter> voters;
	// Number of votes for each party
	std::map<std::string, unsigned int> counts;
	// Code for party with most votes
	std::string major_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	unsigned int major_party_count = 0;
	// Code for party with second most votes
	std::string minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	unsigned int minor_party_count = 0;

public:
	// Generates population cell based on criteria
	// "latest_id" refers to the last ID used to create a voter. This insures that no duplicate voters are created with the same ID across the entire project
	PopulationCell(unsigned int size, std::string major_party, std::vector<std::string> other_parties, int& latest_ID);
	// Creates population cell from specified initial voters
	PopulationCell(std::vector<Voter> initial_voters);

	// Updates population statistics
	void updateStats();

	// Returns lean of this population cell
	std::string lean();

	// Adds specified voter and returns whether or not it was successful in doing so (Voters cannot have same ID)
	bool addVoter(Voter voter_to_add);
	// Removes voter by ID and returns whether or not it was successful in doing so (can't remove Voter if one with specified ID doesn't exist)
	bool removeVoterByID(int id);
};
#endif
