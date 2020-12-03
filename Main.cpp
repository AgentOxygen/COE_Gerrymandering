/*
* Github: https://github.com/AgentOxygen/COE_Gerrymandering
*/
#include "Districting.h"
#include "PopulationCell.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>

// Creates two-party district with specified distribution
District createDistrict(std::string major_party_code, int major_party_count, std::string minor_party_code, int minor_party_count) {
	// Keep track of next voter ID
	int next_unique_id = 1;
	// Create vector to store voters in
	std::vector<Voter> voters;
	// Reserve memory
	voters.reserve(major_party_count + minor_party_count);

	// Add major party voters
	for (int index = 0; index < major_party_count; index++) {
		Voter voter(major_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Add minor party voters
	for (int index = 0; index < minor_party_count; index++) {
		Voter voter(minor_party_code, next_unique_id);
		next_unique_id++;
		voters.push_back(voter);
	}

	// Return filled-district
	District ret(voters);
	return ret;
}

// Generates and returns an initialized population grid
std::vector<PopulationCell> genPopGrid(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, std::string rand_majority = "") {
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

			PopulationCell cell(std::rand() % max_population, major, parties, latest_ID);

			grid.push_back(cell);
		}
	}
	return grid;
}

// Visualize grid for debugging
void printGrid(std::vector<PopulationCell> grid, unsigned int row, unsigned int col) {
	for (int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			unsigned int loc = i*col + j;
			std::cout << std::setw(3) << grid[loc].lean() << " ";
		}
		std::cout << std::endl;
	}
}

void printGridID(std::vector<int> grid, unsigned int row, unsigned int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			unsigned int loc = i * col + j;
			std::cout << std::setw(3) << grid[loc] << " ";
		}
		std::cout << std::endl;
	}
}

int algo2(std::vector<PopulationCell> grid, std::vector<int>& districtID, unsigned int num_rows, unsigned int num_cols) {

	unsigned int index = 0;
	for (auto& cell : grid) {
		unsigned int x = index % num_cols;
		unsigned int y = std::floor(index / num_cols);

		// Check left neighbor
		if (x > 0) {
			if (grid[y*num_rows + x - 1].lean() == cell.lean()) districtID[y * num_rows + x - 1] = districtID[index];
		}
		// Check right neighbor
		if (x < num_cols - 1) {
			if(grid[y * num_rows + x + 1].lean() == cell.lean()) districtID[y * num_rows + x + 1] = districtID[index];
		}
		// Check top neighbor
		if (y > 0) {
			if (grid[(y - 1) * num_cols + x].lean() == cell.lean()) districtID[(y - 1) * num_cols + x] = districtID[index];
		}
		// Check bottom neighbor
		if (y < num_rows - 1) {
			if (grid[(y + 1) * num_cols + x].lean() == cell.lean()) districtID[(y + 1) * num_cols + x] = districtID[index];
		}


		index++;
	}

	return 0;
}
// 
int main() {

	unsigned int num_rows = 10;
	unsigned int num_cols = 10;
	unsigned int max_population = 1000;
	std::vector<std::string> parties = { "A", "B" };

	std::vector<PopulationCell> grid  = genPopGrid(max_population, num_rows, num_cols, parties);
	std::vector<int> districtID(num_rows*num_cols, 0);

	// Make ID's for each PopulationCell
	int id = 0;
	for (auto& cell : grid) {
		districtID[id] = id;
		id++;
	}

	algo2(grid, districtID, num_rows, num_cols);
	printGrid(grid, num_rows, num_cols);
	printGridID(districtID, num_rows, num_cols);


	std::ofstream dfile("district_output.txt");
	if (dfile.is_open()) {
		for (unsigned int i = 0; i < num_rows; i++) {
			for (unsigned int j = 0; j < num_cols; j++) {
				unsigned int loc = i * num_cols + j;
				dfile << districtID[loc];
				if (j != num_cols - 1) dfile << " ";
			}
			dfile << "\n";
		}
		dfile.close();
	}
	std::ofstream pfile("party_output.txt");
	if (pfile.is_open()) {
		for (unsigned int i = 0; i < num_rows; i++) {
			for (unsigned int j = 0; j < num_cols; j++) {
				unsigned int loc = i * num_cols + j;
				pfile << int(grid[loc].lean()[0]) % parties.size();
				if(j != num_cols-1) pfile << " ";
			}
			pfile << "\n";
		}
		pfile.close();
	}

	return 0;
}
