#include "PopulationCell.h"

PopulationCell::PopulationCell(unsigned int size, std::vector<std::string> parties, int& latest_ID) {
	std::vector<Voter> voters;
	voters.reserve(size);
	// Add other voters randomly
	for (unsigned int index = 0; voters.size() <= size; index++) {
		latest_ID++;
		Voter voter(parties[std::rand() % parties.size()], latest_ID);
		voters.push_back(voter);
	}
	updateStats(voters);
}
PopulationCell::PopulationCell(std::vector<Voter>& initial_voters) {
	updateStats(initial_voters);
}
void PopulationCell::updateStats(std::vector<Voter>& voters_) {
	voters = voters_;
	for (auto& voter : voters) {
		counts[voter.getAffiliationCode()] += 1;
		size++;
	}
	for (auto& count : counts) {
		if (counts[lean] < count.second) lean = count.first;
	}
}
std::string PopulationCell::getLean() {
	return lean;
}
std::map<std::string, unsigned int> PopulationCell::getCounts() {
	return counts;
}
unsigned int PopulationCell::getSize() {
	return size;
}
std::vector<Voter> PopulationCell::getVoters() {
	return voters;
}
void PopulationCell::changeUpstream(unsigned int index) {
	district_index = index;
	if (next != nullptr) next->changeUpstream(index);
}
PopulationCell* PopulationCell::getHead() {
	if (next != nullptr) return next->getHead();
	return this;
}
void PopulationCell::linkPopulationCell(PopulationCell* to_add) {
	if (prior == nullptr) {
		prior = to_add->getHead();
		prior->next = this;
		changeUpstream(to_add->district_index);
	}
	else {
		prior->linkPopulationCell(to_add);
	}
}
void outputPopulationGridLean(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path, std::string suffix) {
	std::ofstream pfile(path + "grid_lean_output_" + suffix + ".txt");
	if (pfile.is_open()) {
		for (unsigned int y = 0; y < num_rows; y++) {
			for (unsigned int x = 0; x < num_cols; x++) {
				unsigned int loc = y * (num_cols) + x;
				pfile << int(population[loc].getLean()[0]) - 65;
				if(x != num_cols - 1) pfile << " ";
			}
			pfile << "\n";
		}
		pfile.close();
	}
}
void outputPopulationGridSize(std::vector<PopulationCell>& population, unsigned int num_rows, unsigned int num_cols, std::string path, std::string suffix) {
	std::ofstream pfile(path + "grid_size_output_" + suffix + ".txt");
	if (pfile.is_open()) {
		for (unsigned int y = 0; y < num_rows; y++) {
			for (unsigned int x = 0; x < num_cols; x++) {
				unsigned int loc = y * (num_cols)+x;
				pfile << int(population[loc].getSize());
				if (x != num_cols - 1) pfile << " ";
			}
			pfile << "\n";
		}
		pfile.close();
	}
}
// Generates and returns an initialized population grid with a uniform distribution
std::vector<PopulationCell> genPopGridUniformRandom(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, unsigned int seed) {
	// Create 2D grid of population cells
	std::vector<PopulationCell> grid;

	int latest_ID = 0;

	std::srand(seed);

	std::cout << "Creating Max Pop (" << max_population << ") Uniform Population" << std::endl;
	std::cout << "Seed: " << seed << std::endl;

	// Initialize grid
	for (unsigned int col = 0; col < num_cols; col++) {
		for (unsigned int row = 0; row < num_rows; row++) {

			PopulationCell cell(std::rand() % max_population, parties, latest_ID);

			grid.push_back(cell);
		}
	}
	return grid;
}
// Generates and returns an initialized population grid with a centered distribution
std::vector<PopulationCell> genPopGridUrbanCenter(unsigned int max_population, unsigned int num_rows, unsigned int num_cols, std::vector<std::string> parties, unsigned int seed, double density) {
	// Create 2D grid of population cells
	std::vector<PopulationCell> grid;

	int latest_ID = 0;

	std::srand(seed);

	int center_x = rand() % num_cols;
	int center_y = rand() % num_rows;
	// Calculate max coordinate differences
	double max_dx = double (num_cols) - (center_x);
	double max_dy = double (num_rows) - (center_y);
	if (max_dx < center_x) {
		max_dx = center_x;
	}
	if (max_dy < center_y) {
		max_dy = center_y;
	}

	std::cout << "Creating a Max Pop(" << max_population << ") Urban-Centered Population at (" << center_x + 1 << ", " << center_y + 1 << ") with a density of " << density << std::endl;
	std::cout << "Seed: " << seed << std::endl;
	// Initialize grid
	for (unsigned int y = 0; y < num_rows; y++) {
		for (unsigned int x = 0; x < num_cols; x++) {

			double dx = std::abs(center_x - int(x));
			double dy = std::abs(center_y - int(y));

			// Calculate percentage, indicative of how close this cell is to the urban center cell
			double cell_pop_percentage = 1 - (std::pow((dx*dx + dy*dy), 0.5) / (std::pow((max_dx* max_dx + max_dy* max_dy + 1), 0.5)));

			// Calculate the max size of the cell
			double max_cell_pop = cell_pop_percentage * max_population;
			// Calculate the min size
			double min_cell_pop = max_cell_pop * density;
			// Get random size within range of min and max
			unsigned int size = std::rand() % int(max_cell_pop - min_cell_pop) + int(min_cell_pop);

			PopulationCell cell(size, parties, latest_ID);

			grid.push_back(cell);
		}
	}
	return grid;
}
// Output population lean to console
void printPopulationLean(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols) {
	for (unsigned int y = 0; y < num_rows; y++) {
		for (unsigned int x = 0; x < num_cols; x++) {
			unsigned int loc = y * num_cols + x;
			std::cout << std::setw(5) << grid[loc].getLean() << " ";
		}
		std::cout << std::endl;
	}
}
// Output population lean to console
void printPopulationDensity(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols) {
	for (unsigned int y = 0; y < num_rows; y++) {
		for (unsigned int x = 0; x < num_cols; x++) {
			unsigned int loc = y * num_cols + x;
			std::cout << std::setw(5) << grid[loc].getSize() << " ";
		}
		std::cout << std::endl;
	}
}
// Output population grid to console
void printPopulationIndex(std::vector<PopulationCell> grid, unsigned int num_rows, unsigned int num_cols) {
	unsigned int index = 0;
	for (unsigned int y = 0; y < num_rows; y++) {
		for (unsigned int x = 0; x < num_cols; x++) {
			unsigned int loc = y * num_cols + x;
			std::cout << std::setw(5) << index << " ";
			index++;
		}
		std::cout << std::endl;
	}
}
unsigned int getPopulationSize(std::vector<PopulationCell>& population) {
	unsigned int size = 0;
	for (auto& cell : population) {
		size += cell.getSize();
	}
	return size;
}
std::map<std::string, unsigned int> getPopularAffiliationCounts(std::vector<PopulationCell>& population) {
	std::map<std::string, unsigned int> counts;
	for (auto& cell : population) {
		for (auto& count : cell.getCounts()) {
			counts[count.first] += count.second;
		}
	}
	return counts;
}