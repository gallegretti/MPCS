#pragma once
#include <string>
#include <iostream>
#include "Solution.h"
#include <algorithm>
#include <stdlib.h>
class Greedy
{
public:
	Greedy::Greedy(std::string input1, std::string input2, unsigned int seed);
	~Greedy();

	std::vector<std::string> nextSolution();


public:

	std::vector<std::string> Greedy::commonStrings(const std::string &str1, const std::string &str2);

	// bool Greedy::assertComplete(int i, int j, int overlapArray[1000][1000]);

	// Remove str from the vector of strings
	void removeString(std::string &str, std::vector<std::string> &strVec1, int pos);

	bool AreStringsRelated(std::vector<std::string> list1, std::vector<std::string> list2);

	struct st
	{
		st(){}

		st(size_t posVec1, size_t posVec2, std::string str)
		{
			this->posVec1 = posVec1;
			this->posVec2 = posVec2;
			this->str = str;
		}
		size_t posVec1, posVec2;
		std::string str;
																	// Intentional. First element should be the biggest
		inline bool operator< (const st& rhs) { return this->str.length() > rhs.str.length(); }
	};


private:
	std::string str1;
	std::string str2;
};

