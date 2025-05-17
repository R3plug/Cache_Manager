/**
* @author - Phillip Davis
* @file binary_search_tree.cpp -  This .CPP file implements the methods in the binary_search_tree.h file.
* 03/6/2025 - P. Davis Created file and addedfunctions to be implemented.
* 04/14/2025 - P.Davis Finished most functionality
* 04/15/2025 - P.Davis Finished last of functionality and debugging edge cases.
* 05/03/2025 - P.Davis Edited add function to work with cache manager including DllNode
*/


#include "tree_node.h"
#include "binary_search_tree.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <fstream>
extern std::ofstream& getOutFile();


/**
 * @namespace 
 * @brief A class representing a Binary Search Tree (BST).
 *
 * This namespace provides helper functions to perfrom recursive action 
 * for adding and removing nodes.
 */
namespace treeHelper{

    /**
     * @brief Removes a node with the specified key from the tree.
     *
     * @param key The key of the node to remove.
     * @return True if the node was removed, false if the key wasn't found.
     */
    int calcHeight(TreeNode* root){
        if(root==nullptr){
            return 0;
        }

        int left =calcHeight(root->left);
        int right =calcHeight(root->right);
        
        root->height = std::max(left,right)+1;

        return root->height;
    }
    
    /**
     * @brief Removes a node with the specified key from the tree.
     *
     * @param key The key of the node to remove.
     * @return True if the node was removed, false if the key wasn't found.
     */
    TreeNode* add(TreeNode* root, int key, DllNode* dllNode){
        //Base case to insert node
        if(root == nullptr){
            root = new TreeNode(key, dllNode);
            root->key = key;
            return root;
            
        }
        else{
            if(root->key >key){
                root->left=add(root->left,key, dllNode);
                
            }
            else {
                root->right = add(root->right,key, dllNode);

            }
        }
            
        return root;
            
    }

    /**
     * @brief Handles deletion and finding in order successor for node removal
     *
     * @param root The node being removed
     * @return returns the new root of the subtree
     */
    TreeNode* inOrderSuccessor(TreeNode* root){
        //if leaf node delete
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            return nullptr;
        }
        TreeNode* temp = nullptr;
        //if no right node delete node and replace with the left tree
        if(root->right ==nullptr){
            temp=root;
            root = root->left;
            delete temp;
            return root;
        }
        //if only right nodes delete node and connect right tree
        if(root->right->left==nullptr){
            temp=root;
            root = root->right;
            delete temp;
            return root;
        }

        TreeNode* parent = root->right;
        //traverse to the parent of the left most node
        while(parent->left->left != nullptr) {
            parent = parent->left;
        }
        //node to be swapped with root
        TreeNode* successor = parent->left;
        
        root->key = successor->key;
        
        parent->left = successor->right;
        delete successor;
        return root;
    }
        
    /**
     * @brief Helper function to find the node to delete
     *
     * @param key, root The key of the node to remove. and the root of the tree
     * @return returns the root of the tree
     */
    TreeNode* remove(TreeNode* root, int key){
        if(root == nullptr){
            return root;
        }
        if(root->key == key){
            return inOrderSuccessor(root);
            
            
        }
        else if(key>root->key){
            root->right=remove(root->right,key);
        }
        else{
            root->left = remove(root->left, key);
        }

        return root;
    }
    /**
     * @brief calculates the number of nodes in a tree 
     *
     * @param root The root of the tree
     * @return Int the number of roots in the tree
     */
    int calcNumNodes(TreeNode* root){
        if(root==nullptr){
            return 0;
        }

        return 1 + calcNumNodes(root->left)+calcNumNodes(root->right);

    }

    /**
     * @brief Helper function to see if the tree contains a node
     *
     * @param root,key Theroot of the tree and key of the node to find.
     * @return True if the node was found, false if the key wasn't found.
     */
    bool containsHelper(TreeNode* root, int key) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == key) {
            return true;
        }
        if (root->key > key) {
            return containsHelper(root->left, key);
        }
        return containsHelper(root->right, key);
    }
    
        
}

/**
 * @class BinarySearchTree
 * @brief A class representing a Binary Search Tree (BST).
 *
 * This class provides methods to manipulate and traverse a binary search tree.
 * It supports operations like adding and removing nodes, checking if a key exists,
 * calculating the height of the tree, and printing the tree in various traversal orders.
 */

    /**
     * @brief Default constructor for BinarySearchTree.
     *
     * Initializes an empty binary search tree.
     */
    BinarySearchTree::BinarySearchTree(){
        this->root = nullptr;
    }

    /**
     * @brief Destructor for BinarySearchTree.
     *
     * Frees the dynamically allocated memory by deleting all nodes in the tree.
     */
    BinarySearchTree::~BinarySearchTree(){
        clear();
        
    }

    /**
     * @brief Adds a node with the specified key to the tree.
     *
     * @param key The key to be added to the tree.
     */
    void BinarySearchTree::addToTree(int key, DllNode* dllNode){
        
        //calls a helper function for adding a tree node
        root = treeHelper::add(getRoot(), key, dllNode);
        root->numberOfNodes=treeHelper::calcNumNodes(root);
        treeHelper::calcHeight(root);
    }

    /**
     * @brief Removes a node with the specified key from the tree.
     *
     * @param key The key of the node to remove.
     * @return True if the node was removed, false if the key wasn't found.
     */
    bool BinarySearchTree::removeNode(int key){
        int preRemoval =root->numberOfNodes;
        root = treeHelper::remove(root, key);
        treeHelper::calcHeight(root);
        root->numberOfNodes=treeHelper::calcNumNodes(root);
        if(preRemoval>root->numberOfNodes){
            return true;
        }
        return false;

    }

    /**
     * @brief Gets the height of the tree.
     *
     * The height of the tree is defined as the length of the longest path from
     * the root to a leaf node.
     *
     * @return The height of the tree.
     */
    int BinarySearchTree::getHeightOfTree() const{
        return root->height;
    }

    /**
     * @brief Gets the number of nodes in the tree.
     *
     * @return The number of nodes in the tree.
     */
    int BinarySearchTree::getNumberOfTreeNodes() const{
        if(root == nullptr){
            return 0;
        }else{
            int nodes = root->numberOfNodes;
            return nodes;
        }
        
    }
    /**
     * @brief Clears the entire tree.
     *
     * Deletes all the nodes in the tree, freeing up memory.
     */
    void BinarySearchTree::clear(){
        // running delete tree from the root deletes the whole tree
        deleteTree(root);
        root = nullptr;
    }

    /**
     * @brief Checks if the tree contains a node with the specified key.
     *
     * @param key The key to search for in the tree.
     * @return True if the key exists in the tree, false otherwise.
     */
    bool BinarySearchTree::contains(int key) const{
        return treeHelper::containsHelper(root,key);
    }

    /**
     * @brief Gets the root node of the tree.
     *
     * @return A pointer to the root node of the tree.
     */
    TreeNode* BinarySearchTree::getRoot() const{
        return root;
    }

    /**
     * @brief Checks if the tree is empty.
     *
     * @return True if the tree is empty, false otherwise.
     */
    bool BinarySearchTree::isEmpty() const{
        //if there is a root node then the tree is not empty
        if(root==nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * @brief Prints the data of a specific node.
     *
     * This function prints the key, number of nodes in the subtree, and height of the given node.
     *
     * @param node A pointer to the node whose data is to be printed.
     */
    void BinarySearchTree::printNodeFromTree(TreeNode* node) const{
        std::ofstream& file = getOutFile();

        std::cout<<"Node key: "<<node->key<<std::endl;
        file<<"Node key: "<<node->key<<std::endl;
    }

    /**
     * @brief Performs an in-order traversal of the tree and prints the nodes.
     *
     * In-order traversal visits the left subtree, the node, and then the right subtree.
     */
    void BinarySearchTree::printInOrder() const{
        std::ofstream& file = getOutFile();
        file<<"Performing In-order Traversal\n";
        std::cout<<"Performing In-order Traversal\n";
        printInOrderHelper(getRoot());
        file<<"End of binary search tree"<<std::endl;
        std::cout<<"End of binary search tree"<<std::endl;
    }

    /**
     * @brief Performs a pre-order traversal of the tree and prints the nodes.
     *
     * Pre-order traversal visits the node, the left subtree, and then the right subtree.
     */
    void BinarySearchTree::printPreOrder() const{
        std::ofstream& file = getOutFile();

        file<<"Performing Pre-order Traversal\n";
        std::cout<<"Performing Pre-order Traversal\n";
        printPreOrderHelper(getRoot());
    }

    /**
     * @brief Performs a post-order traversal of the tree and prints the nodes.
     *
     * Post-order traversal visits the left subtree, the right subtree, and then the node.
     */
    void BinarySearchTree::printPostOrder() const{
        std::ofstream& file = getOutFile();

        file<<"Performing Post-order Traversal\n";
        std::cout<<"Performing Post-order Traversal\n";
        printPostOrderHelper(getRoot());
    }

    /**
     * @brief Performs a depth-first traversal (same as pre-order traversal) and prints the nodes.
     *
     * Depth-first traversal visits the node first, then the left subtree, and then the right subtree.
     */
    void BinarySearchTree::printDepthFirst() const{
        std::ofstream& file = getOutFile();

        file<<"Performing Depth First via PreOrder traversal\n";
        std::cout<<"Performing Depth First via PreOrder traversal\n";
        printPreOrder();

    }

    /**
     * @brief Performs a breadth-first traversal of the tree and prints the nodes.
     *
     * Breadth-first traversal visits nodes level by level, from left to right.
     */
    void BinarySearchTree::printBreadthFirst() const{
        std::ofstream& file = getOutFile();

        file<<"Performing Breadth FIrst Search\n";
        std::cout<<"Performing Breadth First Search\n";
        std::queue<TreeNode*> queue;
        queue.push(root);
        TreeNode* temp = nullptr;

        while(queue.size()!=0){
            temp = queue.front();
            if(temp->left){
                queue.push(temp->left);
            }
            if(temp->right){
                queue.push(temp->right);
            }
            printNodeFromTree(temp);
            queue.pop();

        }

    }

    /**
     * @brief Deletes the tree starting from the specified node.
     *
     * Recursively deletes all nodes in the tree.
     *
     * @param node The starting node to begin deleting the tree.
     */
    void BinarySearchTree::deleteTree(TreeNode* node){
       
        if(node==nullptr){
            return;
            
        }
        deleteTree(node->left);
        deleteTree(node->right);
        delete(node);
        node=nullptr;
        

    }

    /**
     * @brief Helper function to calculate the height of a node.
     *
     * This function is used by `getHeightOfTree` to calculate the height of the tree.
     *
     * @param node A pointer to the node whose height is to be calculated.
     * @return The height of the given node.
     */
    int BinarySearchTree::getHeight(TreeNode* node) const{
        return node->height;
    }

    /**
     * @brief Helper function for recursive in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
     */
    void BinarySearchTree::printInOrderHelper(TreeNode* node) const{
        if(node==nullptr){
            return;
        }
        printInOrderHelper(node->left);
        printNodeFromTree(node);
        printInOrderHelper(node->right);
    }

    /**
     * @brief Helper function for recursive pre-order traversal.
     *
     * This function is called recursively to perform a pre-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the pre-order traversal.
     */
    void BinarySearchTree::printPreOrderHelper(TreeNode* node) const{
        if(node==nullptr){
            return;
        }
        printNodeFromTree(node);
        printPreOrderHelper(node->left);
        printPreOrderHelper(node->right);
    }

    /**
     * @brief Helper function for recursive post-order traversal.
     *
     * This function is called recursively to perform a post-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the post-order traversal.
     */
    void BinarySearchTree::printPostOrderHelper(TreeNode* node) const{
        if(node==nullptr){
            return;
        }
        printPostOrderHelper(node->left);
        printPostOrderHelper(node->right);
        printNodeFromTree(node);

    }

        /**
     * @brief Performs an reverse traversal of the tree and prints the nodes.
     *
     * Reverse traversal visits the right subtree, the node, and then the left subtree.
     */
    void BinarySearchTree::printReverseOrder() const{
        std::ofstream& file = getOutFile();

        file<<"Performing reverse-order traversal"<<std::endl;
        std::cout<<"Performing reverse-order traversal"<<std::endl;
        printReverseOrderHelper(getRoot());
        file<<"End of binary search tree"<<std::endl;
        std::cout<<"End of binary search tree"<<std::endl;
    }

    /**
    *
    * printRange
    *
    * Method to traverse and print out the cache information given a low and high value.
    *
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
    */
    void BinarySearchTree::printRange(int low, int high){
        printRangeHelper(getRoot(),low, high);
        

   }

       /**
     * @brief Helper function for recursive in-order traversal.
     *
     * This function is called recursively to perform an in-order traversal starting from the given node.
     *
     * @param node A pointer to the node from which to begin the in-order traversal.
     */
    void BinarySearchTree::printReverseOrderHelper(TreeNode* node) const{
        if(node== nullptr){
            return;
        }
        printReverseOrderHelper(node->right);
        node->fifoNode->printNode();
        printReverseOrderHelper(node->left);

    }

    /**
    *
    * printRangeHelper
    *
    * Method to traverse and print out the cache information given a low and high value.
    *
    * @param    low			the lower bound (inclusive) of the range to print
    * @param	high		the higher bound (inclusive) of the range to print
    *
    * @return   nothing, but prints out the keys for the cache between low and high
    */
   void BinarySearchTree::printRangeHelper(TreeNode* node, int low, int high){
        if(node==nullptr || node->key>high){
            return;
        }
        printRangeHelper(node->left,low, high);
        if(node->key>=low||node->key<=high){
            node->fifoNode->printNode();
        }
        printRangeHelper(node->right, low, high);
   }

    



