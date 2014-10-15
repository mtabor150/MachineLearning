//Mark Tabor
//Nov 5 2012

#include "BinaryTree.h"
using namespace std;

template <typename ItemType>
class BinarySearchTree : public BinaryTree<ItemType> {
  
public:
  
  /**
   * Function to insert an element into the BST
   * Input Parameter: the element to insert
   */
  typename BinaryTree<ItemType>::Iterator insert(const ItemType& element) {
    
    //if the tree is empty, make new element the root
    if (BinaryTree<ItemType>::empty()) {
      BinaryTree<ItemType>::createRoot(element);
      return BinaryTree<ItemType>::root();
    }
    else {
      //otherwise, start at the root
      typename BinaryTree<ItemType>::Iterator position = BinaryTree<ItemType>::root();
      bool done = false;
      while (!done) { 
        if (*position < element) {
          //insert to right
          if (position.hasRightChild())
            position = position.right();
          else
            done = true;
        }
        else {
          //insert to left
          if (position.hasLeftChild())
            position = position.left();
          else
            done = true;
        }
      } //end while
      
      //Now, position is place to insert below
      if (element <= *position) {
        BinaryTree<ItemType>::insertAsLeftChild(element,position);
        position = position.left();
      }
      else {
        BinaryTree<ItemType>::insertAsRightChild(element,position);
        position=position.right();
      }
      return position;
      
    }//end of main else
  } //end of insert
  
  /** 
   * Function to find if an element is in the tree
   * Input Parameter: the element to search for
   * Return value: an iterator to the node if it is present, or a null iterator if not
   */
  bool find(const ItemType& value) {
    typename BinaryTree<ItemType>::Iterator position = BinaryTree<ItemType>::root();
    
    while (!position.isNULL()) {
    
      if (*position == value)
        return true;
      else
        if (*position > value)
          position = position.left();
        else
          position = position.right();
    }
    return false; 
  }

  /** 
   * Function to remove an element from the tree
   */
  void remove(const ItemType& element) {
    //if empty do nothing
    typename BinaryTree<ItemType>::Iterator root = BinaryTree<ItemType>::root(); 
    if(root.isNULL()) return;
    
    //if element not present do nothing
    if(!find(element)) return;
    
    //else find element
    else {
      typename BinaryTree<ItemType>::Iterator position = BinaryTree<ItemType>::root();
      while(*position != element){
        if (*position > element)
          position = position.left();
        else
          position = position.right();
      }
      
      //if leaf delete or has no right child
      if(position.isLeaf()||!position.hasRightChild()) {
        this->deleteAndMoveLeftChildUp(position);
        return;
      }
      //if no left child
      if(!position.hasLeftChild()) {
        this->deleteAndMoveRightChildUp(position);
        return;
      }
      
      //else find next item in an in order traversal
      typename BinaryTree<ItemType>::Iterator next = position;
      next++;
      *position = *next;
      this->deleteAndMoveRightChildUp(next);
      return;
    }
  }
}; // end BinarySearchTree.h



