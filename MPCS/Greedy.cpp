#include "Greedy.h"


Greedy::Greedy(std::string input1, std::string input2, unsigned int seed)
{
	this->str1 = input1;
	this->str2 = input2;
	srand(seed);

	if (!AreStringsRelated({str1}, {str2})) {
		std::cout << "Invalid inputs";
	}
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

	
	std::vector <std::string> common;
	st selected;

	while (!str1List.empty()) {
		std::vector <st> candidates;
		// Find where the common strings are
		for (size_t string1 = 0; string1 < str1List.size(); string1++) {
			for (size_t string2 = 0; string2 < str2List.size(); string2++) {
				common = commonStrings(str1List[string1], str2List[string2]);
				for (auto &str : common) {
					candidates.push_back({ string1 , string2, str });
				}
			}
		}

		// Select one
		std::sort(candidates.begin(), candidates.end());
		bool done = false;
		for (auto &candidate : candidates)
		{
			if (rand() % 100 > 50)
			{
				selected = candidate;
				done = true;
				break;
			}
		}
		if (!done)
		{
			selected = candidates[0];
		}

		result.push_back(selected.str);

		// Remove from the unmarked strings
		removeString(selected.str, str1List, selected.posVec1);
		removeString(selected.str, str2List, selected.posVec2);
		
	}
	return result;
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




// This is very bad
std::vector<std::string> Greedy::commonStrings(const std::string &str1, const std::string &str2)
{
	int i = 0;
	int j = 0;
	int k = 1;
	//std::vector<std::string> overlaps;
	std::string secondBest;
	std::string overlap, maxOverlap;
	int overlapSize = 0;
	//std::cout << "Longest overlapping for " << str1 << " and " << str2 << " is:" << std::endl;
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
					{
						secondBest = maxOverlap;
						maxOverlap = overlap;
					}
					overlap.clear();
				}
			}
			if (overlap.size() > maxOverlap.size())
			{
				secondBest = maxOverlap;
				maxOverlap = overlap;
			}
			overlap.clear();
		}
	}
	if (maxOverlap.size() == 0)
	{
		return {};
	}

	if (secondBest.size() == 0)
	{
		return{ maxOverlap };
	}
	return { maxOverlap, secondBest };
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