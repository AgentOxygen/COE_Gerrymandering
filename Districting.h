#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING
#include "District.h"
#include <vector>
class Districting {
private:
	std::vector<District> districts;

	// ================== Districting statistics ==================
	// Code for party with most votes
	int major_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with major party
	int major_party_count = 0;
	// Code for party with second most votes
	int minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	// Number of voters affiliated with minor party
	int minor_party_count = 0;

	// Updates districting statistics 
	void updateStats();
public:
	Districting(std::vector<District>& districts_);
	Districting(District& district_);
	// Returns popular affiliation of districts
	int lean();
	// Returns majority count
	int majority();
	// Returns minority count
	int minority();
	// Returns string containing output for districts in this districting
	std::string printDistricts();
};
#endif
