/**
 * Trie.h
 *
 * EECS 281: Lab 8
 * Spring 2017
 *
 * Implements a trie.
 */

#ifndef Trie_h
#define Trie_h

#include <string>
#include <iostream>

const int ALPHABET_SIZE = 26;

struct TrieNode {
    // TODO: add member variables
	TrieNode() {
		isLeaf = false;
		//std::cout << "CONSTRUCTOR RUNS\n";
		for (int i = 0; i < ALPHABET_SIZE; ++i) {
			next[i] = nullptr;
		}
	}
	TrieNode *next[ALPHABET_SIZE];
	bool isLeaf;
	int val;
    ~TrieNode();
};

class Trie {

public:
    //Inserts `word` into the trie if the trie does not already contain it.
    void insert(const std::string &word);

    //Returns true if the trie contains `word`.
    bool contains(const std::string &word) const;

	//Returns true if the trie contains something starting with `word`.
	bool containsAtLeast(const std::string &word) const;

    //Removes `word` from the trie if the trie contains it.
    void remove(const std::string &word);

    //Removes all elements from the trie.
    void clear();

    //Returns the number of elements in the trie.
    size_t size() const;

    //Destructor.
    ~Trie();

private:
    TrieNode* root = nullptr;
    size_t elementCount = 0;

    // add private helper functions if you'd like!
	//TrieNode *newNode(void) {
	//	TrieNode *pNode = NULL;
	//	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	//	//pNode = new TrieNode
	//	if (pNode) {
	//		pNode->isLeaf = false;
	//		for (int i = 0; i < ALPHABET_SIZE; i++)
	//			pNode->children[i] = NULL;
	//	}
	//	return pNode;
	//}
};

#endif /* Trie_h */
