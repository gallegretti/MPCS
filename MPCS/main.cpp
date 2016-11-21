#include <iostream>
#include <string>
#include "Greedy.h"
#include <fstream>

struct Options {
	bool verbose;
	int seed;
};

Options parseOptions(int argc, char *argv[])
{
	Options options;
	options.verbose = false;
	options.seed = 123456;
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-s") == 0)
		{
			options.seed = atoi(argv[i + 1]);
		}
		if (strcmp(argv[i], "-v") == 0)
		{
			options.verbose = true;
		}
	}
	return options;
}

void showHelp()
{
	std::cout << "input file" << std::endl;
	std::cout << "-s seed : for the RNG" << std::endl;
	std::cout << "-v : verbose log" << std::endl;
}

bool readStringsFromFile(char * file, std::string &string1, std::string &string2)
{
	std::ifstream inputFile(file);
	if (!inputFile.is_open())
	{
		return false;
	}
	if (!getline(inputFile, string1))
	{
		inputFile.close();
		return false;
	}
	if (!getline(inputFile, string2))
	{
		inputFile.close();
		return false;
	}
	inputFile.close();
	return true;
}

int main(int argc, char *argv[])
{
	if (argc < 2) {
		showHelp();
		return 0;
	}

	auto options = parseOptions(argc, argv);
	std::string str1, str2;
	auto success = readStringsFromFile(argv[1], str1, str2);
	if (success == false)
	{
		std::cout << "Failed to read the input file" << std::endl;
		return -1;
	}


	auto greedyGenerator = Greedy(str1, str2, options.seed);

	while (true)
	{
		auto longest = greedyGenerator.nextSolution();
		for (auto &block : longest) {
			std::cout << block;
			std::cout << " - ";
			std::cout << std::endl;
		}
	}

	return 0;
}
