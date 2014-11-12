#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include "NgramVector.h"
#include "DataSet.h" 
using namespace std;


int main(){
  //ifstream fin("data/small-test.txt");
  //ifstream fin("data/test-tweets.txt");
  ifstream fin("data/bar-tweets.txt");
  //ifstream fin("data/ht-tweets.txt");
  
  DataSet<NgramVector> v;
  map<string, NgramVector> vect_map;
  int i = 1;
  while(!fin.eof()){
    //NgramVector temp(to_string(i++),"2","multi",3);

    //get line
    string line;
    getline(fin, line);

    //get tweet_id
    string tweet_id = line.substr(0,line.find('\t'));
    line.erase(0, tweet_id.size()+1);

    //get user_id
    string id = line.substr(0,line.find('\t'));
    line.erase(0, tweet_id.size()+1);

    //get tweet
    string tweet = line.substr(0,line.find('\t'));

    //if user_id not in map
    if(vect_map.find(id) == vect_map.end())
    {
      NgramVector temp(id,"2","multi",3);
      vect_map[id] = temp;
      cout << id << " " << tweet << endl;// tweet << endl;
    }
    vect_map[id].input_string(tweet);
  }

  for(auto it=vect_map.begin(); it!=vect_map.end(); it++)
  {
    v.push_back(it->second);
  }
  v.print();
  
  /*
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
  }*/
  return 0;
} 
