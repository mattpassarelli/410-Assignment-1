/*
 * utilities.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: matt
 */

#include "utilities.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

std::vector<process_stats> list;

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename) {
	list.clear();

	std::ifstream inFile;
	std::string line;
	std::string token;
	process_stats stats;
	int count = 0;
	const char CHAR_TO_SEARCH_FOR = ',';

	inFile.open(filename);
	inFile.clear();

	if (inFile.is_open()) {

		while(!inFile.eof())
		{
			getline(inFile, line);
			if(!line.empty())
			{
				std::istringstream ss(line);
				if(!getline(ss, line, CHAR_TO_SEARCH_FOR))
				{
					break;
				}

				if(count == 0)
					stats.process_number = std::stoi(line);
				else if(count == 1)
					stats.start_time = std::stoi(line);
				else if(count == 2)
					stats.cpu_time = std::stoi(line);

				count++;
			}

			list.push_back(stats);
		}

		return SUCCESS;

	} else {
		return COULD_NOT_OPEN_FILE;
	}

}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename) {
	return 0;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {

}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {

}
