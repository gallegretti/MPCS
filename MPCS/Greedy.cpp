#include "Greedy.h"


Greedy::Greedy(std::string input1, std::string input2, int seed)
{
	this->str1 = input1;
	this->str2 = input2;
	this->seed = seed;
}

Greedy::~Greedy()
{
}

std::vector<std::string> Greedy::nextSolution()
{
	std::vector <std::string> result;
	// Remaining strings that need to match
	std::vector <std::string> str1List = { str1 };
	std::vector <std::string> str2List = { str2 };
	std::string candidate;
	
	while (!str1List.empty()) {
		std::string longestString = "";
		// Find longest common string between the two sets
		for (auto string1 : str1List) {
			for (auto string2 : str2List) {
				candidate = longestOverlapSize(string1, string2);
				// TODO: Random
				if (candidate.length() > longestString.length()) {
					longestString = candidate;
				}
			}
		}
		result.push_back(longestString);

		// Remove from the unmarked strings
		removeString(longestString, str1List);
		removeString(longestString, str2List);
	}
	return result;
}


void Greedy::removeString(std::string & longestString, std::vector<std::string>& str1List)
{
	for (int i = 0; i < str1List.size(); i++) {
		// TODO: Stops at the first? Tries to find one that matches the whole string?
		auto find = str1List[i].find(longestString);
		// If found
		if (find != std::string::npos) {
			// If it's the whole string, remove the whole element
			if (str1List[i] == longestString) {
				for (auto j = i; j < str1List.size() - 1; j++) {
					str1List[j] = str1List[j + 1];
				}
				str1List.pop_back();
			}
			// If it's in the begin
			else if (find == 0) {
				str1List[i] = str1List[i].substr(longestString.length(), longestString.length());
			}
			// If it's in the end
			else if (find + longestString.length() == str1List[i].length()) {
				str1List[i] = str1List[i].substr(0, str1List[i].length() - longestString.length());
			}
			// If it's in the middle
			else {
				// Break into two new elements
				auto newStrLeft = str1List[i].substr(0, find);
				auto newStrRight = str1List[i].substr(find + longestString.length(), str1List[i].length());
				str1List[i] = newStrLeft;
				str1List.push_back(newStrRight);
			}
		}
	}
}


// This is very bad
std::string Greedy::longestOverlapSize(std::string &str1, std::string &str2)
{
	int i = 0;
	int j = 0;
	int k = 1;
	std::string overlap, maxOverlap;
	int overlapSize = 0;

	for (i = 0; i < str1.size(); i++)
	{
		for (j = 0; j < str2.size(); j++)
		{
			for (k = 1; k <= str1.size() && k <= str2.size(); k++)
			{
				if (str1.substr(i, k) == str2.substr(j, k))
				{
					overlap = str1.substr(i, k);
				}
				else
				{
					if (overlap.size() > maxOverlap.size())
						maxOverlap = overlap;
					overlap.clear();
				}
			}
			if (overlap.size() > maxOverlap.size())
				maxOverlap = overlap;
			overlap.clear();
		}
	}
	return maxOverlap;
}


/*	{
		int i = 0;
		int j = 0;
		int k = 1;
		std::string overlap, maxOverlap;
		int overlapSize = 0;


		for (i = 0; i < str1.size(); i++)
		{
			for (j = 0; j < str2.size(); j++)
			{
				for (k = 1; k <= str1.size() && k <= str2.size(); k++)
				{
					if (str1.substr(i, k) == str2.substr(j, k))
					{
						overlap = str1.substr(i, k);
					}
					else
					{
						if (overlap.size() > maxOverlap.size())
							maxOverlap = overlap;
						overlap.clear();
					}
				}
				if (overlap.size() > maxOverlap.size())
					maxOverlap = overlap;
				overlap.clear();
			}
		}
		//overlapSize = maxOverlap.size();

		return maxOverlap;
		}*/