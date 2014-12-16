#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <unordered_map>
#include "MLVector.h"
#include "DataSet.h"

using namespace std;

           
class Distribution{

private:
  unordered_map<string, double>* _dist;
  

public:
  
  //dist will hold a discrete probability distribution
  Distribution() : _dist(new unordered_map<string,double>) {}
  
  double get_prob(string key)
  {
    return (*_dist)[key];
  }
  
  bool check_dist_sum(string extra_message = "")
  {
    double total;
    for(auto it = _dist->begin(); it != _dist->end(); it++)
    {
      total += it->second;
    }
    if(abs(total - 1) < pow(10,-6))
    {
      //cout << "-----------------------------------------------------------------------------------" << endl;
      //cout << "probability distribution sum = " << total << endl;
      //cout << "valid probability distribution" << endl;
      return true;
    }
    else
    {
      cout << "----------invalid probability distribution: distribution adds up to " << total << "----------"<< endl;
      for(auto it=_dist->begin(); it!=_dist->end(); it++)
      {
	      cout << it->first << ": " << it->second << endl;
      }
      cout << "extra message: " << extra_message << endl;
      return false;
    }
  }
  
  void dist_from_mlvector_file(string filename = "")
  {
    //start with a fresh distribution
    _dist->erase(_dist->begin(), _dist->end());
    
    //iterate through file
    if (filename.compare("") != 0){
      double total = 0;
      ifstream fin(filename.c_str());
      while(!fin.eof()){
        string line, key;
        double val = 0;
        getline(fin, line);
        key = line.substr(0,line.find('\t'));
        val = atoi(line.substr(line.find('\t')+1, line.size()).c_str());
        (*_dist)[key] = val;
        total+=val;
      }
      
      for(auto it = (*_dist).begin(); it != (*_dist).end(); ++it){
        it->second /= total;
      }
    }
    
    //verify that the probability distrubtion adds up to one
    check_dist_sum();
  }
  
  void dist_from_mlvector(NgramVector& mlvector)
  {
    //start with a fresh distribution
    _dist->erase(_dist->begin(), _dist->end());
    
    //iterate through mlvector
    double total = 0;
    for(auto it=mlvector.begin(); it!=mlvector.end(); it++)
    {
      total += it->second;
      (*_dist)[it->first] = it->second;
    }
    for(auto it=_dist->begin(); it!=_dist->end(); it++)
    {
      it->second /= total;
    }
    
    //verify that the probability distribution adds up to one
    check_dist_sum();
  }
  
  //probability distribution from a dataSet of mlvectors for each author
  void dist_from_dataset(DataSet<NgramVector>& dataset)
  {
    //start with a fresh distribution
    _dist->erase(_dist->begin(), _dist->end());
    
    int size = dataset.size();
    for(int i=0; i<size; i++)
    {
      (*_dist)[to_string(i)] = 1.0/(double)size;
    }
    
    //verify that the probability distribution adds up to one
    check_dist_sum();
  }
  
  //conditional probability distribution from a dataSet of mlvectors for each author
  void conditional_dist_from_dataset(DataSet<NgramVector>& dataset, string& key)
  {
    _dist->erase(_dist->begin(), _dist->end());
    
    //smooth if we haven't already
    dataset.set_universe();
    dataset.smooth();
    
    if(dataset.get_universe_value(key) == 0)
    {
      cout << "error: key does not exist in universe" << endl;
      cout << key << endl;
    }
    else
    {
      //cout << "good key: " << key << endl;
    }
    
    //double prob_even = 1.0/(double)size;
    double p_w = 0.0;
    
    //TODO: implement smooth so each author has at least some probabilty of seeing a certain key
    //      for now this distribution could have a few 0 probability values
    //iterate through dataset and get probability of each mlvector in dataset
    for(int i=0; i<dataset.size(); i++)
    {
      if(dataset[i].get_author()!="test")
      {
      	int size = dataset.size();
      	
      	//Distribution i_dist;
      	//i_dist.dist_from_mlvector(dataset[i]);
      	double p_w_c = dataset[i][key]/dataset[i].get_total();//i_dist.get_prob(key);
      	p_w += p_w_c;
      	
      	//p_w_c is p(w|c) and p_w is p(w)
      	//p(w|c) should come from a distribution made from dataset[i]
      	//p(w) should come from all the distributions added together divided by the number of distributions
      	double probability = p_w_c;// * prob_even / p_w;
      	
      	//double probability = (((double)dataset[i][key] / (double)dataset[i].get_total() )*prob_even) / ((double)dataset.get_universe_value(key)/(double)dataset.get_universe_total());
      	(*_dist)[dataset[i].get_author()] = probability;
      }
    }
    
    for(auto it=_dist->begin(); it!=_dist->end(); it++)
    {
      it->second /= p_w;
    }
    
    //verify that the probability distribution adds up to one
    check_dist_sum(key);
  }
    
  
  ~Distribution(){
    delete _dist;
  }
  
  double entropy() const{
    double entropy = 0;
    for(unordered_map<string,double>::iterator it = (*_dist).begin(); it != (*_dist).end(); ++it){
      double prob = it->second;
      entropy -= prob*log2(prob);
    }
    return entropy;
  }
  
  
  void add_point(string key, double value){
    (*_dist)[key] = value;
  }
  
  double info_gain(const Distribution& other) const{
    double this_entropy = entropy(), other_entropy = other.entropy();
    return (this_entropy - other_entropy);
  }

};

#endif
