#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "MLVector.h"
#include "DataSet.h"
#include "tweet.h"

using namespace std;

int main(){
  
  unordered_map<string, tweet> tweets;
  unordered_map<string, tweet>* pt = &tweets;
  readInTweets(pt, "bar-tweets.txt");
  
  //readInTweets(pt, "ht-tweets.txt");
  //consolidate(pt);
//   int i = 0;
//   for(unordered_map<string, tweet>::iterator it=tweets.begin(); it!=tweets.end(); ++it){
//     cout << "=========  " << i << "  ========\n";
//     tweet* ptr = &(it->second);
//     printTweet(ptr);
//     i++;
//   }
  
  
  vector<unordered_map<string, float> > tVectors;
  vector<cluster> clusters;
  for(unordered_map<string, tweet>::iterator it=tweets.begin(); it!=tweets.end(); ++it){
    tVectors.push_back(it->second.charVector);
  }
  
  vector<unordered_map<string, float> > *tVptr;
  vector<cluster> *clustptr;
  tVptr = &tVectors;
  clustptr = &clusters;
  
  kMeans(3, tVptr, clustptr);
  
  
  
  
 //char* str = (char*)"å";
 //cout << (int)str[0] << " " << (int)str[1] << endl;
  

//   for(int k = 0; k+12 < length; k+=12){
//     float angleMatrix[12][12];
//     for(int j = k; j < k+12; j++){
//       for(int i = k; i < k+12; i++){
// 	angleMatrix[i%12][j%12] = vAngle(tweets[i].charVector, tweets[j].charVector);
// 	printf("%06f  ", angleMatrix[i%12][j%12]);
//       }
//       cout << '\n';
//     }
//     cout << '\n';
//   }
  
  /*
  unordered_map<string, float> a, b, c, ab, abc, mean;
  
  unordered_map<string, float>* ap = &a;
  unordered_map<string, float>* bp = &b;
  unordered_map<string, float>* cp = &c;
  unordered_map<string, float>* abp = &ab;
  unordered_map<string, float>* abcp = &abc;
  unordered_map<string, float>* mp = &mean;
  makeVector(ap, "aaaaaaaaabbbcccjklmhijdef");
  cout << "======== Vector a =========" << endl;
  printVector(ap);
  
  makeVector(bp, "aaaaaaaaabbbcccdefjklmnop");
  cout << "======== Vector b =========" << endl;
  printVector(bp);
  
  addVectors(ap, bp, abp);
  cout << "======== Vector a+b =========" << endl;
  printVector(abp);
  
  makeVector(cp, "aaabbbcccdefjklmnop");
  cout << "======== Vector c =========" << endl;
  printVector(cp);
  
  addVectors(abp, cp, abcp);
  cout << "======== Vector a+b+c =========" << endl;
  printVector(abcp);
  
  
  vector< unordered_map<string, float> > vectors;
  vector< unordered_map<string, float> >* pv = &vectors;
  vectors.push_back(a);
  vectors.push_back(b);
  vectors.push_back(c);
  vectors.push_back(ab);  
  vectors.push_back(abc);
  
  cout << "========Mean Vector=========" << endl;
  
  meanVector(pv, mp);
  printVector(mp);
  
  vectors.push_back(mean);
  
  int ln = 6;
  
  float angleMatrix[ln][ln];
  unordered_map<string, float> *ptrA, *ptrB;
  for(int j = 0; j < ln; j++){
    for(int i = 0; i < ln; i++){
      ptrA = &vectors[i];
      ptrB = &vectors[j];
      angleMatrix[i][j] = vAngle(ptrA, ptrB);
      printf("%02.03f  ", angleMatrix[i][j]);
    }
    cout << '\n';
  }*/
  
  return 0;
}
