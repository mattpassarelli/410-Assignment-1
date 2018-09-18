/*
 * utilities.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: Matt Passarelli
 */

#include "utilities.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

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
	std::stringstream ss;

	inFile.open(filename);
	inFile.clear();

	if (inFile.is_open()) {

		while (!inFile.eof()) {

			process_stats stats;

			while (getline(inFile, line)) {

				ss.str(line);
				std::string tempValue;

				getline(ss, tempValue, CHAR_TO_SEARCH_FOR);
				stats.process_number = std::stoi(tempValue);

				getline(ss, tempValue, CHAR_TO_SEARCH_FOR);
				stats.start_time = std::stoi(tempValue);

				getline(ss, tempValue, CHAR_TO_SEARCH_FOR);
				stats.cpu_time = std::stoi(tempValue);

				list.push_back(stats);
				ss.clear();
			}

		}

		inFile.close();
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

	if (outFile.is_open()) {
		std::string data;
		process_stats temp;

		for (unsigned int i = 0; i < list.size(); i++) {
			temp = list[i];

			data = std::to_string(temp.process_number) + ","
					+ std::to_string(temp.start_time) + ","
					+ std::to_string(temp.cpu_time);

			//I can't tell you how long it took me to figure out how to stop
			//outputting a blank line at the end of all my files. I couldn't do it in 327
			//but lo and behold, I figured out how to do it in class now lmoa

			if (i < list.size() - 1)
				outFile << data << std::endl;
			else
				outFile << data;
		}

		outFile.close();
		return SUCCESS;
	} else {
		return COULD_NOT_OPEN_FILE;
	}

}

//Below are a set of sorting methods that I can use with std::sort
//Another thing that took me a while to figure out how to do, and honestly
//There's probably still a better way to do this, but this is how I figured I would sort
//using an enum for the sorting parameter

//Sorts by CPU_TIME
bool compareByCPUTime(const process_stats &a, const process_stats b) {
	return a.cpu_time < b.cpu_time;
}

//Sorts by PROCESS_NUMBER
bool compareByProcessNumber(const process_stats &a, const process_stats b) {
	return a.process_number < b.process_number;
}

//Sorts by START_TIME
bool compareByStartTime(const process_stats &a, const process_stats b) {
	return a.start_time < b.start_time;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	switch (mySortOrder) {
	case CPU_TIME:
		std::sort(list.begin(), list.end(), compareByCPUTime);
		break;
	case PROCESS_NUMBER:
		std::sort(list.begin(), list.end(), compareByProcessNumber);
		break;
	case START_TIME:
		std::sort(list.begin(), list.end(), compareByStartTime);
		break;
	}
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats rtn;

	rtn = list.front();

	list.erase(list.begin());

	return rtn;
}
