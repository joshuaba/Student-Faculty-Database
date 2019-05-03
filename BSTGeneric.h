#include <iostream>
#include <cstdlib>
#include <string>
#include "TreeNode.h"

using namespace std;

template <class T>
class BST
{
    public:
        BST(); //default constructor
        virtual ~BST();
        void insert(T value); //value is the key
        bool contains(T value); //AKA search
        //bool deleteNode(int value); //delete the node at position value
        TreeNode<T>* getSucessor(TreeNode<T> *d);
        bool deleteR(T value);
        T find(T value); //find the element value in the BST

        TreeNode<T>* getMin(); //get the minimum value of the tree
        TreeNode<T>* getMax(); //get the maximum value of the tree
        bool isEmpty(); //returns true if the tree is empty
        void printTree(); //print the Tree
        void printTreeToFile(string fileToWrite); //print the tree out to the file so we can read from it later
        void recPrint(TreeNode<T>* node);
        void recPrintToFile(TreeNode<T>* node, string fileToWrite);
    private:
        TreeNode<T> *root;
};

template <class T>
BST<T>::BST() //default constructor
{
    root = nullptr; //empty tree
}

template <class T>
BST<T>::~BST()
{
	//iterate and delete
    //research
}

template <class T>
void BST<T>::printTree()
{
    recPrint(root);
}

template <class T>
void BST<T>::printTreeToFile(string fileToWrite)
{
	recPrintToFile(root, fileToWrite);
}

template <class T>
void BST<T>::recPrint(TreeNode<T> *node)
{
    if(node == nullptr)
    {
        return;
    }

    recPrint(node->left);
    (node->key).getInformation();
    recPrint(node->right);
}

template <class T>
void BST<T>::recPrintToFile(TreeNode<T> *node, string fileToWrite)
{
	if(node == nullptr)
	{
		return;
	}

	recPrintToFile(node->left, fileToWrite);
	(node->key).writeInformationToDisk(fileToWrite);
	recPrintToFile(node->right, fileToWrite);
}

template <class T>
bool BST<T>::isEmpty()
{
    return (root == nullptr);
}

template <class T>
void BST<T>::insert(T value)
{
    //check if value exist, if not continue

    TreeNode<T> *node = new TreeNode<T>(value); //key is now set to value

    if(isEmpty()) //empty Tree
    {
        root = node;
    }

    else //not an empty tree, need to find insertion point
    {
        TreeNode<T> *current = root;
        TreeNode<T> *parent; //empty node

        while(true)
        {
            parent = current;

            //error checking
            if(value == current->key)
            {
                cout << "Value already in BST." << endl;
                break;
            }

            else if(value < current->key)
            {
                current = current->left; //going left

                if(current==nullptr) //we found a home for our new node
                {
                    parent->left = node;
                    break;
                }
                //else keep looping
            }

            else
            {
                current = current->right;

                if(current == nullptr)
                {
                    parent->right = node;
                    break;
                }
            }
        }

    }
}

template <class T>
bool BST<T>::contains(T value)
{
    if(isEmpty())
    {
        return false;
    }

    else //not an empty tree
    {
        TreeNode<T> *current = root;

        while(current->key != value)
        {
            if(value < current->key) //go left
                current = current->left;
            else
                current = current->right;

            if(current == nullptr)
                return false;
        }
    }
    return true;
}

template <class T>
T BST<T>::find(T value)
{
	if(isEmpty())
	{
		cout << "The requested element is not found in the database. Ending program" << endl;
		exit(1); //make a call to exit and exit the program
	}

	else
	{
		TreeNode<T> *current = root;

		while(current->key != value)
		{
			if(value < current->key)
				current = current->left;
			else
				current = current->right;

			if(current == nullptr)
			{
				cout << "The requested element is not found in the database. Ending program" << endl;
				exit(1);
			}
		}

		return current->key;
	}
}

/*
template <class T>
void operator =(BST<T>& tree1, BST<T>& tree2)
{
	tree1.root = tree2.root;

	tree1.root = tree1.root->left;
}
*/

template <class T>
bool BST<T>::deleteR(T k)
{
    if(isEmpty())
    {
        cerr << "Database is empty! Ending program" << endl;
        exit(1);
        return false;
    }

    //check if key/value exists before continuing to delete
    if(!contains(k))
    {
        cerr << "The requested person is not in the database! Ending program" << endl;
        exit(1);
        return false;
    }

    TreeNode<T> *current = root;
    TreeNode<T> *parent = root;
    bool isLeft;

    //find the node we want to delete
    while(current->key != k)
    {
        parent = current;

        if(k < current->key) //left child
        {
            isLeft = true;
            current = current->left;
        }

        else //rightchild
        {
            isLeft = false;
            current = current->right;
        }

        if(current == nullptr)
        {
        	return false;
        }
    }

    //at this point we found our node

    if(current->left == nullptr && current->right == nullptr) //no children ; leaf node
    {
        if(current == root) //the tree has the root as its only element
        {
            root = nullptr;
        }
        else if(isLeft) //the child is a left child
        {
            parent->left = nullptr;
        }
        else //is right child
        {
            parent->right = nullptr;
        }
    }

    else if(current->right == nullptr) //the node we want to delete has no right child
    {
        if(current == root)
            root = current->left;

        else if(isLeft) //the node we are deleting is a left child
        {
            parent->left = current->left;
        }

        else //the node we are deleting is a right child of the parne t
        {
            parent->right = current->left;
        }
    }

    else if(current->left == nullptr) //node we want to delete has no left child, exact opposite of above
    {
        if(current == root)
            root = current->right;

        else if(isLeft) //node we want to delete is a left child of a parent node
        {
            parent->left = current->right;
        }

        else //node we want to delete is a right child of a parent node
        {
            parent->right = current->right;
        }
    }

    else //the node we want to delete has two children
    {
        //find the successor of the node to be deleted (current)
        TreeNode<T> *successor = getSucessor(current);

        if(current == root)
        {
            root = successor;
        }

        else if(isLeft)
        {
            parent->left = successor;
        }

        else
        {
            parent->right = successor;
        }

        successor->left = current->left;
    }

    return true;
}

template <class T>
TreeNode<T>* BST<T>::getSucessor(TreeNode<T>* d) //d is the node to be deleted
{
    TreeNode<T> *sp = d; // successors parent
    TreeNode<T> *successor = d;
    TreeNode<T> *current = d->right;

    while(current != nullptr)
    {
        sp = successor;
        successor = current;
        current = current->left;
    }

    if(successor != d->right)
    {
        sp->left = successor->right;
        successor->right = d->right;
    }

    return successor;
}

