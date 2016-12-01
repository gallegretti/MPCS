#include <iostream>
#include <string>
#include "Greedy.h"
#include <fstream>

struct Options {
	bool verbose;
	unsigned int seed;
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

std::string prettyString(const std::vector<std::string> &list)
{
	std::string out = "{ ";
	for (auto &string : list) {
		out += "\"" + string + "\",";
	}
	out += "}";
	return out;
}

std::vector<std::string> toVector(int(&commonStrings)[1000][1000], bool(&selected)[1000][1000], std::string str1, std::string str2) 
{
	std::vector<std::string> result;
	for (auto i = 0; i < str1.length() + 1; i++)
		for (auto j = 0; j < str2.length() + 1; j++) 
		{
			if (selected[i][j]) {
				auto value = commonStrings[i][j];
				std::cout << "valor:" << value << std::endl;
				//result.push_back(str2.substr(j - value, value + 1));
				//std::cout << "i:" << i << "j:" << j << " value:" << value << " result:" <<prettyString(result) << std::endl;
			}
		}
	return result;
}

int main(int argc, char *argv[])
{
	std::string str1, str2;
	bool selected[1000][1000] = { false };
	/*
	if (argc < 2) {
		showHelp();
		return 0;
	}

	auto options = parseOptions(argc, argv);
	auto success = readStringsFromFile(argv[1], str1, str2);
	if (success == false)
	{
		std::cout << "Failed to read the input file" << std::endl;
		return -1;
	}

	if (options.verbose)
	{
		std::cout << "Inputs:" << std::endl;
		std::cout << str1 << std::endl;
		std::cout << str2 << std::endl;
		std::cout << "Seed: " << options.seed << std::endl;
	}
	*/
	str2 = "cdabcdabceab";
	str1 = "abceabcdabcd";

	std::vector<std::string> best;
	auto greedyGenerator = Greedy(str1, str2, 1);

	/*
	// Procura o maior bloco
	int biggest = 0;
	int biggest_i;
	int biggest_j;
	for (auto i = 0; i < str1.length(); i++)
		for (auto j = 0; j < str2.length(); j++)
		{
			if (selected[i][j] == true)
			{
				if (greedyGenerator.psMatrix[i][j] > biggest)
				{
					biggest = greedyGenerator.psMatrix[i][j];
					biggest_i = i;
					biggest_j = j;
				}
			}
		}
		// Desmarca ele

	*/
	for (auto i = 0; i < 1; i++)
	{
		//auto instance = greedyGenerator.nextSolution();
		// TODO: local search 
		// Procura o maior bloco
		// Desmarca
		// 
		for (auto i = 0; i < str1.length() + 1; i++)
			for (auto j = 0; j < str2.length() + 1; j++)
				selected[i][j] = false;
		greedyGenerator.nextSolution(selected);
		auto instance = toVector(greedyGenerator.psMatrix, selected, str1, str2);
		if (instance.size() < best.size() || best.size() == 0)
		{
			best = instance;
			std::cout << prettyString(best) << std::endl;
			std::cout << "Size: " << best.size();
		}
	}

	std::cout << prettyString(best) << std::endl;
	std::cout << "Size: " << best.size();
	
	if ( !greedyGenerator.AreStringsRelated(best, { str1 }) || !greedyGenerator.AreStringsRelated(best, { str2 }) ) {
		std::cout << "IF YOU'RE READING THIS, YOU FUCKED UP";
	}
	

	return 0;
}

