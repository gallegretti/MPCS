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
		if (strcmp(argv[i], "--verbose") == 0)
		{
			options.verbose = true;
		}
	}
	return options;
}

void showHelp()
{
	std::cout << "Usage: mpcs.exe <file> [options]\n" << std::endl;
	std::cout << "For a <file> that has two related strings, one per line\n" << std::endl;
	std::cout << "options:\n" << std::endl;
	std::cout << "-s <seed>      Seed to be used in the RNG" << std::endl;
	std::cout << "--verbose      Prints verbose log" << std::endl;
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
	/*
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
		std::cout << "Running with the following strings:" << std::endl;
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;

		*/

	Options options;
	options.seed = 0;
	std::string str1 = "tctccacctcaagtctgactagtgcataaagcactgacgatgataccgggctagtatggttgtctgcctcaccaggaggaaggagttccccgtgttattaaggccattgtcaataagcagtcaattcttccgggagc";
	std::string str2 = "agggtaccggaaagccttacctcgtgctacgctctacatagacccacgagcattcccttagtaattgataagatagtagagccgccgggatgctggtttcttggccgctcggtgattcgattccaatataatgagac";

	auto greedyGenerator = Greedy(str1, str2, options.seed);


	auto longest = greedyGenerator.nextSolution();
	for (auto &block : longest) {
		std::cout << block;
		std::cout << " - ";
		std::cout << std::endl;
	}


	return 0;
}

