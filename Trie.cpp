/**
 * Trie.h
 *
 * EECS 281: Lab 8
 * Spring 2017
 *
 * Implements a trie.
 */

#include "Trie.h"

TrieNode::~TrieNode() {
    // TODO: delete dynamically allocated data
}

void Trie::insert(const std::string &word) {
	if (root == nullptr) {
		root = new TrieNode;
	}
	if (contains(word)) {
		return;
	}

	int length = (int)word.length();

	TrieNode *nood = root;
	
	for (int lvl = 0; lvl < length; ++lvl) {
		int num = tolower(word[lvl]) - ((int)'a');
		if (nood->next[num] == nullptr) {
			nood->next[num] = new TrieNode;
			++elementCount;
		}
		nood = nood->next[num];
	}
	nood->isLeaf = true;
}

bool Trie::contains(const std::string &word) const {
	int length = (int)word.length();
	TrieNode *nood = root;

	for (int lvl = 0; lvl < length; ++lvl) {
		int num = tolower(word[lvl]);
		num -= 97;
		if (nood->next[num] == nullptr) {
			return false;
		}
		nood = nood->next[num];
	}
	return (nood != nullptr && nood->isLeaf);
}

bool Trie::containsAtLeast(const std::string &word) const {
	int length = (int)word.length();
	TrieNode *nood = root;

	for (int lvl = 0; lvl < length; ++lvl) {
		int num = tolower(word[lvl]);
		num -= 97;
		if (nood->next[num] == nullptr) {
			return false;
		}
		nood = nood->next[num];
	}
	return (nood != nullptr);	// ONLY DIFFERENCE IS NOT NECESSARILY LEAF
}

void Trie::remove(const std::string &word) {
    // TODO: remove the following like that we've added to avoid a warning
    //(void)word;
	if (!contains(word)) {
		return;
	}
    // TODO: implement `remove`
	int length = (int)word.length();
	TrieNode *nood = root;

	for (int lvl = 0; lvl < length; ++lvl) {
		int num = tolower(word[lvl]) - ((int)'a');
		nood = nood->next[num];
	}

	// online code
	/*if ((int)word.size() > 0) {
		deleteHelper(root, word, 0, (int)word.size());
	}*/

	//return (nood != nullptr && nood->isLeaf);
	return;
}

//bool deleteHelper(TrieNode *pNode, const std::string &word, int level, int len) {
	//if (pNode) {
	//	// Base case
	//	if (level == len && pNode->isLeaf) {
	//		// Unmark leaf node
	//		pNode->isLeaf = true;
	//		// If empty, node to be deleted
	//		if (isItFreeNode(pNode)) {
	//			return true;
	//		}
	//		else return false;
	//	}
	//	else { // Recursive case
	//		int index = INDEX(key[level]);
	//		if (deleteHelper(pNode->children[index], key, level + 1, len)) {
	//			// last node marked, delete it
	//			FREE(pNode->children[index]);
	//			// recursively climb up, and delete eligible nodes
	//			return (!leafNode(pNode) && isItFreeNode(pNode));
	//		}
	//	}
	//}

	//return false;
//}

void Trie::clear() {
    // TODO: implement `clear`
	delete root;
}

size_t Trie::size() const {
    return elementCount;
}

Trie::~Trie() {
    clear();
}
