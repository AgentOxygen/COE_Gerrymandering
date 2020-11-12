#include "District.h"

District::District(Voter voter_) : major_party_code(voter_.getAffiliationCode()), major_party_count(1) {
	voters.push_back(voter_);
}
District::District(std::vector<Voter> voters_) {
	voters = voters_;
}
void District::updateStats() {
	// Map of party (first value) to the number of affiliated voters (second value)
	std::map<int, unsigned int> affiliation_counts;

	// Cycle through all voters and count the number of voters in each party
	for (auto& voter : voters) {
		affiliation_counts[voter.getAffiliationCode()] += 1;
	}

	// Initialize stats
	major_party_code = -1;
	major_party_count = -1;
	minor_party_code = -1;
	minor_party_count = -1;

	// Cycle through parties and compare counts
	for (auto& party : affiliation_counts) {
		// If a party with more voters is found
		if (major_party_count < party.second) {
			// Minor party is second largest party
			minor_party_code = major_party_code;
			minor_party_count = major_party_count;
			// Major party is the largest party
			major_party_code = party.first;
			major_party_count = party.second;
		}
	} //FIX THIS
}
int District::getNumberOfVoters() {
	return voters.size();
}
int District::lean() {
	return major_party_code;
}
int District::majority() {
	return major_party_count;
}
int District::minority() {
	return minor_party_count;
}
std::string District::print() {
	for (auto& voter : voters) {
		std::cout << "Listing voters..." << std::endl;
		std::cout << voter.getID() << " leans towards ";
		if (voter.affiliatesWithA()) {
			std::cout << "'Party A'" << std::endl;
		} else if (voter.affiliatesWithB()) {
			std::cout << "'Party B'" << std::endl;
		} else if (voter.undecided()) {
			std::cout << "'Undecided'" << std::endl;
		} else if (voter.weird()){
			std::cout << "'Weird'" << std::endl;
		}
	}
}