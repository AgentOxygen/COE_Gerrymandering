/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"
#include <iostream>

int main() {

	Voter voter1(VOTER_AFFILIATION_UNDECIDED, 1);
	Voter voter2(VOTER_AFFILIATION_UNDECIDED, 1);
	Voter voter3(VOTER_AFFILIATION_UNDECIDED, 1);
	Voter voter4(VOTER_AFFILIATION_UNDECIDED, 1);
	Voter voter5(VOTER_AFFILIATION_UNDECIDED, 1);

	std::vector<Voter> voters = { voter1, voter2, voter3, voter4, voter5 };

	District district(voters);
	Districting districting(district);

	std::cout << districting.printDistricts();

	return 0;
}