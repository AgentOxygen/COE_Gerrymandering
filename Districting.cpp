#include "Districting.h"

Districting::Districting(std::vector<PopulationCell> population, unsigned int num_rows, unsigned int num_cols,
	int algorithm, std::string args) : pop_num_cols(num_cols), pop_num_rows(num_rows) {

	// Initialize population cells
	for (unsigned int index = 0; index < population.size(); index++) population[index].grid_index = index;

	switch (algorithm) {
	default:
		districtLean(population);
		break;
	case 1:
		districtTarget(population, args);
		break;
	}
	// Load districts from this population
	loadDistricts(population);
	// Log indicies into a map
	for (unsigned int y = 0; y < pop_num_rows; y++) {
		for (unsigned int x = 0; x < pop_num_cols; x++) {
			unsigned int index = y * pop_num_cols + x;
			population_to_district[index] = population[index].district_index;
		}
	}
}
void Districting::loadDistricts(std::vector<PopulationCell>& population) {
	std::map<unsigned int, std::vector<Voter>> district_voters;
	// Collect voters
	for (auto& cell : population) {
		std::vector<Voter> voters;
		for (auto& voter : district_voters[cell.district_index]) voters.push_back(voter);
		for (auto& voter : cell.getVoters()) voters.push_back(voter);
		district_voters[cell.district_index] = voters;
	}
	// Create districts
	for (auto& voting_pool : district_voters) districts.push_back(District(voting_pool.second));
	// Count district and popular votes
	countVotes();
}
void Districting::countVotes() {
	for (auto& district : districts) {
		party_district_counts[district.lean()] += 1;
		for (auto& party_voter_count : district.getAffiliationCounts()) {
			party_voter_counts[party_voter_count.first] += party_voter_count.second;
			num_of_voters += party_voter_count.second;
		}
	}
}
unsigned int Districting::getNumOfVoters() {
	return num_of_voters;
}
std::map<std::string, unsigned int> Districting::getPopularCounts() {
	return party_voter_counts;
}
std::map<std::string, unsigned int> Districting::getPartyCounts() {
	return party_district_counts;
}
void Districting::districtLean(std::vector<PopulationCell>& population) {
	unsigned int next_district_index = 1;

	for (unsigned int y = 0; y < pop_num_rows; y++) {
		for (unsigned int x = 0; x < pop_num_cols; x++) {
			unsigned int index = y * pop_num_cols + x;
			std::string this_lean = population[index].getLean();

			// Whether or not to create a new district for this cell
			bool new_district = true;

			// Check the population cell above this cell in the grid
			if (y > 0) {
				unsigned int top_index = ((y - 1) * pop_num_cols) + x;
				if (this_lean == population[top_index].getLean()) {
					population[index].linkPopulationCell(&population[top_index]);

					new_district = false;
				}
			}
			// Check the population cell to the right of this cell in the grid
			if (x > 0) {
				unsigned int left_index = (y * pop_num_cols) + (x - 1);
				if (population[left_index].getLean() == this_lean && population[index].district_index != population[left_index].district_index) {
					population[index].linkPopulationCell(&population[left_index]);

					new_district = false;
				}
			}
			if (new_district) {
				population[index].district_index = next_district_index;
				next_district_index++;
			}
		}
	}
}
void Districting::districtTarget(std::vector<PopulationCell>& population, std::string target_party) {
	unsigned int next_district_index = 1;

	for (unsigned int y = 0; y < pop_num_rows; y++) {
		for (unsigned int x = 0; x < pop_num_cols; x++) {
			unsigned int index = y * pop_num_cols + x;
			std::string this_lean = population[index].getLean();

			// Whether or not to create a new district for this cell
			bool new_district = true;

			// Check the population cell above this cell in the grid
			if (y > 0) {
				unsigned int top_index = ((y - 1) * pop_num_cols) + x;
				if (this_lean != target_party && this_lean == population[top_index].getLean()) {
					population[index].linkPopulationCell(&population[top_index]);

					new_district = false;
				}
			}
			// Check the population cell to the right of this cell in the grid
			if (x > 0) {
				unsigned int left_index = (y * pop_num_cols) + (x - 1);
				if (this_lean != target_party && population[left_index].getLean() == this_lean && population[index].district_index != population[left_index].district_index) {
					population[index].linkPopulationCell(&population[left_index]);

					new_district = false;
				}
			}
			if (new_district) {
				population[index].district_index = next_district_index;
				next_district_index++;
			}
		}
	}
}
std::vector<District> Districting::getDistricts() {
	return districts;
}
std::vector<unsigned int> Districting::getDistricting() {
	std::vector<unsigned int> districting_indicies;
	for (auto& pop_dis : population_to_district) {
		districting_indicies.push_back(0);
	}
	for (auto& pop_dis : population_to_district) {
		districting_indicies[pop_dis.first] = pop_dis.second;
	}

	return districting_indicies;
}
void Districting::outputDistricting(std::string path) {
	std::ofstream dfile(path + "districting_output.txt");
	if (dfile.is_open()) {
		std::vector<unsigned int> districting_indicies = getDistricting();
		for (unsigned int y = 0; y < pop_num_rows; y++) {
			for (unsigned int x = 0; x < pop_num_cols; x++) {
				unsigned int loc = y * pop_num_cols + x;
				dfile << districting_indicies[loc];
				if (x != pop_num_cols - 1) dfile << " ";
			}
			dfile << "\n";
		}
		dfile.close();
	}
}
void printDistrictIDGrid(std::vector<unsigned int> grid, unsigned int num_rows, unsigned int num_cols) {
	for (unsigned int y = 0; y < num_rows; y++) {
		for (unsigned int x = 0; x < num_cols; x++) {
			unsigned int loc = y * num_cols + x;
			std::cout << std::setw(5) << grid[loc] << " ";
		}
		std::cout << std::endl;
	}
}
