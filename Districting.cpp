#include "Districting.h"
Districting::Districting(District district_) {
	districts.push_back(district_);
	updateStats();
}
Districting::Districting(std::vector<District> districts_) {
	districts = districts_;
	updateStats();
}
void Districting::updateStats() {
	// Map of party (first value) to the number of affiliated districts (second value)
	std::map<std::string, unsigned int> affiliation_counts;

	// Map of party (first value) to the number of affiliated voters (second value)
	std::map<std::string, unsigned int> popular_affiliation_counts;

	// Cycle through all voters and count the number of voters in each party
	for (auto& district : districts) {
		total_count += district.getNumberOfVoters();
		affiliation_counts[district.lean()] += 1;
		// Get map of all voters to their affiliate parties
		std::map<std::string, unsigned int> district_affiliation_counts = district.getAffiliationCounts();
		for (auto& party : district_affiliation_counts) {
			// Count popular votes for each party
			popular_affiliation_counts[party.first] += party.second;
		}
	}

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

	// Cycle through parties and compare counts for popular votes
	for (auto& party : popular_affiliation_counts) {
		// If a party with more voters is found
		if (popular_party_count < party.second) {
			// Major party is the largest party
			popular_party_code = party.first;
			popular_party_count = party.second;
		}
	}
}
std::string Districting::lean() {
    return major_party_code;
}
unsigned int Districting::majority() {
	return major_party_count;
}
unsigned int Districting::minority() {
    return minor_party_count;
}
std::string Districting::print() {
	std::stringstream stream;
    unsigned int count = 0;
    for (auto& d : districts) {
        count++;
		stream << "Listing districts..." << std::endl;
		stream << "District " << count << " leans towards ";
		if (d.lean() == VOTER_AFFILIATION_A) {
			stream << "'Party A'" << std::endl;
		} else {
			stream << "'Party B'" << std::endl;
		}
	}
	return stream.str();
}
std::string Districting::leanPopular() {
	return popular_party_code;
}
unsigned int Districting::popular() {
	return popular_party_count;
}
unsigned int Districting::total() {
	return total_count;
}