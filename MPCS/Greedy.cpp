#include "Greedy.h"
#include <algorithm>


Greedy::Greedy(std::string input1, std::string input2, unsigned int seed)
{
	this->str1 = input1;
	this->str2 = input2;
	srand(seed);

	if (!AreStringsRelated({str1}, {str2})) {
		std::cout << "Invalid inputs";
	}

	this->commonStrings();

}

Greedy::~Greedy()
{

}


std::vector<std::string> Greedy::nextSolution() {
	int i = 0;
	int j = 0;
	int locationLongest[2] = { 0, 0 };
	int overlapSize = 0;
	int psCopy[1000][1000];
	bool firstFlag = true;
	std::string stringCopy[1000][1000];
	std::vector<std::string> stringPartitions;
	
	for (i = 0; i < 1000; i++)
		for (j = 0; j < 1000; j++) {
			psCopy[i][j] = psMatrix[i][j];
			stringCopy[i][j] = partitionsMatrix[i][j];
			if (psCopy[i][j] > overlapSize) {
				overlapSize = psCopy[i][j];
				locationLongest[0] = i;
				locationLongest[1] = j;
			}
		}

	while (overlapSize) {

		stringPartitions.push_back(stringCopy[locationLongest[0]][locationLongest[1]]);

		for (i = 0; i < overlapSize; i++)
			for (j = 0; j <= str2.size(); j++)
				psCopy[locationLongest[0] - i][j] = 0;

		for (i = 0; i <= str1.size(); i++)
			for (j = 0; j < overlapSize; j++)
				psCopy[i][locationLongest[1] - j] = 0;

		overlapSize = 0;
		firstFlag = true;
		for (int i = 0; i <= str1.size(); i++)
		{
			for (int j = 0; j <= str2.size(); j++)
			{	
				if (psCopy[i][j] > overlapSize) {
					if (firstFlag || (rand() % 100 < 60)) {
						assertCorrect(i, j, psCopy, stringCopy);
						if (psCopy[i][j] > overlapSize) {
							overlapSize = psCopy[i][j];
							locationLongest[0] = i;
							locationLongest[1] = j;
							firstFlag = false;
						}
					}
				}
			}
		}
	}
	return stringPartitions;
}

bool Greedy::AreStringsRelated(std::vector<std::string> list1, std::vector<std::string> list2)
{
	int a[256] = { 0 };
	int b[256] = { 0 };

	for (auto &str : list1) {
		for (auto &character : str) {
			a[character]++;
		}
	}
	for (auto &str : list2) {
		for (auto &character : str) {
			b[character]++;
		}
	}

	for (auto i = 0; i < 256; i++) {
		if (a[i] != b[i]) {
			return false;
		}
	}

	return true;
}


void Greedy::commonStrings()
{
	int i = 0;
	int j = 0;
	int locationLongest[2] = {0, 0};
	int overlapSize = 0;

	//Monta matriz completa de overlaps das duas strings
	for (int i = 0; i <= str1.size(); i++)
	{
		for (int j = 0; j <= str2.size(); j++)
		{
			if (i == 0 || j == 0) 
				psMatrix[i][j] = 0;

			else if (str1[i - 1] == str2[j - 1])
			{
				psMatrix[i][j] = psMatrix[i - 1][j - 1] + 1;
				if (psMatrix[i][j] > overlapSize) {
					locationLongest[0] = i;
					locationLongest[1] = j;
				}
				overlapSize = std::max(overlapSize, psMatrix[i][j]);
				partitionsMatrix[i][j] = partitionsMatrix[i - 1][j - 1];
				partitionsMatrix[i][j] += str1[i - 1];
			}
			else psMatrix[i][j] = 0;
		}
	}
}

 
bool Greedy::assertCorrect(int i, int j, int (&overlapArray)[1000][1000], std::string(&stringArray)[1000][1000]) {
	if (overlapArray[i][j] == 1)
		return true;
	else if (overlapArray[i - 1][j - 1] == (overlapArray[i][j] - 1)) 
		return assertCorrect(i - 1, j - 1, overlapArray, stringArray);
	else {
		correctMatrix(i, j, overlapArray, stringArray);
		return true;
	}
}

void Greedy::correctMatrix(int i, int j, int(&overlapArray)[1000][1000], std::string(&stringArray)[1000][1000]) {
	if (overlapArray[i][j] > 0) {
		overlapArray[i][j] = overlapArray[i - 1][j - 1] + 1;
		stringArray[i][j] = stringArray[i][j].substr(stringArray[i][j].size() - overlapArray[i][j], -1);
		correctMatrix(i + 1, j + 1, overlapArray, stringArray);
	}
	else {
	}

}