//Mark Tabor, Imaoye Ekpelu
//Nov 17, 2012
#include "AVLTree.h"
#include <iostream>
using namespace std;

int main() {

  AVLTree<int> mytree;
  
  //try to remove on a tree
  mytree.remove(10);
  
  
  mytree.insert(10);
  mytree.insert(5);
  mytree.insert(15);

  mytree.draw("AVLtree",0,true);
 
  //triggers no rotation
  mytree.insert(21);
  mytree.draw("AVLtree",0,true);
  
  //triggers rotation in right side
  mytree.insert(35);
  mytree.draw("AVLtree",0,true);
  
  //triggers rotation at root
  mytree.insert(42);  
  mytree.draw("AVLtree", 0, true);
  
  mytree.insert(16);
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
  mytree.draw("AVLtree", 0, true);

  //test remove
  
  //try to remove item not in tree
  mytree.remove(1000);
  
  mytree.remove(35);
  mytree.draw("AVLtree", 0, true);

  mytree.remove(42);
  mytree.draw("AVLtree", 0, true);
  
  mytree.remove(28);
  mytree.draw("AVLtree", 0, true);
  
  mytree.remove(73);
  mytree.draw("AVLtree", 0, true);
  
  mytree.remove(67);
  mytree.draw("AVLtree", 0, true);
  
  mytree.remove(21);
  mytree.draw("AVLtree", 0, true);
  
}
