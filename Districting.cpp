#include "Districting.h"

Districting::Districting(std::vector<PopulationCell> population, unsigned int width, unsigned int height, 
	int algorithm, std::string args) : pop_grid_width(width), pop_grid_height(height) {

	switch (algorithm) {
	default:
		districtLean(population);
		break;
	case 1:
		districtMajority(population, args);
		break;
	case 2:
		districtTarget(population, args);
		break;
	}

}
void Districting::districtLean(std::vector<PopulationCell>& population) {
	unsigned int index = 0;
	
	// Initialize districting IDs
	for (auto& cell : population) {
		districting_id.push_back(index);
		index++;
	}

	index = 0;
	for (auto& cell : population) {
		unsigned int x = index % pop_grid_width;
		unsigned int y = std::floor(index / pop_grid_width);

		// ADD CONDITION TO SOLVE BUG:
		// Compare IDs, if the ID of the target is less than the current ID, modify and restart loop? <-- could result in endless

		// Check left neighbor
		if (x > 0) {
			if (population[y * pop_grid_height + x - 1].lean() == cell.lean()) districting_id[y * pop_grid_height + x - 1] = districting_id[index];
		}
		// Check right neighbor
		if (x < pop_grid_width - 1) {
			if (population[y * pop_grid_height + x + 1].lean() == cell.lean()) districting_id[y * pop_grid_height + x + 1] = districting_id[index];
		}
		// Check top neighbor
		if (y > 0) {
			if (population[(y - 1) * pop_grid_width + x].lean() == cell.lean()) districting_id[(y - 1) * pop_grid_width + x] = districting_id[index];
		}
		// Check bottom neighbor
		if (y < pop_grid_height - 1) {
			if (population[(y + 1) * pop_grid_width + x].lean() == cell.lean()) districting_id[(y + 1) * pop_grid_width + x] = districting_id[index];
		}
		index++;
	}
}
void Districting::districtMajority(std::vector<PopulationCell>& population, std::string run_off) {

}
void Districting::districtTarget(std::vector<PopulationCell>& population, std::string target_party) {

}
std::vector<District> Districting::getDistricts() {
	return districts;
}
std::vector<unsigned int> Districting::getDistricting() {
	return districting_id;
}
void Districting::outputDistricting(std::string path = "") {
	std::ofstream dfile(path + "districting_output.txt");
	if (dfile.is_open()) {
		for (unsigned int i = 0; i < pop_grid_width; i++) {
			for (unsigned int j = 0; j < pop_grid_height; j++) {
				unsigned int loc = i * pop_grid_width + j;
				dfile << districting_id[loc];
				if (j != pop_grid_height - 1) dfile << " ";
			}
			dfile << "\n";
		}
		dfile.close();
	}
}

void printDistrictIDGrid(std::vector<unsigned int> grid, unsigned int row, unsigned int col) {
	for (unsigned int i = 0; i < row; i++) {
		for (unsigned int j = 0; j < col; j++) {
			unsigned int loc = i * col + j;
			std::cout << std::setw(3) << grid[loc] << " ";
		}
		std::cout << std::endl;
	}
}
