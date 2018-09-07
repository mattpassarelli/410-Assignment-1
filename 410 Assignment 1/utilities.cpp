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
	const char CHAR_TO_SEARCH_FOR = ',';

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

	outFile.open(filename);

	if(outFile.is_open())
	{
		std::string data;
		process_stats temp;

		for(int i = 0; i < list.size(); i++)
		{

			//TODO assign removed index to temp
			temp = list.pop_back();
			data = temp.process_number + "," + temp.start_time + "," + temp.cpu_time;

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

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {

}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats rtn;

	rtn = list.front();

	//TODO remove the index

	return rtn;
}
