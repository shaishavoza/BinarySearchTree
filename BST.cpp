#include <iostream>
//#include <iomanip>

using namespace std;

#include "BST.h"

//--- Definition of constructor
BST::BST()
: myRoot(0)
{}

bool BST::empty() const
{ return myRoot == 0; }


bool BST::search(const int & item) const
{
   BinNode * locptr = myRoot;
   bool found = false;
   while (!found && locptr != 0)
   {
      if (item < locptr->data)       // descend left
        locptr = locptr->left;
      else if (locptr->data < item)  // descend right
        locptr = locptr->right;
      else                           // item found
        found = true;
   }
   return found;
}


void BST::insert(const int & item)
{
   BinNode * locptr = myRoot;   // search pointer
   BinNode * parent = 0;        // pointer to parent of current node
   bool found = false;     // indicates if item already in BST
   while (!found && locptr != 0)
   {
      parent = locptr;
      if (item < locptr->data)       // descend left
         locptr = locptr->left;
      else if (locptr->data < item)  // descend right
         locptr = locptr->right;
      else                           // item found
         found = true;
   }
   if (!found)
   {                                 // construct node containing item
      locptr = new BinNode(item);  
      if (parent == 0)               // empty tree
         myRoot = locptr;
      else if (item < parent->data )  // insert to left of parent
         parent->left = locptr;
      else                           // insert to right of parent
         parent->right = locptr;
   }
   else
      cout << "Item already in the tree\n";
}

void BST::deleteNode(const int & item){
   BinNode * locptr = myRoot;
    BinNode * parent = 0;      // pointer to parent of current node
    bool found = false;     
    while (!found && locptr != 0)
    {
       if (item < locptr->data)       // descend left
       {
	  parent = locptr;
          locptr = locptr->left;
       }
       else if (locptr->data < item)  // descend right
       {
	  parent = locptr;
          locptr = locptr->right;
       }
       else                           // item found
          found = true;
    }
    if(!found){
       cout << "No such item in the tree\n";
       return;
    }


if(locptr->left==0 && locptr->right==0) //node with no children
    {
        if(locptr!=myRoot)
        {
            if(parent->left==locptr)
                parent->left=0;
            else
                parent->right=0; 
        }
        else
            myRoot=0;

	free(locptr);
    }
    else if(locptr->left && locptr->right) //The node has two children
    {
        parent=locptr;
        child=locptr->left;
        while (child->right!=0)
	{
            parent=child;
            child=child->right;
        }
        if(parent==locptr)
        {
            locptr->data=child->data;
            locptr->left=child->left;
        }
        else
        {
            locptr->data=child->data;
            parent->right=child->left;
        }
    }    
    else //The node has only one child
    {
        BinNode * subchild = (locptr->left)? locptr->left: locptr->right;
	/*if(subchild==locptr->left)
	    subchild=locptr->left;
        else
	    subchild=locptr->right;*/
        if(locptr!=myRoot)
        {
            if(locptr==parent->left)            
                parent->left=subchild;
            else    
                parent->right=subchild;
        }
        else
            myRoot=subchild;

        free(locptr);
    }

}

void BST::accessPreOrder()
{
    preOrder(myRoot);
}

void BST::preOrder(BinNode * root)
{
    if(root==0){
       return;
    }
    cout <<root->data <<" ";
    preOrder(root->left);
    preOrder(root->right);
    
}

void BST::accessInOrder()
{
    inOrder(myRoot);
}

void BST::inOrder(BinNode * root)
{
    if(root==0)
    {
       return;
    }
    inOrder(root->left);
    cout <<root->data <<" ";
    inOrder(root->right);
    
}

int BST::accessNodeCount()
{
    int num=nodeCount(myRoot);
    return num-1;
}

int BST::nodeCount(BinNode * root)
{
    int count=1;
    if(root==0)
        return count;
    else
    {
        count=nodeCount(root->left);
        count=count+nodeCount(root->right);
    }
    return count;
}