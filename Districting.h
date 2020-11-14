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
	int major_party_code;
	// Number of voters affiliated with major party
	int major_party_count;
	// Code for party with second most votes
	int minor_party_code;
	// Number of voters affiliated with minor party
	int minor_party_count;

public:
	// Create district from a single voter
	Districting(District district_);
	// Create district from collection of voters
	Districting(std::vector<District> districts_);

	// Updates districting stats
	void updateStats();
	// Returns popular affiliation of districts
	int lean();
	// Returns majority count
	int majority();
	// Returns minority count
	int minority();
	// Used for debugging
	std::string print();
};
#endif
