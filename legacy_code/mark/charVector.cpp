#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "charVector.h"

using namespace std;


/* character vector constructor
 * works with utf-8 but not other unicode values
 * look into switching to ICU library
 */
void makeVector(unordered_map<string, float>* charVector, string text = ""){
  int keyLength = 3;
  
  char* str = (char*)text.c_str();    	// utf-8 string
  char* begin = str;			//begining of string
  char* end = str+strlen(str);      	// end iterator
  char* it = end;       		// string iterator
  
  int size = end-begin;
  if(size <= keyLength){
    (*charVector)[text] = 1;
  }
  
  else{
    for(int i = 0; i < keyLength; i++){
      it--;
      if(it[0] < 0 && it[1] >= 0)it--;
    }
    
    while(it >= begin){
      (*charVector)[it] += 1;
      
      if(end[0] <= 0){
	end[0] = '\0';
	end--;
      }
      end[0] = '\0';
      end--;
      
      it--;
      if(it[0] < 0)it--;
     }
  }
}


/*prints vector*/
void printVector(unordered_map<string, float> *vector){
  int i = 0;
  for(unordered_map<string,float>::iterator it= (*vector).begin(); it!= (*vector).end(); ++it){
    cout << "[" << it->first << ": ";
    printf("%.2f] ", it->second);
    i++;
    if(i%11 == 0) cout << '\n';
  }
  cout << "\n";
}


/*adds the elements of two vectors and returns a vector of their sum*/
void addVectors(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB, unordered_map<string, float>* destV){
  (*destV) = (*vectorA);
  
  for(unordered_map<string,float>::iterator it=(*vectorB).begin(); it!=(*vectorB).end(); ++it){
      (*destV)[it->first] += it->second;
  }
}


/*returns angle between two charVectors*/
float vAngle(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB){
  float normA = 0;
  float normB = 0;
  float adotb = 0;
  
  for(unordered_map<string,float>::iterator it=(*vectorA).begin(); it!=(*vectorA).end(); ++it){
    float value = it->second;
    normA += (value*value);
    if((*vectorB).find(it->first) != (*vectorB).end()){
      adotb += (value*(*vectorB)[it->first]);
    }
  }
  
  for(unordered_map<string,float>::iterator it=(*vectorB).begin(); it!=(*vectorB).end(); ++it){
    float value = it->second;
    normB += (value*value);
  }
  
  normA = sqrt(normA);
  normB = sqrt(normB);
  
  float product = adotb/(normA*normB);
  float angle;
  if(product >= 1.0){
    angle = acos(1);
  }
  else if(product <= -1.0){
    angle = acos(-1);
  }
  else{
    angle = acos(product);
  }
  angle = (angle*180)/(atan(1)*4);
  return angle;
}


/*returns euclidean distance between charVectors*/
float vDistance(unordered_map<string, float>* vectorA, unordered_map<string, float>* vectorB){
  float dist = 0;
  
  for(unordered_map<string,float>::iterator it=(*vectorA).begin(); it!=(*vectorA).end(); ++it){
    float valueA = it->second;
    if((*vectorB).find(it->first) != (*vectorB).end()){
      float valueB = (*vectorB)[it->first];
      dist += ((valueA-valueB)*(valueA-valueB));
    }
    else{
      dist += (valueA*valueA);
    }
  }
  
  for(unordered_map<string,float>::iterator it=(*vectorB).begin(); it!=(*vectorB).end(); ++it){
    float value = it->second;
    if((*vectorA).find(it->first) == (*vectorA).end()){
      dist += (value*value);
    }
  }

  dist = sqrt(dist);
  return dist;
}


/*takes an array of charVectors and returns a vector representing their means*/
void meanVector(vector< unordered_map<string, float> >* vectors, unordered_map<string, float>* vMean){
  int numVectors = (*vectors).size();
  unordered_map<string, float>* tmp, *mptr;
  unordered_map<string, float> tmpMean;
  for(int i=0; i < numVectors; i++){
    tmpMean = (*vMean);
    mptr = &tmpMean;
    tmp = &(*vectors)[i];
    addVectors(tmp, mptr, vMean);
  }
  
  for(unordered_map<string,float>::iterator it=(*vMean).begin(); it!=(*vMean).end(); ++it){
    (*vMean)[it->first] = ((it->second)/numVectors);
  }
}

/*takes an array of charVectors and returns the k dispersed charVectors*/
void initCentroids(int k, vector< unordered_map<string, float> >* vectors, vector< unordered_map<string, float> >* centroids){
  
  if(k<=0){
    return;
  }
  
  (*centroids).push_back((*vectors)[0]);
  int numVectors = (*vectors).size();
  int numCent = 1;
  while(numCent < k){
    unordered_map<string, float> nextCent = (*vectors)[numCent]; 
    float bestDist = 0;
    for(int i = numCent; i < numVectors; i++){
      float currentMinMax = 100;
      for(int j = 0; j < numCent; j++){
	float minMax = 0;
	unordered_map<string, float>* vptr = &(*vectors)[i];
	unordered_map<string, float>* cptr = &(*centroids)[j];
	minMax = vAngle(vptr, cptr);
	if(minMax < currentMinMax){
	  currentMinMax = minMax;
	}
      }
      //currentDist = (currentDist/numCent);
      if(currentMinMax > bestDist){
	bestDist = currentMinMax;
	nextCent = (*vectors)[i];
      }
    }
    (*centroids).push_back(nextCent);
    numCent++;
  }
}


/*function to check the equivalence of vectors*/
bool equivalence(unordered_map<string, float> *vA, unordered_map<string, float> *vB){
  int sizeA = (*vA).size(); 
  int sizeB = (*vB).size();
  float epsilon = 0.000001;
  if(sizeA != sizeB){
    cout << "vectors different sizes" << endl;
    return false;
  }
  else{
    for(unordered_map<string, float>::iterator it=(*vA).begin(); it!=(*vA).end(); ++it){
      unordered_map<string, float>::iterator it2 = (*vB).find(it->first);
      if(it2 == (*vB).end()){
	cout << "key doesn't exist in vector" << endl;
	return false;
      }
      else if (abs(it->second - it2->second) > epsilon){
	cout << "different values for keys. Key: " << it->first<< " Value 1: "<< it->second << " Value 2:" << it2->second <<endl;
	return false;
      }
    }
  }
  
  return true;
}


/*kMeans clustering implementation*/
void kMeans(int k, vector< unordered_map<string, float> >* vectors, vector<cluster>* clusters){
  
  vector< unordered_map<string, float> > previousCentroids, *cptr;
  cptr = &previousCentroids;
  
  //get initial centroids
  initCentroids(k, vectors, cptr);
  for(int i = 0; i < k; i++){
    struct cluster tempC;
    tempC.centroid = previousCentroids[i];
    (*clusters).push_back(tempC);
  }
  int itrtn = 1;
  bool done = false;
  while(!done){
    cout << "Iteration: " << itrtn << endl;
    //place vectors with centroids
    int numVectors = (*vectors).size();
    for(int i = 0; i < numVectors; i++){
      unordered_map<string, float> *v, *c;
      v = &(*vectors)[i];
      c = &(*clusters)[0].centroid;
      int centGroup = 0;
      float dist = vAngle(v, c);
      for(int j = 1; j < k; j++){
	c = &(*clusters)[j].centroid;
	float currentDist = vAngle(v, c);
	if(currentDist < dist){
	  dist = currentDist;
	  centGroup = j;
	}
      }
      //cout << "Vector: " << i << " Cluster: "<<  centGroup << "    ";
      //add to centroid group
      (*clusters)[centGroup].neighbors.push_back((*vectors)[i]);
    }
    
    cout << endl;
    //recompute centroids
    for(int i = 0; i < k; i++){
      cout << "Computing mean for cluster: " << i <<  " of size "<< (*clusters)[i].neighbors.size() << endl;
      unordered_map<string, float>* c = &(*clusters)[i].centroid;
      vector< unordered_map<string, float> >* v = &(*clusters)[i].neighbors;
      meanVector(v, c);
    }
    
    //check if same as previous iteration
    done = true;
    for(int i = 0; i < k; i++){
      cout << "Checking equivalence" << endl;
      unordered_map<string, float> *vPrev, *vCur;
      vPrev = &previousCentroids[i];
      vCur = &(*clusters)[i].centroid;
      
      
      if(!equivalence(vPrev, vCur)){
	cout << "Centroid " << i << " not equivalent to previous centroid." << endl;
// 	cout << "============previous============" << endl;
// 	printVector(vPrev);
// 	cout << "============current=============" << endl;
// 	printVector(vCur);
	done = false;
      }
    }
    
    if(!done){
      //keep previous centroids and clear clusters
      for(int i = 0; i < k; i++){
	previousCentroids[i] = (*clusters)[i].centroid;
	(*clusters)[i].neighbors.clear();
      }
    }
    itrtn++;
  }
}