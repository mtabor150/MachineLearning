//Mark Tabor
//Nov 17, 2012

#include "BinarySearchTree.h"
#include <cmath>
#include <iostream>
using namespace std;

template <typename ItemType>
class AVLTree : public BinarySearchTree<ItemType> {
  
protected:
  
  /** function to set the height correctly **/
  void _setHeight(typename BinaryTree<ItemType>::Iterator position) {
    //get left child's height
    int leftheight = -1;
    if (position.hasLeftChild())
      leftheight = BinaryTree<ItemType>::getAux(position.left());
    //get left child's height
    int rightheight = -1;
    if (position.hasRightChild())
      rightheight = BinaryTree<ItemType>::getAux(position.right()); 
    //update position's height
    BinaryTree<ItemType>::setAux(max(leftheight,rightheight)+1, position);
  }//end of _setHeight
  
  bool _isBalanced(typename BinaryTree<ItemType>::Iterator position) {
    //get left child's height
    int leftheight = -1;
    if (position.hasLeftChild())
      leftheight = BinaryTree<ItemType>::getAux(position.left());
    //get left child's height
    int rightheight = -1;
    if (position.hasRightChild())
      rightheight = BinaryTree<ItemType>::getAux(position.right()); 
    
    if (abs(leftheight-rightheight) <= 1)
      return true;
    else
      return false;
    
  }
  
  typename BinaryTree<ItemType>::Iterator _getHigherChild(typename BinaryTree<ItemType>::Iterator position) {
    //get left child's height
    int leftheight = -1;
    if (position.hasLeftChild())
      leftheight = BinaryTree<ItemType>::getAux(position.left());
    //get left child's height
    int rightheight = -1;
    if (position.hasRightChild())
      rightheight = BinaryTree<ItemType>::getAux(position.right()); 
    
    if (leftheight > rightheight)
      return position.left();
    else
      return position.right();
  }
  
public:
  
  void insert(const ItemType& value) {

    //insert using binary search tree's version
    typename BinaryTree<ItemType>::Iterator it =  BinarySearchTree<ItemType>::insert(value);
    BinaryTree<ItemType>::setAux(0, it);  //leaves have height 0
    
    cout << "binary tree insert worked on " << *it << endl;
    it = it.up();
    
    //travel up the tree resetting heights
    while (!it.isNULL()) {
      //cout << "in loop in insert" << endl;
      //reset heights
      _setHeight(it);
      
      //check if unbalanced, and fix if so
      if (!_isBalanced(it)) {
	typename BinaryTree<ItemType>::Iterator z = it;
	typename BinaryTree<ItemType>::Iterator y = _getHigherChild(z);
	typename BinaryTree<ItemType>::Iterator x = _getHigherChild(y);
	
	if ((z.left() == y && y.left() == x) || (z.right() == y && y.right() == x)) {
	  BinaryTree<ItemType>::pivot(y);
	  _setHeight(z);
	  _setHeight(y);
	  it = y.up();
	}
	else  {
	  BinaryTree<ItemType>::pivot(x);
	  BinaryTree<ItemType>::pivot(x);
	  _setHeight(z);
	  _setHeight(y);
	  _setHeight(x);
	  it = x.up();
	}
      } //end of if not balanced
      else
	 it = it.up();
      
    } //end of while
    
  } //end insert

  void remove(const ItemType& value) {
    //check if tree is empty
    if(BinaryTree<ItemType>::empty()) return;
    
    //search for value, if not present do nothing
    if(!BinarySearchTree<ItemType>::find(value)) return;
    
    //else remove value
    else{
       
    typename BinaryTree<ItemType>::Iterator position = BinaryTree<ItemType>::root();
    while(*position != value){
      if (*position > value)
	position = position.left();
      else
	position = position.right();
    }
    
    typename BinaryTree<ItemType>::Iterator next = position;
    
    //if leaf delete or has no right child
    if(position.isLeaf()||!position.hasRightChild()) {
      this->deleteAndMoveLeftChildUp(position);
    }
    //if no left child
    else{
      if(!position.hasLeftChild()) {
	this->deleteAndMoveRightChildUp(position);
      }
    
    
      else{
	//find next item in an in order traversal, replace, and delete
	next++;
	*position = *next;
	this->deleteAndMoveRightChildUp(next);
      }
    }
    while (!next.isNULL()) {
      //reset heights
      _setHeight(next);
      
      //check if unbalanced, and fix if so
      if (!_isBalanced(next)) {
	typename BinaryTree<ItemType>::Iterator z = next;
	typename BinaryTree<ItemType>::Iterator y = _getHigherChild(z);
	typename BinaryTree<ItemType>::Iterator x = _getHigherChild(y);
	
	if ((z.left() == y && y.left() == x) || (z.right() == y && y.right() == x)) {
	  BinaryTree<ItemType>::pivot(y);
	  _setHeight(z);
	  _setHeight(y);
	  next = y.up();
	}
	else  {
	  BinaryTree<ItemType>::pivot(x);
	  BinaryTree<ItemType>::pivot(x);
	  _setHeight(z);
	  _setHeight(y);
	  _setHeight(x);
	  next = x.up();
	}
      } //end of if not balanced
      else
	 next = next.up();
      
    } //end of while
    
    return;
   }
   
   //check if tree is balanced
      


  } //end remove
  
}; //end AVLTree class
