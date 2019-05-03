#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

template <class T>
class TreeNode
{
    public:

        TreeNode(); //default constructor
        TreeNode (T key); //overloaded constructor
        virtual ~TreeNode();

        T key;
		TreeNode<T> *left;
		TreeNode<T> *right;
};

template <class T>
TreeNode<T>::TreeNode()
{
    left = nullptr;
    right = nullptr;
    key = 0;
}

template <class T>
TreeNode<T>::TreeNode(T k)
{
    left = nullptr;
    right = nullptr;
    key = k;
}

template <class T>
TreeNode<T>::~TreeNode()
{
    //figure this one out
}

