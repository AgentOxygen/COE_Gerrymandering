#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING

#include "District.h"
#include "PopulationCell.h"
#include <fstream>

class Districting {
private:

	unsigned int pop_grid_width;
	unsigned int pop_grid_height;

	std::vector<District> districts;
	std::vector<unsigned int> districting_id;

	void districtLean(std::vector<PopulationCell>& population);
	void districtMajority(std::vector<PopulationCell>& population, std::string run_off);
	void districtTarget(std::vector<PopulationCell>& population, std::string target_party);

public:
	// Generate Districting out of provided population
	// population -> population cells to generate districts from
	// width -> number of columns in the population grid
	// height -> number of rows in the population grid
	// algorithm -> algorithm to use: (1) Majority   (2) Targeting   (Default/0) Lean
	// args -> arguments to pass to either majority or targeting algorithms
	Districting(std::vector<PopulationCell> population, unsigned int width, unsigned int height, int algorithm = 0, std::string args = "");

	std::vector<District> getDistricts();
	std::vector<unsigned int> getDistricting();

	// Output districting array to a text file
	void outputDistricting(std::string path);
};

void printDistrictIDGrid(std::vector<unsigned int> grid, unsigned int row, unsigned int col);
#endif


/*

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

*/
