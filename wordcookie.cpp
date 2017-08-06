//
//  main.cpp
//  Lab08
//
//  Created by Anthony Shinn on 6/16/17.
//  Copyright © 2017 Anthony Shinn. All rights reserved.
//

#include "Trie.h"
#include <fstream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <map>
#include <algorithm>
#include <deque>

Trie trie;
std::vector<std::string> foundwords;	// words found in the trie
std::vector<char> currin;
std::deque<char> currout;
bool sMode;
char special;

struct mycomp {
	bool operator()(const char *c1, const char *c2) const {
		return (strcmp(c1, c2) < 0);
	}
};

bool sProm(std::string word) {
	for (char j : word) {
		if (j == special) {
			return true;
		}
	}
	return false;
}

bool promising(std::string word) {
	//for (const auto i : currout) {
	if (trie.containsAtLeast(word)) {
		if (word.size() > 2 && trie.contains(word) && (!sMode || sProm(word))) {
			foundwords.push_back(word);
		}
		return true;
	}
	return false;
}

void gen_perms() {
	std::string theword(currin.begin(), currin.end());
	if (currout.empty()) {		// BASECASE 1
		if (trie.contains(theword) && (!sMode || sProm(theword))) {
			foundwords.push_back(theword);
		}
		return;
	} // if
	if (!promising(theword)) {	// BASECASE 2
		return;
	}
	// if promising
	for (unsigned k = 0; k < currout.size(); k++) {
		// add to unvisited. Promising
		currin.push_back(currout.front());
		currout.pop_front();

		gen_perms();
		// hit a base case (not promising)

		currout.push_back(currin.back());
		currin.pop_back();
	} // for
} // gen_perms()

// UPDATE 3: sort input letters

int main(int argc, char *argv[]) {
	if (argc != 3 && argc != 4) {
		std::cerr << "TOO MANY ARGS OR TOO FEW";
		exit(1);
	}

	std::ifstream dict;
	std::string word;
	dict.open(argv[1]);
	while (dict >> word) {
		trie.insert(word);
	}
	dict.close();

	std::string ogword = argv[2];
	size_t ogsize;
	for (char i : ogword) {
		currout.push_back(i);
	}

	sMode = false;
	if (argc == 4) {
		special = argv[3][0];
		sMode = true;
		currout.push_back(special);
	}

	bool repeat = false;
	ogsize = currout.size();
	for (size_t b = 0; b < currout.size(); ++b) {
		for (size_t d = b + 1; d < currout.size(); ++d) {
			if (currout[b] == currout[d]) {
				repeat = true;
				break;
			}
		}
		if (repeat) break;
	}

	//std::sort(currout.begin(), currout.end(), mycomp());	// sorts letters

	gen_perms();

	//if (sMode) {
	//	std::vector<std::string> temp = foundwords;
	//	foundwords.clear();
	//	// special level mode so remove words w/out special
	//	for (int i = 0; i < (int)temp.size(); ++i) {
	//		for (char j : temp[i]) {
	//			if (j == special) {
	//				foundwords.push_back(temp[i]);
	//				break;
	//			}
	//		}
	//	}
	//}
	
	if (repeat) {
		int ogsize2 = (int)foundwords.size();
		for (int s = ogsize2 - 1; s > 0; --s) {
			for (int t = s - 1; t >= 0; --t) {		// [0 t s 3 4]
				if (foundwords[s] == foundwords[t]) {	// [1 3 3 5 7]
					//foundwords[s] = foundwords.back();// [1 3 5 7 7]
					int g = s;
					while (g != (int)foundwords.size() - 1) {
						foundwords[g] = foundwords[g + 1];
						++g;
					}
					foundwords.pop_back();				// [1 3 5 7]
					break;
				}
			}
		}
	}

	std::cout << foundwords.size() << " words found:\n";
	for (size_t a = 3; a <= ogsize; ++a) {
		for (std::string& it : foundwords) {
			if (it.size() == a) {
				std::cout << it << "\n";
			}
			
		}
	}
	/*for (std::string& it : foundwords) {
		std::cout << it << "\n";
	}*/

	
}
