/**
*
* hash_node.h : This is the node struct header file for HashTable, used in hash_table.cpp
*
* 01/16/25 - Created by H. Hui
*
*2/21/25 - P. Davis Added new constructor for Gtest Testing
*03/01/2025 pdavis recreated file to use in unordered list to create low coupling. added linkedlist node member variable.
* removed uneeded variables;
*/

#ifndef _HASH_NODE
#define _HASH_NODE

#include <string>
#include "dll_node.h"

extern void logToFileAndConsole(std::string msg);

// Define a structure for a node in the hash table
struct HashNode {
	
	int key;                                                           // Value stored in the node
	DllNode* node;												   // hash code based on array size
                                                   

	HashNode(int val, DllNode* listNode){
		key=val;
		node = listNode;
		
	}

};

#endif 