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

std::vector<std::vector<unsigned int>> getCombos() {
	return {
		{0, 1, 2, 3},
		{0, 1, 3, 2},
		{0, 2, 1, 3},
		{0, 2, 3, 1},
		{0, 3, 2, 1},
		{0, 3, 1, 2},
		{1, 2, 3, 0},
		{1, 2, 0, 3},
		{1, 3, 2, 0},
		{1, 3, 0, 2},
		{1, 0, 3, 2},
		{1, 0, 2, 3},
		{2, 1, 0, 3},
		{2, 1, 3, 0},
		{2, 3, 1, 0},
		{2, 3, 0, 1},
		{2, 0, 3, 1},
		{2, 0, 1, 3},
		{3, 2, 0, 1},
		{3, 2, 1, 0},
		{3, 1, 2, 0},
		{3, 1, 0, 2},
		{3, 0, 1, 2},
		{3, 0, 2, 1}
	};
}

// First algorithm
int algo1(std::vector<PopulationCell> grid, std::vector<int>& districtID, unsigned int num_rows, unsigned int num_cols) {
	int num_changes = 0;
	std::vector<std::vector<unsigned int>> combos = getCombos();
	std::vector<unsigned int> sequence = combos[std::rand() % combos.size()];

	for (auto& operation : sequence) {
		switch (operation) {
		case 0:
			// l -> r
			for (unsigned int row = 0; row < num_rows; row++) {
				for (unsigned int col = 0; col < num_cols; col++) {
					if (col != (num_cols - 1)) {
						if (grid[row * num_cols + col].lean() == grid[row * num_cols + col + 1].lean()
							&& districtID[row * num_cols + col + 1] != districtID[row * num_cols + col]) {
							districtID[row * num_cols + col + 1] = districtID[row * num_cols + col];
							num_changes++;
						}
					}
				}
			}
			break;

		case 1:
			// t -> b
			for (unsigned int col = 0; col < num_cols; col++) {
				for (unsigned int row = 0; row < num_rows; row++) {
					if (row != (num_rows - 1)) {
						if (grid[row * num_cols + col].lean() == grid[(row + 1) * num_cols + col].lean()
							&& districtID[(row + 1) * num_cols + col] != districtID[row * num_cols + col]) {
							districtID[(row + 1) * num_cols + col] = districtID[row * num_cols + col];
							num_changes++;
						}
					}
				}
			}
			break;

		case 2:
			// r -> l
			for (unsigned int row = 0; row < num_rows; row++) {
				for (int col = num_cols - 1; col >= 0; col--) {
					if (col != 0) {
						if (grid[row * num_cols + col].lean() == grid[row * num_cols + col - 1].lean()
							&& districtID[row * num_cols + col - 1] != districtID[row * num_cols + col]) {
							districtID[row * num_cols + col - 1] = districtID[row * num_cols + col];
							num_changes++;
						}
					}
				}
			}
			break;

		case 3:
			// b -> t
			for (unsigned int col = 0; col < num_cols; col++) {
				for (int row = num_rows - 1; row >= 0; row--) {
					if (row != 0) {
						if (grid[row * num_cols + col].lean() == grid[(row - 1) * num_cols + col].lean()
							&& districtID[(row - 1) * num_cols + col] != districtID[row * num_cols + col]) {
							districtID[(row - 1) * num_cols + col] = districtID[row * num_cols + col];
							num_changes++;
						}
					}
				}
			}
			break;
		}
	}
	
	return num_changes;
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

	/* Creating continuous districts of the same identifier "A, B, C"
	*  In each iteration, keep track of num of changes 'n'
	*                     l->r     t->b     r->l     b->t
	*                     n=2      n=4      n=1      n=0
	   A A B    1 2 3    1 1 3    1 1 3    1 1 3    1 1 3
	   A C B -> 4 5 6 -> 4 5 6 -> 1 5 3 -> 1 5 3 -> 1 5 3
	   C C B    7 8 9    7 7 9    7 5 3    5 5 3    5 5 3
	*/

	// Make ID's for each PopulationCell
	int id = 0;
	for (auto& cell : grid) {
		districtID[id] = id;
		id++;
	}

	/**
	unsigned int count = 0;
	while (count < 20) {
		int num = algo1(grid, districtID, num_rows, num_cols);
		if(num == 0) count++;
		else count = 0;
		std::cout << num << std::endl;
	}
	*/

	algo2(grid, districtID, num_rows, num_cols);
	printGrid(grid, num_rows, num_cols);
	printGridID(districtID, num_rows, num_cols);


	std::ofstream dfile("district_output.txt");
	if (dfile.is_open()) {
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_cols; j++) {
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
		for (int i = 0; i < num_rows; i++) {
			for (int j = 0; j < num_cols; j++) {
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


/* Create a districting
	Districting districting({
		createDistrict(VOTER_AFFILIATION_A, 12, VOTER_AFFILIATION_B, 25),
		createDistrict(VOTER_AFFILIATION_A, 5, VOTER_AFFILIATION_B, 19),
		createDistrict(VOTER_AFFILIATION_A, 65, VOTER_AFFILIATION_B, 17)
		});

	std::cout << "During the election in this districting, " << districting.total() << " voters participated" << std::endl;
	std::cout << "This distrcting leans towards Party " << districting.lean() << " by " << districting.majority() << " districts" << std::endl;
	std::cout << "But has a popular vote of " << districting.popular() << " in favor of Party " << districting.leanPopular() << std::endl;
	std::cout << "This means the popular voting margin is " << districting.total() - districting.popular() << " votes" << std::endl;




	// l -> r
		for (unsigned int row = 0; row < num_rows; row++) {
			for (unsigned int col = 0; col < num_cols; col++) {
				if (col != (num_cols - 1)) {
					if (grid[row * num_cols + col].lean() == grid[row * num_cols + col + 1].lean()
						&& districtID[row * num_cols + col + 1] != districtID[row * num_cols + col]) {
						districtID[row * num_cols + col + 1] = districtID[row * num_cols + col];
						num_changes++;
					}
				}
			}
		}

		// t -> b
		for (unsigned int col = 0; col < num_cols; col++) {
			for (unsigned int row = 0; row < num_rows; row++) {
				if (row != (num_rows - 1)) {
					if (grid[row * num_cols + col].lean() == grid[(row + 1) * num_cols + col].lean()
						&& districtID[(row + 1) * num_cols + col] != districtID[row * num_cols + col]) {
						districtID[(row + 1) * num_cols + col] = districtID[row * num_cols + col];
						num_changes++;
					}
				}
			}
		}
		// r -> l
		for (unsigned int row = 0; row < num_rows; row++) {
			for (int col = num_cols - 1; col >= 0; col--) {
				if (col != 0) {
					if (grid[row * num_cols + col].lean() == grid[row * num_cols + col - 1].lean()
						&& districtID[row * num_cols + col - 1] != districtID[row * num_cols + col]) {
						districtID[row * num_cols + col - 1] = districtID[row * num_cols + col];
						num_changes++;
					}
				}
			}
		}
		// b -> t
		for (unsigned int col = 0; col < num_cols; col++) {
			for (int row = num_rows - 1; row >= 0; row--) {
				if (row != 0) {
					if (grid[row * num_cols + col].lean() == grid[(row - 1) * num_cols + col].lean()
						&& districtID[(row - 1) * num_cols + col] != districtID[row * num_cols + col]) {
						districtID[(row - 1) * num_cols + col] = districtID[row * num_cols + col];
						num_changes++;
					}
				}
			}
		}




	*/