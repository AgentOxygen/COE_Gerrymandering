#include "PopulationCell.h"
#include <iostream>

PopulationCell::PopulationCell(unsigned int size, std::string major_party, std::vector<std::string> all_parties, int& latest_ID) {
    
    // Create vector will all parties in it
    std::vector<std::string> parties = all_parties;
    parties.push_back(major_party);

    // Add other voters randomly
    for (int index = 0; voters.size() <= size; index++) {
        latest_ID++;

        Voter voter(parties[std::rand() % parties.size()], latest_ID);

        voters.push_back(voter);
    }

    updateStats();
}
PopulationCell::PopulationCell(std::vector<Voter> initial_voters) {
    voters = initial_voters;
    updateStats();
}
void PopulationCell::updateStats() {
    // Map of party (first value) to the number of affiliated districts (second value)
    std::map<std::string, unsigned int> affiliation_counts;

    // Cycle through all voters and count the number of voters in each party
    for (auto& voter : voters) {
        affiliation_counts[voter.getAffiliationCode()] += 1;
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
}
std::string PopulationCell::lean() {
    return major_party_code;
}
bool PopulationCell::addVoter(Voter voter_to_add) {

    // Checks if the new voter is a copy of an already-existing voter
    for(auto &v: voters) {
        if(v.getID() == voter_to_add.getID()) {
            return false;
        }
    }
    
    // If new voter, add to voter
    voters.push_back(voter_to_add);
    
    // If voter was added - True
    return true;
}
bool PopulationCell::removeVoterByID(int id) {
    unsigned int index = 0;
    
    // Checks if the ID exists in the voter group
    for (auto& v : voters) {
        if (v.getID() == id) {
            voters.erase(voters.begin() + index);
            return true;
        }
        index++;
    }
    return false;
}
