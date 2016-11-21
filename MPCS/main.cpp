#include <iostream>
#include "Greedy.h"

int main(int argc, char *argv[]) {
	auto greedyGenerator = Greedy("ttcccaagctcacattctcgggcgtctttactcacgttcggggaggtgcgtagtcgtttgaacctaaattaaaggtctcggcaacgagcgggacaagaatttgatcctcatcaa", "cgcagtaccatgcaggacaaattccttgacagacgttgtgggactccgcgcaatgtgattgtattaaattgacctcacgattaacagctcgagcgtatccggtgcgctctatgt", 10);
	/*
	auto sol = greedyGenerator.nextSolution("abcde", "bcdea");
	*/
	//"cdabcdabceab","abceabcdabcd"
	//"abcde", "bcdea"
	//"ttcccaagctcacattctcgggcgtctttactcacgttcggggaggtgcgtagtcgtttgaacctaaattaaaggtctcggcaacgagcgggacaagaatttgatcctcatcaa", "cgcagtaccatgcaggacaaattccttgacagacgttgtgggactccgcgcaatgtgattgtattaaattgacctcacgattaacagctcgagcgtatccggtgcgctctatgt"

	auto longest = greedyGenerator.nextSolution();
	for (auto &block : longest) {
		std::cout << block;
		std::cout << " - ";
	}
	
	return 0;
}