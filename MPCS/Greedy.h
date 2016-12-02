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

	void nextSolution(int(&common)[1000][1000]);


public:

	void Greedy::commonStrings();

	bool Greedy::assertCorrect(int i, int j, int (&overlapArray)[1000][1000], int(&common)[1000][1000]);

	void Greedy::correctMatrix(int i, int j, int(&overlapArray)[1000][1000], int(&common)[1000][1000]);

	bool AreStringsRelated(const std::vector<std::string> &list1, const std::vector<std::string> &list2);

	int psMatrix[1000][1000];

private:
	std::string str1;
	std::string str2;
};

