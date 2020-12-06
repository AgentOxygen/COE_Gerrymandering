#ifndef GERRYMANDERING_VOTER
#define GERRYMANDERING_VOTER
#include <string>
#include <vector>

const std::string VOTER_AFFILIATION_UNDECIDED = "U";
const std::string VOTER_AFFILIATION_A = "A";
const std::string VOTER_AFFILIATION_B = "B";

class Voter {
private:
	// Voter affiliation definied by one of the constants
	std::string affiliation;
	// Voter ID
	int id;
public:
	Voter(std::string party_affiliation_code, int unique_id);
	// Returns ID of voter
	int getID();
	// Returns code of party this voter is affiliated with
	std::string getAffiliationCode();
	// Returns whether or not this voter is undecided
	bool undecided();
	// Returns whether or not this voter is affiliated with party "B"
	bool affiliatesWithB();
	// Returns whether or not this voter is affiliated with party "A"
	bool affiliatesWithA();
	// Returns whether or not this voter is weird (doesn't have appropriate affiliation)
	bool weird();
};
#endif
