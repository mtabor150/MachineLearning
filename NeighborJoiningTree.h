
/*
 * Phillip Martin, October 15 2014
 * NeighborJoiningTree.h - Neighbor Joining tree
 * 
 * NOTE: For now NJDistanceMatrix will only take in NGramVectors (technical debt). NeighborJoiningTree is based on this
 */
#ifndef NEIGHBORJOININGTREE_H
#define NEIGHBORJOININGTREE_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "NgramVector.h"
#include "NJDistanceMatrix.h"
#include "tree/BinaryTree.h"
#include "DataSet.h"


using namespace std;

template <typename ItemType, class VectorType=NgramVector>
class NeighborJoiningTree : public BinaryTree<ItemType> {
  
private:

  //distance matrix to hold the necessary data and modifying that data
  //as the matrix shrinks to fewer and fewer elements and the tree grows
  NJDistanceMatrix distance_matrix;

  //DataSet for the tree to hold all vectors
  DataSet<NgramVector> d_set;

  //next id
  int next_id;

public:

  void set_data(DataSet<VectorType> _set)
  {
    d_set = _set;
    distance_matrix.set_data(_set);
  }

  NeighborJoiningTree createNJTreeFromDataSet(string tree_name)
  {
    next_id = 1;

    //create a vector of NeighborJoiningTrees
    map<int, NeighborJoiningTree<ItemType>* > trees;

    //create tree for each MLVector
    int dataSize = d_set.size();
    for(int i=0; i< dataSize; i++)
    {

      //create tree for each MLVector consisting of one node
      NeighborJoiningTree<ItemType> *temp_tree = new NeighborJoiningTree<ItemType>;

      //add tree to vector of trees
      trees[next_id] = temp_tree;

      //create a string with the author id to place as the data value of the root for each tree
      string str = "NULL";
      int id = stoi(d_set[i].get_author(str));
      
      //create the root for the data specified
      trees[next_id]->createRoot(d_set[i].get_author(str));
      next_id++;
      cout << id << endl;
    }
    
    while(trees.size() > 1)
    {
      cout << "treesize = " << trees.size() << endl;
      
      double closest_distance = distance_matrix.get_closest_distance(); //get closest distance not closest q distance
      NJDistanceMatrix::pair closest_pair = distance_matrix.combine_closest_pair();
      
      cout << "a" << endl;
      int id1 = stoi(closest_pair.element1);
      int id2 = stoi(closest_pair.element2);
      cout << "b" << endl;
      //create new tree with id1 and id2 as subtrees
      NeighborJoiningTree<ItemType> *temp_tree = new NeighborJoiningTree<ItemType>;
      temp_tree->d_set += trees[id1]->d_set;
      temp_tree->d_set += trees[id2]->d_set; 
      temp_tree->createRoot(to_string(closest_distance));//small_dist));
      temp_tree->setSubTrees(*trees[id1], *trees[id2]);
      cout << "c" << endl;
      trees.erase(id1);
      trees.erase(id2);
      cout << "d" << endl;
      trees[next_id] = temp_tree;
      next_id++;
      cout << trees.size() << endl;
    }
    cout << "tree" << endl;
    trees.begin()->second->draw(tree_name);
    cout << "tree2" << endl;
    //return trees[0];
  }


}; // end NeighborJoiningTree.h

#endif