#ifndef GERRYMANDERING_DISTRICTING
#define GERRYMANDERING_DISTRICTING
#include "District.h"
#include <vector>
class Districting {
private:
	std::vector<District> districts;
public:
	// Returns popular affiliation of districts
	int lean();
	// Returns majority count
	int majority();
	// Returns minority count
	int minority();
};
#endif
