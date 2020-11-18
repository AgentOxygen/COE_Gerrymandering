#ifndef GERRYMANDERING_VOTER
#define GERRYMANDERING_VOTER

const int VOTER_AFFILIATION_A = 1;
const int VOTER_AFFILIATION_B = 2;
const int VOTER_AFFILIATION_UNDECIDED = 3;

class Voter {
private:
	// Voter affiliation definied by one of the constants
	int affiliation;
	// Voter ID
	int id;
public:
	Voter(int party_affiliation_code, int unique_id);
	// Returns ID of voter
	int getID();
	// Returns code of party this voter is affiliated with
	int getAffiliationCode();
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
