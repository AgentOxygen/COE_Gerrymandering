#include "District.h"

District::District(Voter voter_) : first_party_code(voter_.getAffiliationCode()), first_party_count(1) {
	voters.push_back(voter_);
	updateStats();
}
District::District(std::vector<Voter> voters_) {
	voters = voters_;
	updateStats();
}
void District::updateStats() {
	// Initialize stats
	first_party_code = VOTER_AFFILIATION_UNDECIDED;
	first_party_count = 0;
	second_party_code = VOTER_AFFILIATION_UNDECIDED;
	second_party_count = 0;

	// Cycle through parties and compare counts
	for (auto& party : getAffiliationCounts()) {
		// If a party with more voters is found
		if (first_party_count < party.second) {
			// Minor party is second largest party
			second_party_code = first_party_code;
			second_party_count = first_party_count;
			// Major party is the largest party
			first_party_code = party.first;
			first_party_count = party.second;
		}
		// If a party with less voters is found
		else if (second_party_count < party.second) {
			second_party_code = party.first;
			second_party_count = party.second;
		}
	}
}
unsigned int District::getNumberOfVoters() {
	return voters.size();
}
std::string District::lean() {
	return first_party_code;
}
unsigned int District::firstPartyCount() {
	return first_party_count;
}
unsigned int District::secondPartyCount() {
	return second_party_count;
}
void District::updateAffiliationCounts() {
	affiliation_counts.clear();

	// Cycle through all voters and count the number of voters in each party
	for (auto& voter : voters) {
		affiliation_counts[voter.getAffiliationCode()] += 1;
	}
}
std::map<std::string, unsigned int> District::getAffiliationCounts() {
	updateAffiliationCounts();
	return affiliation_counts;
}
std::vector<Voter> District::getVoters() {
	return voters;
}