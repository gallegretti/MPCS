#pragma once
#include <string>
#include <iostream>
#include "Solution.h"
class Greedy
{
public:
	Greedy::Greedy(std::string input1, std::string input2, int seed);
	~Greedy();

	std::vector<std::string> nextSolution();


public:
	int seed;

	std::string longestOverlapSize(std::string &str1, std::string &str2);

	// Remove str from the vector of strings
	void removeString(std::string &str, std::vector<std::string> &strVec1, int pos);

	bool AreStringsRelated(std::vector<std::string> list1, std::vector<std::string> list2);

private:
	std::string str1;
	std::string str2;
};

