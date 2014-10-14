#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "charVector.h"
#include "MLVector.h"
#include "DataSet.h"
#include "tweet.h"

using namespace std;

tweet makeTweet(string tid, string uid, string data){
  struct tweet twt;
  twt.tid = tid;
  twt.uid = uid;
  unordered_map<string, float>* pV = &twt.charVector;
  makeVector(pV, data);
  return twt;
}


void readInTweets(unordered_map<string, tweet>* vectors, string filename){

  ifstream fin(filename.c_str());

  while(!fin.eof()){
    struct tweet tempTweet;
    string temp_tid;
    string temp_uid;
    string line;
   
    getline(fin, line);
    
    temp_tid = line.substr(0,line.find('\t'));
    temp_uid = line.substr(line.find('\t')+1,line.rfind('\t')-line.find('\t'));
    
    tempTweet = makeTweet(temp_tid, temp_uid, line.substr(line.rfind('\t')+1,line.size()));
    
    (*vectors)[tempTweet.tid] = tempTweet;
  }
}

void printTweet(tweet* t){
  cout << "Tweet ID: "<< (*t).tid << "  User ID: " << (*t).uid << '\n';
  unordered_map<string, float>* ptr = &(*t).charVector; 
  printVector(ptr);
}

void consolidate(unordered_map<string, tweet>* tweets){
  unordered_map<string, tweet> cTweets;
  int i = 0;
  //int count = 0;
  for(unordered_map<string, tweet>::iterator it=(*tweets).begin(); it!=(*tweets).end(); ++it){
    unordered_map<string, tweet>::iterator current = cTweets.find(it->second.uid);
    if(current == cTweets.end()){
      i++;
      it->second.tid = to_string(i);
      cTweets[it->second.uid] = it->second;
    }
    else{
      unordered_map<string, float> temp = current->second.charVector;
      unordered_map<string, float> *pta, *ptb, *ptc;
      pta = &it->second.charVector;
      ptb = &temp;
      ptc = &current->second.charVector;
      addVectors(pta, ptb, ptc);
     }
//      count++;
//      cout << count << endl;
  }
  
  (*tweets) = cTweets;
}