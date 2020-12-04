#include "PopulationCell.h"

PopulationCell::PopulationCell(unsigned int size, std::vector<std::string> parties, int& latest_ID) {
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
	first_party_code = VOTER_AFFILIATION_UNDECIDED;
	first_party_count = 0;
	second_party_code = VOTER_AFFILIATION_UNDECIDED;
	second_party_count = 0;

	// Cycle through parties and compare counts
	for (auto& party : affiliation_counts) {
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
			second_party_count = party.second;
		}
	}
}
std::string PopulationCell::lean() {
	return first_party_code;
}
std::string PopulationCell::getSecondPartyCode() {
	return second_party_code;
}
unsigned int PopulationCell::getSecondPartyCount() {
	return second_party_count;
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

void outputPopulationCells(std::vector<PopulationCell>& population, unsigned int width, unsigned int height, std::string path) {
	std::ofstream pfile(path + "party_output.txt");
	if (pfile.is_open()) {
		for (unsigned int i = 0; i < height; i++) {
			for (unsigned int j = 0; j < width; j++) {
				unsigned int loc = i * width + j;
				pfile << int(population[loc].lean()[0]);
				if(j != width -1) pfile << " ";
			}
			pfile << "\n";
		}
		pfile.close();
	}
}

// Generates and returns an initialized population grid
std::vector<PopulationCell> genPopGrid(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, std::string rand_majority) {
	// Create 2D grid of population cells
	std::vector<PopulationCell> grid;

	int latest_ID = 0;

	std::srand(time(NULL));

	// Initialize grid
	for (unsigned int row = 0; row < num_rows; row++) {
		for (unsigned int col = 0; col < num_cols; col++) {

			std::string major = parties[std::rand() % parties.size()];

			if (rand_majority != "") {
				major = rand_majority;
			}

			PopulationCell cell(std::rand() % max_population, parties, latest_ID);

			grid.push_back(cell);
		}
	}
	return grid;
}
// Output population grid to console
void printPopulationGrid(std::vector<PopulationCell> grid, unsigned int row, unsigned int col) {
	for (unsigned int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < col; j++) {
			unsigned int loc = i * col + j;
			std::cout << std::setw(3) << grid[loc].lean() << " ";
		}
		std::cout << std::endl;
	}
}