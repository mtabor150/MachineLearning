#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "NgramVector.h"
#include "DataSet.h" 
using namespace std;


int main(){
  ifstream fin("small-test.txt");
  //ifstream gin("bar-tweets.txt");
  
  DataSet<NgramVector> v;
  
  int i = 1;
  while(!fin.eof()){
    NgramVector temp(to_string(i++),"2","multi",3);
    string line;
    getline(fin, line);
    temp.input_string(line.substr(line.rfind('\t')+1,line.size()));
    v.push_back(temp);
  }
  //v.print();
  
  
  vector<DataSet<NgramVector> > clusters;
  for(int k = 1; k < 10; k++){
    v.kmeans(k, clusters);
    
    vector<NgramVector> centroids;

    for(int i = 0; i < k; i++){
      NgramVector temp;
      clusters[i].mean(temp);
      centroids.push_back(temp);
    }
    
    float mean = 0;
    for(int i = 0; i < k; i++){
      float thismean = clusters[i].mean_distance(centroids[i]);
      mean += thismean;
      cout << "Mean distance from centroid " << i << ": " << thismean << endl;
    }
    mean /= k;
    cout << "=============================================" << endl;
    cout << "       Average Distance To Centroid: " << mean << endl;
    cout << "==============================================" << endl;
  }
  return 0;
} 
