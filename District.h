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
	// Code for party with most votes
	std::string major_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	unsigned int major_party_count = 0;
	// Code for party with second most votes
	std::string minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	unsigned int minor_party_count = 0;


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
	unsigned int majority();
	// Returns minority count
	unsigned int minority();


	// Returns map of party (first value) to the number of affiliated voters (second value)
	std::map<std::string, unsigned int> getAffiliationCounts();

	// Outputs data on district for debugging
	std::string print();

};
#endif

