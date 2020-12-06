#include "Voter.h"

Voter::Voter(std::string party_affiliation_code, int unique_id) : affiliation(party_affiliation_code), id(unique_id) {}
std::string Voter::getAffiliationCode() {
	return affiliation;
}
int Voter::getID() {
	return id;
}