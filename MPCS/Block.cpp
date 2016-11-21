#include "Block.h"



Block::Block()
{
}


Block::~Block()
{
}

std::string Block::toString(std::string str)
{
	return str.substr(begin, end-begin);
}
