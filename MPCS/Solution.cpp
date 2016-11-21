#include "Solution.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef pair<string::const_iterator, string::const_iterator> stringp;
typedef vector<string> strings;


Solution::Solution()
{
}


Solution::~Solution()
{
}

bool Solution::isSolutionTo(std::string str1, std::string str2)
{
	/*
	strings blockStrs1;
	for (auto block : blocks) {
		blockStrs1.push_back(block.toString(str1));
	}
	stringp string = { str1.begin , str1.end };

	strings blockStrs2;
	for (auto block : blocks) {
		blockStrs1.push_back(block.toString(str1));
	}
	stringp string = { str1.begin , str1.end };

	*/
	//return isConcatenation(string, blockStrs) && isConcatenation(string, st;
	/*
	std::string stringFromBlocks(str.length);
	// Assume that blocks are ordered
	for (auto block : blocks) {
		stringFromBlocks.append(str.substr(block.begin, block.end - block.begin));
	}
	return stringFromBlocks == str;
	*/
	return false;
}

bool Solution::isSolutionTo(std::string str)
{
	for (auto block : blocks) {
		auto blockStr = block.toString(str);
		str.find(blockStr);
	}
	return false;
}



bool isConcatenation(stringp S, const strings L) {
	for (strings::const_iterator p = L.begin(); p != L.end(); ++p) {
		auto M = mismatch(p->begin(), p->end(), S.first);
		if (M.first == p->end()) {
			if (L.size() == 1)
				return true;
			strings T;
			T.insert(T.end(), L.begin(), p);
			strings::const_iterator v = p;
			T.insert(T.end(), ++v, L.end());
			if (isConcatenation(make_pair(M.second, S.second), T))
				return true;
		}
	}
	return false;
}