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
	std::map<std::string, unsigned int> affiliation_counts = getAffiliationCounts();

	// Initialize stats
	major_party_code = VOTER_AFFILIATION_UNDECIDED;
	major_party_count = 0;
	minor_party_code = VOTER_AFFILIATION_UNDECIDED;
	minor_party_count = 0;

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
		// If a party with less voters is found
		else if (minor_party_count < party.second) {
			minor_party_code = party.first;
			minor_party_count = party.second;
		}
	}
}
unsigned int District::getNumberOfVoters() {
	return voters.size();
}
std::string District::lean() {
	return major_party_code;
}
unsigned int District::majority() {
	return major_party_count;
}
unsigned int District::minority() {
	return minor_party_count;
}
std::map<std::string, unsigned int> District::getAffiliationCounts() {
	std::map<std::string, unsigned int> affiliation_counts;

	// Cycle through all voters and count the number of voters in each party
	for (auto& voter : voters) {
		affiliation_counts[voter.getAffiliationCode()] += 1;
	}
	return affiliation_counts;
}
std::string District::print() {
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