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

	void Greedy::commonStrings();

	bool Greedy::assertCorrect(int i, int j, int (&overlapArray)[1000][1000], std::string(&stringArray)[1000][1000]);

	void Greedy::correctMatrix(int i, int j, int(&overlapArray)[1000][1000], std::string(&stringArray)[1000][1000]);

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
	int psMatrix[1000][1000];
	std::string partitionsMatrix[1000][1000];
};

