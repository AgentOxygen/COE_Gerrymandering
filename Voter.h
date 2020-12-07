#ifndef GERRYMANDERING_VOTER
#define GERRYMANDERING_VOTER
#include <string>
#include <vector>

const std::string VOTER_AFFILIATION_UNDECIDED = "U";

class Voter {
private:
	// Voter affiliation definied by one of the constants
	std::string affiliation;
	// Voter ID
	int id;
public:
	/// <summary>
	/// Stores voter ID and affiliation
	/// </summary>
	/// <param name="party_affiliation_code"> Code of party that this voter is affiliated with</param>
	/// <param name="unique_id"> The unique ID of this voter</param>
	Voter(std::string party_affiliation_code, int unique_id);
	// Returns ID of voter
	int getID();
	// Returns code of party this voter is affiliated with
	std::string getAffiliationCode();
};
#endif
