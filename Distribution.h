#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

           
class Distribution{

private:
  unordered_map<string,float>* _dist;
  
public:
  
  Distribution(string filename = ""): _dist(new unordered_map<string,float>){
    if (filename.compare("") != 0){
      int total = 0;
      ifstream fin(filename.c_str());
      while(!fin.eof()){
	string line, key;
	int val = 0;
	getline(fin, line);
	key = line.substr(0,line.find('\t'));
	val = atoi(line.substr(line.find('\t')+1, line.size()).c_str());
	(*_dist)[key] = val;
	total+=val;
      }
      
      for(unordered_map<string,float>::iterator it = (*_dist).begin(); it != (*_dist).end(); ++it){
	it->second /= total;
      }
    }
  }
  
  ~Distribution(){
    delete _dist;
  }
  
  float entropy(){}
  
  void add_point(string key, float value){
    (*_dist)[key] = value;
  }
  
  float info_gain(){}
  
  
  
};

#endif
