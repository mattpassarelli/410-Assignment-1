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

	inFile.open(filename);
	inFile.clear();

	if (inFile.is_open()) {

		while (!inFile.eof()) {
			int count = 0;
			process_stats stats;

			getline(inFile, line);
			while (!line.empty()) {

				std::istringstream ss(line);

				if (!getline(ss, line, CHAR_TO_SEARCH_FOR)) {
					break;
				}

				switch(count)
				{
				case 0:
					stats.process_number = std::stoi(line);
					break;
				case 1:
					stats.start_time = std::stoi(line);
					break;
				case 2:
					stats.cpu_time = std::stoi(line);
					break;
				}

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
	std::ofstream outFile;

	std::vector<process_stats>::iterator ptr;

	outFile.open(filename);

	if(outFile.is_open())
	{
		std::string data;
		process_stats temp;

		for(ptr = list.begin(); ptr < list.end(); ptr++)
			{
				temp = *ptr;

				data = temp.process_number + ',' + temp.start_time + ',' + temp.cpu_time;

				outFile << data << std::endl;
			}

		outFile.close();
		return SUCCESS;
	}
	else
	{
		return COULD_NOT_OPEN_FILE;
	}

}



int sort(SORT_ORDER mySortOrder)
{
	switch(mySortOrder)
		{
		case SORT_ORDER::CPU_TIME:
			return 1;
		case SORT_ORDER::PROCESS_NUMBER:
			return 2;
		case SORT_ORDER::START_TIME:
			return 3;
		default:
			return FAIL;
		}
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	sort(mySortOrder);
}

bool operator<(SORT_ORDER left, SORT_ORDER right)
{
	return sort(left) < sort(right);
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats rtn;

	rtn = list.front();

	list.erase(list.begin());

	return rtn;
}
