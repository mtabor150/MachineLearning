//Mark Tabor
//Nov 5 2012

#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

int main() {

  BinarySearchTree<int> mytree;
  //try to remove on an empty tree
  mytree.draw("tree",0,true);
  mytree.remove(12);
  
  //remove root
  mytree.createRoot(12);
  mytree.draw("tree",0,true);
  mytree.remove(12);
  cout<<"removing 12"<<endl;
  mytree.draw("tree",0,true);
  
  //remove a leaf
  mytree.createRoot(50);
  mytree.insert(25);
  mytree.insert(75);
  mytree.insert(1);
  mytree.draw("tree",0,true);
  mytree.remove(1);
  cout<<"removing 1"<<endl;
  mytree.draw("tree",0,true);
  
  //remove node with no left child
  mytree.insert(15);
  mytree.insert(70);
  mytree.insert(67);
  mytree.insert(73);
  mytree.insert(17);
  mytree.insert(13);
  mytree.insert(14);
  mytree.insert(28);
  mytree.insert(18);
  mytree.insert(55);
  mytree.insert(74);
  mytree.insert(66);
  mytree.insert(68);
  mytree.draw("tree",0,true);
  cout<<"removing 13"<<endl;
  mytree.remove(13);
  mytree.draw("tree",0,true);
  
  //remove node with no right child
  mytree.remove(75);
  cout<<"removing 75"<<endl;
  mytree.draw("tree",0,true);
  
  
  //remove node with 2 children
  mytree.remove(50);
  cout<<"removing 50"<<endl;
  mytree.draw("tree",0,true);
  mytree.remove(55);
  cout<<"removing 55"<<endl;
  mytree.draw("tree",0,true);
  mytree.remove(15);
  cout<<"removing 15"<<endl;
  mytree.draw("tree",0,true);
  mytree.remove(67);
  cout<<"removing 67"<<endl;
  mytree.draw("tree",0,true);
  mytree.remove(25);
  cout<<"removing 25"<<endl;
  mytree.draw("tree",0,true);
}
