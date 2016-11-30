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
	static int psCopy[1000][1000];
	std::vector<std::string> stringPartitions;
	
	for (i = 0; i < 1000; i++)
		for (j = 0; j < 1000; j++) {
			psCopy[i][j] = psMatrix[i][j];
			if (psMatrix[i][j] > overlapSize) {
				overlapSize = psMatrix[i][j];
				locationLongest[0] = i;
				locationLongest[1] = j;
			}
		}


	while (overlapSize) {
		stringPartitions.push_back(partitionsMatrix[locationLongest[0]][locationLongest[1]]);
		for (i = 0; i < overlapSize; i++)
			for (j = 0; j < str2.size(); j++)
				psMatrix[locationLongest[0] - i][j] = 0;
		for (i = 0; i < str1.size(); i++)
			for (j = 0; j < overlapSize; j++)
				psMatrix[i][locationLongest[0] - j] = 0;
		overlapSize = 0;
		for (int i = 0; i <= str1.size(); i++)
		{
			for (int j = 0; j <= str2.size(); j++)
			{
				if (psMatrix[i][j] > overlapSize) {
					if (assertComplete(i, j, psMatrix)) {
						overlapSize = psMatrix[i][j];
						locationLongest[0] = i;
						locationLongest[1] = j;
					}
					else psMatrix[i][j] = 0;
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



void Greedy::removeString(std::string & longestString, std::vector<std::string>& str1List, int pos)
{
	auto find = str1List[pos].find(longestString);
	// If it's the whole string, remove the whole element
	if (str1List[pos] == longestString) {
		for (size_t j = pos; j < str1List.size() - 1; j++) {
			str1List[j] = str1List[j + 1];
		}
		str1List.pop_back();
	}
	// If it's in the begin
	else if (find == 0) {
		str1List[pos] = str1List[pos].substr(longestString.length(), std::string::npos);
	}
	// If it's in the end
	else if (find + longestString.length() == str1List[pos].length()) {
		str1List[pos] = str1List[pos].substr(0, str1List[pos].length() - longestString.length());
	}
	// If it's in the middle
	else {
		// Break into two new elements
		auto newStrLeft = str1List[pos].substr(0, find);
		auto newStrRight = str1List[pos].substr(find + longestString.length(), std::string::npos);
		str1List[pos] = newStrLeft;
		str1List.push_back(newStrRight);
	}
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

 
bool Greedy::assertComplete(int i, int j, int overlapArray[1000][1000]) {
	if (overlapArray[i][j] == 1)
		return true;
	else if (overlapArray[i - 1][j - 1] == (overlapArray[i][j] - 1))
		return assertComplete(i - 1, j - 1, overlapArray);
	else
		return false;
}