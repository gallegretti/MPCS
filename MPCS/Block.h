#pragma once
#include <string>
class Block
{
public:
	Block();
	~Block();

	std::string toString(std::string str);

	int begin;
	int end;
};

