/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"
#include <iostream>

// Creates two-party district with specified distribution
District createDistrict(std::string major_party_code, int major_party_count, std::string minor_party_code, int minor_party_count) {
	// Keep track of next voter ID
	int next_unique_id = 1;
	// Create vector to store voters in
	std::vector<Voter> voters;
	// Reserve memory
	voters.reserve(major_party_count + minor_party_count);

	// Add major party voters
	for (int index = 0; index < major_party_count; index++) {
		Voter voter(major_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Add minor party voters
	for (int index = 0; index < minor_party_count; index++) {
		Voter voter(minor_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Return filled-district
	District ret(voters);
	return ret;
}

int main() {

	// Create a districting
	Districting districting({
		createDistrict(VOTER_AFFILIATION_A, 12, VOTER_AFFILIATION_B, 25),
		createDistrict(VOTER_AFFILIATION_A, 5, VOTER_AFFILIATION_B, 19),
		createDistrict(VOTER_AFFILIATION_A, 65, VOTER_AFFILIATION_B, 17)
		});

	std::cout << "During the election in this districting, " << districting.total() << " voters participated" << std::endl;
	std::cout << "This distrcting leans towards Party " << districting.lean() << " by " << districting.majority() << " districts" << std::endl;
	std::cout << "But has a popular vote of " << districting.popular() << " in favor of Party " << districting.leanPopular() << std::endl;
	std::cout << "This means the popular voting margin is " << districting.total() - districting.popular() << " votes" << std::endl;


	return 0;
}