/*
 * Phillip Martin, October 15 2014
 * NJTree - Neighbor Joining tree
 * 
 * NOTE: Currently requires NGramVector as the MLVector type in the DataSet (needs to be able
 *       to use any MLVector type).
 */
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "tree/BinaryTree.h"
#include "DataSet.h"

using namespace std;

template <typename ItemType, class VectorType=NgramVector>
class NJTree : public BinaryTree<ItemType> {
  

public:
  DataSet<VectorType> d_set;

  void setSubTrees(NJTree<ItemType>& right, NJTree<ItemType>& left)
  {
    this->_root->_right = right._duplicate(right.root());
    this->_root->_left = left._duplicate(left.root());
  }


  void setDataSet(DataSet<VectorType> _set)
  {
    d_set = _set;
  }

  NJTree createNJTreeFromDataSet()
  {
    //create a vector of NJTrees
    vector<NJTree<ItemType>* > trees;

    //create tree for each MLVector
    int dataSize = d_set.size();
    for(int i=0; i< dataSize; i++)
    {
      NJTree<ItemType> *temp_tree = new NJTree<ItemType>;
      temp_tree->d_set.push_back(d_set[i]);
      //temp_tree.createRoot(to_string(i));
      trees.push_back(temp_tree);
      string str = "NULL";
      int id = stoi(d_set[i].get_author(str));
      
      trees[i]->createRoot(d_set[i].get_author(str), 1);
      
      cout << id << endl;
      //trees[i]->setAux(id, trees[i]->root());
    }
    
    while(trees.size() > 1)
    {
      cout << "treesize = " << trees.size() << endl;
      //find two closest vectors
      int id1 = -1;
      int id2 = -1;
      double small_dist = 90.0;
      int treeSize = trees.size();
      for(int i=0; i<treeSize; i++ )
      {
        VectorType mean1;
        VectorType mean2;
        trees[i]->d_set.mean(mean1);
        for(int j=i+1 ; j<treeSize; j++)
        {
          trees[j]->d_set.mean(mean2);
          double temp_dist = mean1.distance(mean2, COS_DIST);
          if(temp_dist < small_dist)
          {
            small_dist = temp_dist;
            id1 = i;
            id2 = j;
          }
          /*
          cout << " id1: " << i << endl;
          cout << " id2: " << j << endl;
          cout << temp_dist << endl;*/
        }
      }

      //create new tree with id1 and id2 as subtrees
      NJTree<ItemType> *temp_tree = new NJTree<ItemType>;
      temp_tree->d_set += trees[id1]->d_set;
      temp_tree->d_set += trees[id2]->d_set; 
      temp_tree->createRoot(to_string(small_dist));
      temp_tree->setSubTrees(*trees[id1], *trees[id2]);
      trees.erase(trees.begin()+id1);
      trees.erase(trees.begin()+id2-1);
      trees.push_back(temp_tree);
    }
    trees[0]->draw("combined");
    //return trees[0];
  }


}; // end BinarySearchTree.h