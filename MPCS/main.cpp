#include <iostream>
#include <string>
#include "Greedy.h"
#include <fstream>
#include <time.h>

struct Options {
	int maximumSeconds;
	bool verbose;
	bool glpk;
	unsigned int seed;
};

Options parseOptions(int argc, char *argv[])
{
	Options options;
	options.verbose = false;
	options.glpk = false;
	options.seed = 123456;
	options.maximumSeconds = 5;
	for (int i = 2; i < argc; i++)
	{
		if (strcmp(argv[i], "-s") == 0)
		{
			if (argc <= i + 1) {
				std::cout << "Invalid seed, using default\n";
				break;
			}
			options.seed = atoi(argv[i + 1]);
		}
		if (strcmp(argv[i], "--verbose") == 0)
		{
			options.verbose = true;
		}
		if (strcmp(argv[i], "--glpk") == 0) 
		{
			options.glpk = true;
		}
		if (strcmp(argv[i], "-t") == 0)
		{
			if (argc <= i + 1) {
				std::cout << "Invalid time, using default\n";
				break;
			}
			options.maximumSeconds = atoi(argv[i + 1]);
		}
	}
	return options;
}

void showHelp()
{
	std::cout << "Usage: mpcs.exe <file> [options]\n" << std::endl;
	std::cout << "For a <file> that has two related strings, one per line\n" << std::endl;
	std::cout << "options:\n" << std::endl;
	std::cout << "--glpk         Returns the GLPK formulation for the input in the stdout" << std::endl;
	std::cout << "-s <seed>      Seed to be used in the GRASP's RNG (Does not apply to --glpk)" << std::endl;
	std::cout << "-t <seconds>   Time in seconds that the program is allowed to run (Does not apply to --glpk)" << std::endl;
	std::cout << "--verbose      Prints verbose log in the stdout (Does not apply to --glpk)" << std::endl;
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

std::vector<std::string> toVector(int(&selected)[1000][1000], const std::string &str1, const std::string &str2)
{
	std::vector<std::string> result;
	for (auto i = 0; i < str1.length() + 1; i++)
		for (auto j = 0; j < str2.length() + 1; j++)
		{
			auto value = selected[i][j];
			if (value) {
				result.push_back(str1.substr(i - value, value));
			}
		}
	return result;
}

int localSearch(int(&selected)[1000][1000], int(&psMatrix)[1000][1000], const std::string &str1, const std::string &str2)
{
	int blocos = 0;
	static int lineWithValue[1000] = { 0 };
	for (auto i = 0; i < str1.length() + 1; i++) {
		lineWithValue[i] = 0;
	}
	// Para cada coluna, indica a linha que há o valor na matriz 'selected' (0 se não há)
	for (auto i = 0; i < str1.length() + 1; i++)
		for (auto j = 0; j < str2.length() + 1; j++)
		{
			if (selected[i][j] != 0) {
				blocos++;
				lineWithValue[j] = i;
				// Como há um valor por linha, pode ir para a proxima quando encontrar
				break;
			}
		}

	int col1 = -1;
	int col2 = -1;
	// Pega todo par de colunas em sequencia, com indices de colunas col1 < col2
	for (auto i = 0; i < str1.length() + 1; i++)
	{
		if (!lineWithValue[i])
			continue;

		if (col1 == -1)
		{
			col1 = i;
			continue;
		}

		if (col2 == -1)
		{
			col2 = i;
		}
		else
		{
			col1 = col2;
			col2 = i;
		}
		
		// Assegura que os blocos sao vizinhos nas duas strings
		if ((col2 - lineWithValue[col1] == 0) && (selected[lineWithValue[col2]][col2] - col1 == 0))
		{
			// Caso exista uma unica substring que cubra as duas atuais
			auto sum = selected[lineWithValue[col2]][col2] + selected[lineWithValue[col1]][col1];
			if (psMatrix[lineWithValue[col2]][col2] >= sum)
			{
				// Desmarca a primeira substring
				selected[lineWithValue[col1]][col1] = 0;
				// Re-marca a nova, sabendo que vai cobrir a anterior
				selected[lineWithValue[col2]][col2] = sum;
				blocos--;
			}
		}
	}
	return blocos;
}

int main(int argc, char *argv[])
{
	time_t startTime;
	time(&startTime);
	
	std::string str1, str2;
	int selected[1000][1000] = { 0 };
	
	
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
		std::cout << "Maximum time: " << options.maximumSeconds << "s" << std::endl;
	}
	/*
	str1 = "abab";
	str2 = "abba";
	*/
	std::vector<std::string> best;
	auto greedyGenerator = Greedy(str1, str2, options.seed);

	// GRASP:
	while(true)
	{
		// Initial solution
		greedyGenerator.nextSolution(selected);
		// Local search
		auto blocos = localSearch(selected, greedyGenerator.psMatrix, str1, str2);
		// Select if it's better
		if ((selected, str1, str2).size() < best.size() || best.size() == 0)
		{
			best = toVector(selected, str1, str2);
		}
		// End if time is up
		time_t currTime;
		time(&currTime);
		if (difftime(currTime, startTime) >= options.maximumSeconds)
			break;
	}

	std::cout << "Melhor string:" << prettyString(best) << std::endl;
	std::cout << "Tamanho: " << best.size() << std::endl;

	if (!greedyGenerator.AreStringsRelated(best, { str1 }) || !greedyGenerator.AreStringsRelated(best, { str2 })) {
		std::cout << "IF YOU'RE READING THIS, YOU FUCKED UP";
	}


	return 0;
}

