#ifndef GERRYMANDERING_DISTRICT
#define GERRYMANDERING_DISTRICT

#include "Voter.h"
#include <sstream>
#include <vector>
#include <string>
#include <map>

class District {
private:
	// Collection of voters in this district
	std::vector<Voter> voters;
	// ================== District statistics ==================
	// ID of this district (-1 default indicates an initialization error)
	int ID = -1;
	// Code for party with most votes
	std::string first_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	unsigned int first_party_count = 0;
	// Code for party with second most votes
	std::string second_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	unsigned int second_party_count = 0;
	// Map of parties to their respective count
	std::map<std::string, unsigned int> affiliation_counts;

	// Updates affiliation_counts map
	void updateAffiliationCounts();
public:
	// Create district from a single voter
	District(Voter voter_);
	// Create district from collection of voters
	District(std::vector<Voter> voters_);

	// Updates district statistics 
	void updateStats();
	// Returns the number of voters in this district
	unsigned int getNumberOfVoters();
	// Returns popular affiliation of voters in district
	std::string lean();
	// Returns majority count
	unsigned int firstPartyCount();
	// Returns minority count
	unsigned int secondPartyCount();

	// Returns map of party (first value) to the number of affiliated voters (second value)
	std::map<std::string, unsigned int> getAffiliationCounts();

	// Outputs data on district for debugging
	std::string print();

};
#endif

