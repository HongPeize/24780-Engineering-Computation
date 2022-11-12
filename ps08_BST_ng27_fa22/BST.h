/*
Nestor Gomez
24-780B Engineering Computation
PS08 - Binary Search Tree (pointer implementation)
Due Tues, Nov. 15, 2022

*/

#pragma warning(disable:4996)  // this helps with _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

// note, class "T" must be comparable using <, ==, and >
template <class T>
class TreeNode {
public:
	T theItem;  // T is the type of item stored (could be string, float, class object, etc.)
	// whatever is stored must be copiable and comparable.
	int count;
	TreeNode* leftChild = nullptr;
	TreeNode* rightChild = nullptr;
	TreeNode() { count = 0; }
	TreeNode(const T& newItem) {
		theItem = newItem; count = 1;
	}
};

template <class T, class TN>
class BST
{
protected:
	int nodeCount = 0; // "manually" maintained by insertItem and deleteItem functions
	TN* theRoot;

public:
	int count() { return nodeCount; }
	TN* root() { return theRoot; }

	// if a node that matches the given item is found, delete the node from the tree
	// returns true if the item was found and deleted, returns false if not found
	// (a bit complex, so we'll write together in lecture and then you can just use Nestor's)
	bool deleteItem(const T& anItem, TN* parentNode = nullptr, TN* currNode = nullptr);

public:
	// For PS08, create the code for these four functions

	// Used to insert item into BST. If newItem is invalid, do nothing
	// If item already in BST, update the item's count
	// If item is not already in BST, place it at the correct location and increment 
	// the overall nodeCount of the tree
	void insertItem(const T& newItem, TN* startNode = nullptr);

	// Returns node that matches given item. Returns nullptr if item is not in tree
	// Optionally starts the search at a node that is not the root, allowing for recursive
	// searching (although search can be done without recursion, ignoring second parameter)
	TN* findItem(const T& anItem, TN* startNode = nullptr);

	// Finds the item and returns the item count. Makes use of findItem() function
	// Returns zero if the item is not in the BST
	int retrieveItemCount(const T& anItem);

	// Tranverses the BST and prints out (to a string stream) each of the items (on its own line)
	// in the BST in correct order, along with the item's count (can use recursion)
	// typical output:    
	//			 here {8}
	//           justice {2}
	void printInOrder(stringstream& out, TN* startNode = nullptr);

};

// Including function definitions in .h because linker has trouble
// using template classes if compiler cannot access at compile time

template <class T, class TN>
bool BST<T, TN>::deleteItem(const T& anItem, TN* parentNode, TN* currNode)
{
	// if tree is not empty
	if (theRoot != nullptr) {
		// is this the first call from "outside"
		if (parentNode == nullptr && currNode == nullptr) {
			currNode = theRoot;
		}

		if (currNode == nullptr)
			return false;   // item not found. possible exit from function

		else if (currNode->theItem == anItem) { // found the node, time to delete
			// if no children, just delete it
            if (currNode->leftChild ==nullptr && currNode -> rightChild ==nullptr){
                if (parentNode==nullptr){
                    theRoot == nullptr;
                }
                if (parentNode->leftChild == currNode){
                    parentNode->leftChild = nullptr;
                }else{
                    parentNode->rightChild = nullptr;
                }
                delete currNode;
            }
			// if only left child, promote left child of current from grandchild of parent to child of parent node
            else if (currNode->rightChild == nullptr){ //only has left child
                if (parentNode==nullptr){
                    theRoot == currNode->leftChild;
                }
                else if (parentNode->leftChild == currNode){
                    parentNode->leftChild = currNode->leftChild;
                }else{
                    parentNode->rightChild = currNode->leftChild;
                }
                delete currNode;
            }
			// if only right child, promote right child of current from grandchild of parent to child of parent node
            else if (currNode->leftChild == nullptr){
                if (parentNode == nullptr){
                    theRoot == currNode->rightChild;
                }
                else if (parentNode->leftChild == currNode){
                    parentNode->leftChild = currNode->rightChild;
                }else{
                    parentNode->rightChild = currNode->rightChild;
                }
                delete currNode;
            }
            // if there are two children (neither leftChild nor rightChild is nullptr)
            else{
                // find right-most node of left subtree
                TN* targetNode = currNode->leftChild;
                TN* targetParent = currNode;
                
                while (targetNode->rightChild != nullptr){
                    targetParent = targetNode;
                    targetNode = targetNode->rightChild;
                }
                // swap currNode and targetNode
                //    make a copy of currNode and complete swap
                T temp1 = currNode->theItem;
                int temp2 = currNode->count;
                currNode->theItem = targetNode->theItem;
                currNode->count = targetNode->count;
                targetNode->theItem = temp1;
                targetNode->count = temp2;
                // recursive call, but node to delete is guaranteed to have 0 or 1 child
                return deleteItem(anItem, targetParent, targetNode);
            }
            nodeCount--;
            return true;
		}
		// keep looking in left or right sub-tree, with current as parent
		else if (anItem < currNode->theItem)
			return deleteItem(anItem, currNode, currNode->leftChild); // recursive call
		else
			return deleteItem(anItem, currNode, currNode->rightChild); // recursive call
	}

	return false;
}

template<class T, class TN>
inline void BST<T, TN>::insertItem(const T& newItem, TN* currNode)
{
    TN* newNode = new TN(newItem);
    if (theRoot == nullptr){
        theRoot = newNode;
        nodeCount = 1;
    }else{
        if (currNode == nullptr){
            currNode = theRoot;
        }
        if (newItem == currNode->theItem){ //equal
            currNode->count++;
        }else if (newItem < currNode->theItem){ //smaller
            if (currNode->leftChild == nullptr){
                currNode -> leftChild = newNode;
                nodeCount++;
            }
            else{
                insertItem(newItem, currNode->leftChild);
            }
        }else{ //greater
            if (currNode->rightChild == nullptr){
                currNode -> rightChild = newNode;
                nodeCount++;
            }else{
                insertItem(newItem, currNode->rightChild);
            }
        }
    }
}

template<class T, class TN>
inline int BST<T, TN>::retrieveItemCount(const T& anItem){
    if (findItem(anItem)!=0){
        return findItem(anItem)->count;
    }else { return 0; }
}

template<class T, class TN>
inline void BST<T, TN>::printInOrder(stringstream& out, TN* currNode)
{
    if (currNode == nullptr){
        currNode = theRoot;
    }
    if (theRoot != nullptr && currNode->count > 0){
        if (currNode->leftChild != nullptr){
            printInOrder(out, currNode->leftChild);
        }
        out << currNode->theItem << " {" << currNode->count << "}" <<endl;

        if (currNode->rightChild != nullptr){
            printInOrder(out, currNode->rightChild);
        }
    }else{out << "The BST is empty" << endl;}
}

template<class T, class TN>
inline TN* BST<T, TN>::findItem(const T& anItem, TN* currNode){
    if (theRoot!=nullptr){
        if (currNode == nullptr){
            currNode = theRoot;
        }
        if (anItem == currNode->theItem){
            return currNode;
        }else if(anItem < currNode->theItem){
            if (currNode->leftChild == nullptr){
                return nullptr;
            }else{
                return findItem(anItem, currNode->leftChild);
            }
        }else{
            if (currNode->rightChild == nullptr){
                return nullptr;
            }else{
                return findItem(anItem, currNode->rightChild);
            }
        }
    }else{return nullptr;}
}
