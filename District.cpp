#include "District.h"

District::District(Voter voter_) : major_party_code(voter_.getAffiliationCode()), major_party_count(1) {
	voters.push_back(voter_);
	updateStats();
}
District::District(std::vector<Voter> voters_) {
	voters = voters_;
	updateStats();
}
void District::updateStats() {
	// Map of party (first value) to the number of affiliated voters (second value)
	std::map<int, unsigned int> affiliation_counts;

	// Cycle through all voters and count the number of voters in each party
	for (auto& voter : voters) {
		affiliation_counts[voter.getAffiliationCode()] += 1;
	}

	// Initialize stats
	int major_party_code = VOTER_AFFILIATION_UNDECIDED;
	int major_party_count = 0;
	int minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	int minor_party_count = 0;

	// Cycle through parties and compare counts
	for (auto& party : affiliation_counts) {
		// If a party with more voters is found than the majority
		if (major_party_count < party.second) {
			// Minor party is second largest party
			minor_party_code = major_party_code;
			minor_party_count = major_party_count;
			// Major party is the largest party
			major_party_code = party.first;
			major_party_count = party.second;
			// If the party isn't larger than the majority but still larger than the minority
		} else if (minor_party_count < party.second) {
			minor_party_code = major_party_code;
			minor_party_count = major_party_count;
		}
	}
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
std::string District::printVoters() {
	std::stringstream stream;
	for (auto& voter : voters) {
		stream << "Listing voters..." << std::endl;
		stream << voter.getID() << " leans towards ";
		if (voter.affiliatesWithA()) {
			stream << "'Party A'" << std::endl;
		} else if (voter.affiliatesWithB()) {
			stream << "'Party B'" << std::endl;
		} else if (voter.undecided()) {
			stream << "'Undecided'" << std::endl;
		} else if (voter.weird()){
			stream << "'Weird'" << std::endl;
		}
	}
	return stream.str();
}