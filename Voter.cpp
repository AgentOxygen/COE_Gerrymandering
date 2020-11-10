#include "Voter.h"

Voter::Voter(int party_affiliation_code, int unique_id) : affiliation(party_affiliation_code), id(unique_id) {}
int Voter::getAffiliationCode() {
	return affiliation;
}
int Voter::getID() {
	return id;
}
bool Voter::undecided() {
	if (affiliation == VOTER_AFFILIATION_UNDECIDED) {
		return true;
	}
	return false;
}
bool Voter::affiliatesWithB() {
	if (affiliation == VOTER_AFFILIATION_B) {
		return true;
	}
	return false;
}
bool Voter::affiliatesWithA() {
	if (affiliation == VOTER_AFFILIATION_A) {
		return true;
	}
	return false;
}
bool Voter::weird() {
	if (!undecided() && !affiliatesWithA() && !affiliatesWithB()) {
		return true;
	}
	return false;
}