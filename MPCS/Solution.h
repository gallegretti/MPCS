#pragma once
#include <string>
#include <vector>
#include "Block.h"

class Solution
{
public:
	Solution();
	~Solution();

	bool isSolutionTo(std::string str, std::string str2);

private:
	std::vector<Block> blocks;

	bool isSolutionTo(std::string str);
};

