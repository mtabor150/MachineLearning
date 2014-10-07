#ifndef DATASET_H
#define DATASET_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "MLVector.h"
using namespace std;
         
template <typename ItemType>

class DataSet : public vector<MLVector<ItemType> > {

public:
  
  DataSet& operator+=(const DataSet& other){
    int size = other.size();
    for(int i = 0; i < size; i++){
      (*this).push_back(other[i]);
    }
  }
  
  void print(){
    int size = (*this).size();
    for(int i = 0; i < size; i++){
      (*this)[i].print(to_string(i));
    }
  }
  
  /*modifies a provided MLVector to be the mean vector of the dataset*/
  void mean(MLVector<ItemType>& mean){
    mean.clear();
    int numVectors = (*this).size();
    for(int i=0; i < numVectors; i++){
      mean += (*this)[i];
    }
    mean /= numVectors;
  }
  
  
  
  /*modifies a DataSet to be k dispersed vectors*/
  void kcentroids(int k, DataSet& centroids){
    centroids.clear();
    
    if(k<=0){
      return;
    }
    
    centroids.push_back((*this)[0]);
    int numVectors = (*this).size();
    int numCent = 1;
    while(numCent < k){
      int nextCent = numCent; 
      float bestDist = 0;
      for(int i = numCent; i < numVectors; i++){
	float currentMinMax = numeric_limits<float>::infinity();
	for(int j = 0; j < numCent; j++){
	  float minMax = 0;
	  minMax = (*this)[i].cosine_distance(centroids[j]);
	  if(minMax < currentMinMax){
	    currentMinMax = minMax;
	  }
	}
	//currentDist = (currentDist/numCent);
	if(currentMinMax > bestDist){
	  bestDist = currentMinMax;
	  nextCent = i;
	}
      }
      centroids.push_back((*this)[nextCent]);
      numCent++;
    }
  }
  
  /*kMeans clustering implementation*/
  void kmeans(int k, vector<DataSet>& clusters){    
    //get initial centroids
    DataSet centroids, previous_centroids;
    kcentroids(k, centroids);
    
    //initialize cluster vector
    clusters.clear();
    for(int i = 0; i < k; i++){
      DataSet<ItemType> temp;
      clusters.push_back(temp);
    }
    
    int itrtn = 1;
    bool done = false;
    while(!done){
      cout << endl;
      cout << "Iteration: " << itrtn << endl;
      
      //place vectors with centroids
      int numVectors = (*this).size();
      cout << "clutering " << numVectors << " vectors around " << k << " centroids" << endl;
      for(int i = 0; i < numVectors; i++){
	if(i%1000 == 0){
	  cout << "v"<< i << endl;
	}
	int centGroup = 0;
	float dist = (*this)[i].cosine_distance(centroids[0]);
	for(int j = 1; j < k; j++){
	  float currentDist = (*this)[i].cosine_distance(centroids[j]);
	  if(currentDist < dist){
	    dist = currentDist;
	    centGroup = j;
	  }
	}
	//cout << "Vector: " << i << " Cluster: "<<  centGroup << "    ";
	
	//add to centroid group
	clusters[centGroup].push_back((*this)[i]);
      }
      
      cout << endl;
      
      //recompute centroids
      previous_centroids = centroids;
      for(int i = 0; i < k; i++){
	cout << "Computing mean for cluster: " << i <<  " of size "<< clusters[i].size() << endl;
	MLVector<ItemType> new_centroid;
	clusters[i].mean(new_centroid);
	centroids[i] = new_centroid;
      }
      
      //check if same as previous iteration
      done = true;
      for(int i = 0; i < k; i++){
	cout << "Checking equivalence" << endl;
	float cdist = centroids[i].cosine_distance(previous_centroids[i]);
	if(cdist > .0000001 ){
	  cout << "Centroid " << i << " not equivalent to previous centroid." << endl;
	  cout << "cosine distance: " << cdist << endl;
	  done = false;
	}
      }
      
      if(!done){
	//reset clusters
	for(int i = 0; i < k; i++){
	  DataSet<ItemType> temp;
	  clusters[i]=temp;
	}
      }
      
      itrtn++;
    }
  }
  
};

#endif
 
