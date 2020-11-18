#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING

#include "District.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

class Districting {
private:
	// collection of districts
	std::vector<District> districts;

	// ================== Districting statistics ==================
	// Code for party with most votes
	std::string major_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	unsigned int major_party_count = 0;
	// Code for party with second most votes
	std::string minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	unsigned int minor_party_count = 0;
	// Code for party with popular vote
	std::string popular_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with the popular party
	unsigned int popular_party_count = 0;
	// Number of voters in total
	unsigned int total_count = 0;

public:
	// Create district from a single voter
	Districting(District district_);
	// Create district from collection of voters
	Districting(std::vector<District> districts_);

	// Updates districting stats
	void updateStats();
	// Returns popular affiliation of districts
	std::string lean();
	// Returns majority district count
	unsigned int majority();
	// Returns minority district count
	unsigned int minority();
	// Returns popular affiliation of voters
	std::string leanPopular();
	// Returns popular party count
	unsigned int popular();
	// Returns total number of voters
	unsigned int total();

	
	// Used for debugging
	std::string print();


};
#endif
