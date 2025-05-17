/**
*
* cache_manager.cpp : This is the implementation file for cache_manager.h.
*
* 02/28/2025 - Created by P. Davis all functions created and tested good.
* 03/01/2025 - pdavis changed functions to use hashnode
* 04/03/2025 - P.Davis Added BST functionality: getBST, printRange, printSort.
* edited: add, remove, and clear
*/
#include <unordered_map>
#include <iostream>
#include<fstream>
#include "cache_manager.h"
#include "doubly_linked_list.h"
#include "dll_node.h"
#include "hash_node.h"
#include "binary_search_tree.h"

extern std::ofstream& getOutFile();

/**
	*
	* getTable
	*
	* Method to return the hash table
	*
	* @param    none
	*
	* @return	the hash table
	*/
std::unordered_map<int,HashNode*>* CacheManager::getTable(){
    
    return hashTable;
}

/**
*
* getList
*
* Method to return the FIFO list
*
* @param    none
*
* @return	the FIFO list
*/
DoublyLinkedList* CacheManager::getList(){
    return doublyLinkedList;
}

/**
	*
	* getBST
	*
	* Method to return the BST
	*
	* @param    none
	*
	* @return	the FIFO list
	*/
BinarySearchTree* CacheManager::getBst(){
    return binarySearchTree;
}


/**
*
* getSize
*
* Method to return the number of items in the CacheManager
*
* @param    none
*
* @return	number of items in the CacheManager if dll and hashtable size dont match returns -1
*/
int CacheManager::getSize(){
    int dllSize =getList()->getSize();
    int hashTableSize =getTable()->size();

    //if the dll and hashtable are the same size return their size otherwise
    //something is wrong 
    if(dllSize == hashTableSize)
    {
        return dllSize;
    }
    else{
        return -1;
    }
}


/**
*
* isEmpty
*
* Method to check if CacheManager is empty
*
* @param    none
*
* @return   true if the CacheManager has zero entries, false otherwise
*/
bool CacheManager::isEmpty(){
    if(getList()->isEmpty()&&getTable()->empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}


/**
*
* add
*
* Method to add a node to the CacheManager
*
* @param    curKey    key for this node
* @param    myNode    new node to add to the table
*
* @return   true if success, false otherwise
*/
bool CacheManager::add(int curKey, DllNode* myNode){
    if(contains(curKey)){
        return false;
    }
    //place the new node at the front of the fifo list, in the hashtable and BST
    getList()->insertAtHead(curKey,myNode);
    HashNode* temp = new HashNode(curKey,myNode);
    bool hashInsert = getTable()->insert({curKey, temp}).second;
    this->binarySearchTree->addToTree(curKey,myNode);

    //if the cache manager is full remove the oldest item.
    if(getList()->getSize()>getMaxCacheSize())
    {
        DllNode* remove = doublyLinkedList->tail;
        getTable()->erase(remove->key);
        getBst()->removeNode(remove->key);
        getList()->removeTailNode();
    }

    //check if the operation was successfull
    if(hashInsert == true && getList()->head->key == curKey){
        return true;
    }
    else
    {
        return false;
    }

}

/**
*
* remove
*
* Method to remove node with curKey
*
* @param    key     key of node to remove
*
* @return   true if success, false otherwise
*/
bool CacheManager::remove(int curKey){
    //get original list size
    int dllSize =getList()->size;

    //remove node from each
    getList()->remove(curKey);
    getTable()->erase(curKey);
    getBst()->removeNode(curKey);

    //check that the dll is one smaller and the hashtable doesnt contain the key
    if(getList()->size<dllSize && getTable()->find(curKey) == getTable()->end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
*
* clear
*
* Method to remove all entries from the CacheManager
*
* @param    none
*
* @return   nothing, but will delete all entries from the CacheManager
*/
void CacheManager::clear(){
    //clears both lists
    getTable()->clear();
    getList()->clear();
    getBst()->clear();
}

/**
*
* getItem
*
* Method to retrieve item from the CacheManager
*
* @param    curKey  retrieve node from CacheManager with curKey value
*
* @return   pointer to the DllNode
*/
DllNode* CacheManager::getItem(int curKey){
    DllNode* temp =nullptr;
    //if key exisits retrieve the dllnode pointer from the hash table and move it to the front of the queue
    if(getTable()->find(curKey) != getTable()->end()){
        temp = getTable()->at(curKey)->node;
        getList()->moveNodeToHead(temp);
    }
    
    return temp;
}

/**
*
* getMaxCacheSize
*
* Method to retrieve max size of cache from the CacheManager
*
* @param    none
*
* @return   max size of cache manager
*/
int CacheManager::getMaxCacheSize(){
    return maxCacheSize;
}

/**
*
* contains
*
* Method to determine if a key value is in the cache
*
* @param    curKey  retrieve node from cacheManager with curKey value
*
* @return   true if exists, false otherwise
*/
bool CacheManager::contains(int curKey){
    bool exists = (getTable()->find(curKey) != getTable()->end());
    //if exists it has been accessed and move it to the fornt of the list
    if(exists){
        getList()->moveNodeToHead(getTable()->at(curKey)->node);
    }
    return exists;
}


/**
*
* printCache
*
* Method to print out the cache information
*
* @param    none
*
* @return   pointer to the hash table array
*/
void CacheManager::printCache(){
    //access the out file
    std::ofstream& file = getOutFile();

    //exports data to console and file
    std::cout<<"\n\nPrinting out the cache contents\n\n";
    file<<"\n\nPrinting out the cache contents\n\n";

    std::cout<<"Here are the FIFO list contents:\n";
    file<<"Here are the FIFO list contents:\n";

    getList()->printList();

    std::cout<<"End of FIFO List\n\n";
    file<<"End of FIFO List\n\n";
    
    std::cout<<"Here are the Hash Table contents ("<<getTable()->size()<<" entries):\n";
    file<<"Here are the Hash Table contents ("<<getTable()->size()<<" entries):\n";
    //for each node in
    DllNode* temp = getList()->head;
    while(temp != nullptr){
        std::cout<<"FIFO info from cacheManager: Node key: "<<temp->key<<std::endl;
        file<<"FIFO info from cacheManager: Node key: "<<temp->key<<std::endl;
        temp=temp->next;
    }
    std::cout<<"End of table\n\n";
    file<<"End of table\n\n";

    getBst()->printInOrder();
    std::cout<<std::endl;
    file<<std::endl;
    getBst()->printReverseOrder();
    std::cout<<std::endl;
    file<<std::endl;

    std::cout<<"End of cache contents\n\n";
    file<<"End of cache contents\n\n";
}

    /**
	*
	* printRange
	*
	* Method to print out nodes within a range of keys
	*
	* @param    int, int low and high
	*
	* @return   nothing but will print dll nodes
	*/
    void CacheManager::printRange(int low, int high){
        getBst()->printRange(low,high);

    }

    /**
    *
    * printSort
    *
    * Method to print out the cache information in sorted order min max
    *
    * @param    none
    *
    * @return   nothing but prints out dll nodes in sorted order
    */
    void CacheManager::printSort(bool ascending){
        std::ofstream& file = getOutFile();
        std::cout<<std::endl;
        file<<std::endl;

        if(ascending){
            binarySearchTree->printInOrder();
        }else{
            getBst()->printReverseOrder();
        }
    }



