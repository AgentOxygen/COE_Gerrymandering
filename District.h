#ifndef GERRYMANDERING_DISTRICT
#define GERRYMANDERING_DISTRICT

#include "Voter.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

class District {
private:
	// Collection of voters in this district
	std::vector<Voter> voters;
	// ================== District statistics ==================
	// Code for party with most votes
	int major_party_code = -1;
	// Number of voters affiliated with major party
	int major_party_count = -1;
	// Code for party with second most votes
	int minor_party_code = -1;
	// Number of voters affiliated with minor party
	int minor_party_count = -1;

	// Updates district statistics 
	void updateStats();
public:
	// Create district from a single voter
	District(Voter voter_);
	// Create district from collection of voters
	District(std::vector<Voter> voters_);

	// Returns the number of voters in this district
	int getNumberOfVoters();
	// Returns popular affiliation of voters in district
	int lean();
	// Returns majority count
	int majority();
	// Returns minority count
	int minority();
	// Outputs data on district for debugging
	std::string print();

};
#endif

