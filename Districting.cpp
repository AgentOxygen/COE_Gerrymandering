#include "Districting.h"


Districting::Districting(std::vector<District>& districts_) {
	districts = districts_;
	updateStats();
}
Districting::Districting(District& district_) {
	districts.push_back(district_);
	updateStats();
}
void Districting::updateStats() {
	// Map of party (first value) to the number of affiliated voters (second value)
	std::map<int, unsigned int> affiliation_counts;

	// Cycle through all voters and count the number of voters in each party
	for (auto& district : districts) {
		affiliation_counts[district.lean()] += 1;
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
int Districting::lean() {
	return major_party_code;
}
int Districting::majority() {
	return major_party_count;
}
int Districting::minority() {
	return minor_party_count;
}
std::string Districting::printDistricts() {
	std::stringstream stream;
	stream << "Listing Districts..." << std::endl;
	for (auto& district : districts) {
		stream << district.printVoters();
	}
	return stream.str();
}