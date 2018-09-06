/*
 * utilities.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: matt
 */

#include "utilities.h"



//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename){
	return 0;
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename)
{
	return 0;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder)
{

}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext()
{

}
