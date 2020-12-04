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

	// Count all the votes for each party affiliation
	updateAffiliationCounts();

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
			first_party_count = party.second;
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
	return affiliation_counts;
}
std::string District::print() {
	std::stringstream stream;
	for (auto& voter : voters) {
		stream << "==== Data for District " << ID << " ====" << std::endl;
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
// Creates two-party district with specified distribution
District createDistrict(std::string major_party_code, unsigned int major_party_count, std::string minor_party_code, unsigned int minor_party_count) {
	// Keep track of next voter ID
	int next_unique_id = 1;
	// Create vector to store voters in
	std::vector<Voter> voters;
	// Reserve memory
	voters.reserve(major_party_count + minor_party_count);

	// Add major party voters
	for (unsigned int index = 0; index < major_party_count; index++) {
		Voter voter(major_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Add minor party voters
	for (unsigned int index = 0; index < minor_party_count; index++) {
		Voter voter(minor_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Return filled-district
	District ret(voters);
	return ret;
}