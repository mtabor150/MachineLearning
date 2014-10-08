#include <string>
#include <iostream>
#include <stdexcept>
using namespace std;

/**
 * Binary Tree class
 */

template <typename ItemType>
class BinaryTree {
  
private: 
  struct Node {
      ItemType _data;
    
      Node* _parent;    //pointer to parent node
      Node* _left;	//pointer to left child
      Node* _right;	//pointer to right child
      
      int _aux;		//auxilary info (for future use)
      
      //constructor
      Node(const ItemType& data, Node* parent = NULL, Node* left = NULL, Node* right = NULL, int aux = 0) : _data(data), _parent(parent), _left(left), _right(right), _aux(aux) {}
      
    }; //end struct
    
public:
    
    /**
    * Iterator class for moving within the tree
    **/
    class Iterator {
      
      private:
	Node* _current; 	//pointer to current node
	BinaryTree* _tree;	//pointer to tree I belong to
	
      public:
	
	//constructor for iterator - useful inside class
	Iterator(Node* c = NULL, BinaryTree* t = NULL) : _current(c) , _tree(t) {}
	
	//copy constructor
	Iterator(const Iterator& other) {
	  _current = other._current;
	  _tree = other._tree;
	}
	
	//returns reference to data
	ItemType& operator*() const {
	  return _current->_data;
	}
	
	//returns const pointer to data
	ItemType* operator->() const {
	  return &(_current->_data);
	}
	
	//Returns an interator to the left child of the iterator
	Iterator left() {
	  return Iterator(_current->_left, _tree);
	}
	
	//Returns an interator to the right child of the iterator
	Iterator right() {
	  return Iterator(_current->_right, _tree);
	}
	
	//Returns an iterator to the parent
	Iterator up() {
	  return Iterator(_current->_parent, _tree);
	}
	
	//Returns true if the iterator points to the root
	bool isRoot() {
	  return (_current == _tree->_root);
	}
	
	//Returns true if the iterators point to the same thing
	bool operator==(const Iterator& other) {
	  return (_current == other._current && _tree == other._tree);
	}
	  
	//Returns true if the 2 iterators are NOT equal
	bool operator!=(const Iterator& other) {
	  return (_current != other._current || _tree != other._tree);
	}
	  
	//Returns true if the iterator has a left child
	bool hasLeftChild() {
	  return (_current->_left != NULL);
	}
	
	//Returns true if the iterator has a right child
	 bool hasRightChild() {
	   return (_current->_right != NULL);
	} 
	
	//Returns true if the iterator points to a leaf node
	bool isLeaf() {
	  return (!hasRightChild() && !hasLeftChild());
	}
	
	//Returns true if the iterator is NULL
	bool isNULL() {
	  return (_current == NULL);
	}
	
	//Find the next node in an inorder traversal - prefix
	Iterator operator++() {
	  //if there is a right child, go to it, and then left as much as possible
	  if (hasRightChild()) {
	    *this = right();
	    while (hasLeftChild()) 
	      *this = left();
	  }
	  else { //no right child, so go up as long as we're the right child, then up one more time
	    while (!isRoot() && (up().right() == *this))
	      *this = up();
	    *this = up();
	  }
	  return *this;  	  

	}
	
	//Find the next node in an inorder traversal - postfix
	Iterator operator++(int dummy) {
	  Iterator temp = *this;
	  //if there is a right child, go to it, and then left as much as possible
	  if (hasRightChild()) {
	    *this = right();
	    while (hasLeftChild()) 
	      *this = left();
	  }
	  else { //no right child, so go up as long as we're the right child, then up one more time
	    while (!isRoot() && (up().right() == *this))
	      *this = up();
	    *this = up();
	  }
	  return temp;  	 

	}
	  
	friend class BinaryTree;
	  
    }; //end of iterator class
    
private:

    int _size;  	//size of binary tree
    Node* _root;	//pointer to root node in binary tree

    
protected:
  
  /** function to recursively delete a subtree 
  * Input parameter: node pointer indicated which subtree to remove
  **/
  void _recursivelyDelete(Iterator iter) {
    //recursive case
    if (!iter.isNULL()) {
      //go left
      _recursivelyDelete(iter.left());
      //go right
      _recursivelyDelete(iter.right());
      //deal with myself
      delete iter._current;
      _size--;
    }
    //non-existant else means base case is to do nothing
  
  }

  
  /**function to recursively! duplicate a subtree
  * Input parameter: node pointing to subtree that should be copied
  * Return a pointer to the root of the duplicate tree
  **/
  Node* _duplicate(Iterator iter) {
    
    if (!iter.isNULL()) {
      //pre-order, so create current vertex
      Node* newtree = new Node(iter._current->_data);
      
      //recursively create left subtree
      if (iter.hasLeftChild()) {
	newtree -> _left = _duplicate(iter.left());
	newtree->_left->_parent = newtree;
      }
      if (iter.hasRightChild()) {
	//recursively create right subtree
	newtree -> _right = _duplicate(iter.right());
	newtree->_right->_parent = newtree;
      }
      return newtree;
    }
    else
      return 0;

  }
    
public:
  
  /**
   * Constructor
   */
  BinaryTree() :  _size(0), _root(NULL) {}
  
  /** 
   * Copy Constructor
   */
  BinaryTree(const BinaryTree& other) {
    _root = _duplicate(other.root());
    _size = other._size;
  }
  
  /** 
   * Destructor 
   */
  ~BinaryTree() {
    _recursivelyDelete(Iterator(_root));
  }
  
  /**
  *  Returns size of the tree
  */
  int size() const {
    return _size;
  }

  /**
  *  Returns true if the tree is empty
  */
  bool empty() const {
    return (_size == 0);
  }
  
  int getAux(Iterator iter) const {
    return iter._current->_aux;
    //return (*iter)->_aux;
  }
  
  void setAux(int value, Iterator iter) {
    iter._current->_aux = value;
  }
  
  void createRoot(const ItemType& value) {
    if (_size != 0)
      throw runtime_error("root already exists");
    _root = new Node(value);
    _size = 1;
  }
  
  
  /** function to insert new data as the right child of a specified node
   * If the right child already exists, delete it (and its subtree)
   */
  void insertAsRightChild(const ItemType& value, Iterator iter) {
    if (iter.hasRightChild()) {
      _recursivelyDelete(iter.right());
      //or could throw an error
    }
    Node* newnode = new Node(value, iter._current);
    iter._current->_right = newnode;
    _size++;
    
  }
  
  void insertAsLeftChild(const ItemType& value, Iterator iter) {
    if (iter.hasLeftChild()) {
      _recursivelyDelete(iter.left());
      //or could throw an error
    }
    Node* newnode = new Node(value, iter._current);
    iter._current->_left = newnode;
    _size++; 
  }
  
  Iterator root() {
    return Iterator(_root, this);
  }
  
  Iterator begin() {
    Iterator it = root();
    while (it.hasLeftChild())
      it = it.left();
    return it;
  }
  
  //return a NULL iterator 
  Iterator end() {
    Iterator it;
    return it;
  }
  
  /** Delete an indicated node, and promoting its left child
   * Any nodes in right subtree are deleted
   */
  void deleteAndMoveLeftChildUp(Iterator location) {
    Node* position = location._current;
    
    //update my left subtree's parent
    if (position->_left != NULL)
      position->_left->_parent = position->_parent;

    //update the parent node
    if (position != _root) {
      if (position->_parent->_left == position) {
	//position is the left child
	position->_parent->_left = position->_left;
      }
      else
	position->_parent->_right = position->_left;
    }
    else
      _root = position->_left;
    
    //delete node and right subtree
    _recursivelyDelete(location.right());
    delete position;
    _size--;
  }

    /**
     *  Delete a node from the tree advancing its right child.
     *
     *  The right child of the node will take the place of the specified
     *  node.  The node and its left subtree will be deleted.
     *
     *  Input parameter location: an iterator referencing the node to be deleted.
     */
    void deleteAndMoveRightChildUp(Iterator location) {
    Node* position = location._current;
    
    //update my right subtree's parent
    if (position->_right != NULL)
      position->_right->_parent = position->_parent;

    //update the parent node (if not the root)
    if (position != _root) {
      if (position->_parent->_left == position) {
	//position is the left child
	position->_parent->_left = position->_right;
      }
      else
	position->_parent->_right = position->_right;
    }
    else
      _root = position->_right;
    
    //delete node and right subtree
    _recursivelyDelete(location.left());
    delete position;
    _size--;

    }
    
    /** pivot function
     * input: iterator
     * swap position of input iterator and its parent
     */
    void pivot(Iterator location) {
      if (location.isRoot())
	throw runtime_error("Can't pivot a root");
      if (location.isNULL())
	throw runtime_error("Can't pivot a null position");
      
      //make temporary pointers
      Node* a = location._current;
      Node* b = a->_parent;
      
      if (b == _root) {
	a->_parent = NULL;
	_root = a;
      }
      else {     
	Node* gp = b->_parent;
	if (b == gp->_right) 
	  gp ->_right = a;
	else
	  gp ->_left = a;
	a->_parent = gp;
      }

      
      //determine if child is right or left
      if (a == b->_left) {
	//left child, so we can isolate t1,t2, and t3
	Node* t2 = a->_right;
	
	a->_right = b;
	b->_parent = a;
	
	//fix t2
	b->_left = t2;
	if (t2 != NULL)
	  t2->_parent = b;
      }
      else {
	
	Node* t2 = a->_left;
	
	a->_left = b;
	b->_parent = a;
	
	b->_right = t2;
	if (t2 != NULL)
	  t2->_parent = b;
      }
      

	  
    } //end _pivot
      
     
  
  
  
  
      /**
      *  Draw function declaration
      * (You can ignore this one!)
      */
    void draw(string name, Iterator* iter=0, bool pause=false);
};


// The code after here is for drawing a representation of the tree using GraphViz.  It
// is not needed for use of the class.
#include <fstream>
#include <list>
#include <set>
#include <iostream>

template<typename ItemType> void BinaryTree<ItemType>::draw(string name, Iterator* iter, bool pause) {
  ofstream out((name + ".dot").c_str());
  out << "digraph {" << endl;

  out << "root [label=\"_root\"];" << endl;
  if (_size > 0) {
    // Follow all possible links and expand each node once
    // This will work even if some of the links are messed up.
    set<Node *> expanded;
    list<Node *> toExpand;
    toExpand.push_back(_root);
    while (!toExpand.empty()) {
      Node *current = toExpand.front();
      toExpand.pop_front();
      if (expanded.find(current) == expanded.end()) {
        expanded.insert(current);
        if (current->_parent != 0)
          toExpand.push_back(current->_parent);
        if (current->_left != 0)
          toExpand.push_back(current->_left);
        if (current->_right != 0)
          toExpand.push_back(current->_right);
      }
    }

    // Draw labels
    out << "root -> node" << _root << ";" << endl;
    typename set<Node *>::iterator nodes;
    for (nodes=expanded.begin(); nodes!=expanded.end(); ++nodes) {
      out << "node" << *nodes << " ";
      out << "[shape=record,label=\"{";
      out << "<parent> _parent | ";
      out << "_data = " << (*nodes)->_data << " | ";
      out << "_aux = " << (*nodes)->_aux << " | ";
      out << "{ <left> _left | <right> _right } }\"];" << endl;
    }

    // Draw links
    for (nodes=expanded.begin(); nodes!=expanded.end(); ++nodes) {
      if ((*nodes)->_parent)
        out << "node" << *nodes << ":parent:n -> node" << (*nodes)->_parent << ";" << endl;
      if ((*nodes)->_left)
        out << "node" << *nodes << ":left:s -> node" << (*nodes)->_left << ";" << endl;
      if ((*nodes)->_right)
        out << "node" << *nodes << ":right:s -> node" << (*nodes)->_right << ";" << endl;
    }

    if (iter != 0)
      out << "iter -> node" << (*iter)._current << ";" << endl;
  }
  else {
    out << "zero [shape=none, label=\"0\"];"  << endl;
    out << "root -> zero;" << endl;
  }

  out << "}" << endl;

  string command = "dot " + name + ".dot -T ps -o " + name + ".ps";
  popen(command.c_str(), "r");

  if (pause) {
    char c;
    cout << "Hit any key to continue" << endl;
    cin >> c;
  }
}
    
