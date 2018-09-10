/*
 * main.cpp
 *
 *  Created on: Sep 6, 2018
 *      Author: matt
 */
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>

//this is a template class, its mostly here as a helper for me
//the T and U are generic params, I can substitute any type for them
//they must be comparable with ==, templates are extremely hard to get right BTW
template<typename T, typename U>
bool EXPECT_EQ(T expectedVal, U actualVal, std::string testnumb = "") {
	bool bout = (expectedVal == actualVal);
	try {
		if (bout) {
			std::cout << "SUCCESS " + testnumb;
		} else
			std::cout << "FAIL " + testnumb;
		std::cout << std::endl;
	} catch (...) {
		std::cout << "Threw exception when attempting " << testnumb
				<< std::endl;
	}

	return bout;
}

void testLoadData() {

	EXPECT_EQ(COULD_NOT_OPEN_FILE, loadData("testdataFAIL.txt"), "Test 1");
	EXPECT_EQ(SUCCESS, saveData("testdata.txt"), "Test 2");

}

void testSaveData() {
	EXPECT_EQ(SUCCESS, saveData("testdata.txt"), "Test 3");
}



void testSortData() {

}

void testGetFirst() {

}

int main() {

	testLoadData();
	testSaveData();
	testSortData();
	testGetFirst();

	return 0;
}

