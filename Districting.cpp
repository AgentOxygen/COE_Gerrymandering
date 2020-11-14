#include "Districting.h"
Districting::Districting(District district_) {
	districts.push_back(district_);
}
Districting::Districting(std::vector<District> districts_) {
	districts = districts_;
}
void Districting::updateStats() {
    // Map of party (first value) to the number of affiliated voters (second value)
	std::map<int, unsigned int> affiliation_counts;

    for (auto d : districts) {
        // Make sure stats from each district are up-to-date
        d.updateStats();
        // Fill map (assumes only A/B will be majority/minority)
        // If majority A
        if (d.lean() == 1) {
            affiliation_counts[1] += d.majority();
            affiliation_counts[2] += d.minority();
        }
        // If majority B
        else {
            affiliation_counts[2] += d.majority();
            affiliation_counts[1] += d.minority();
        }
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
		} else {
			minor_party_code = party.first;
			minor_party_count = party.second;
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
std::string Districting::print() {
    unsigned int count = 0;
    for (auto& d : districts) {
        count++;
		std::cout << "Listing districts..." << std::endl;
		std::cout << "District " << count << " leans towards ";
		if (d.lean() == 1) {
			std::cout << "'Party A'" << std::endl;
		} else {
			std::cout << "'Party B'" << std::endl;
		}
	}
}