#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <unordered_map>
#include "Heap.h"
#include "DataSet.h"
#include "Distribution.h"
#include "ClassifiedDataSet.h"

using namespace std;

#define USING_XI_VALUE false

template <class VectorType = NgramVector>

class Classifier{

private:
  //classified data set for universal vector for each class
  ClassifiedDataSet<VectorType> _universal_classified_data_set;

  //normal data set to reperesent _universal_classified_data_set;
  DataSet<VectorType> _universal_data_set;
  
  //map of classified data sets for each class
  unordered_map<string, ClassifiedDataSet<VectorType> > _classified_data_sets;

  void set_universal_dataset()
  {
    _universal_data_set = (DataSet<VectorType>)_universal_classified_data_set;
  }
  
public:
  //add classified dataset
  void add_classified_dataset(ClassifiedDataSet<VectorType>& dataset, string name)
  {
    _classified_data_sets[name] = dataset;
    
    VectorType *new_vector = new VectorType("", name, "", 3);
    for(int i=0; i<dataset.size(); i++)
    {
      (*new_vector) += dataset[i];
    }
    _universal_classified_data_set.push_back(*new_vector);
  }
  
  //remove all but TOP unwanted characteristics from vectors
  void remove_unwanted_characteristics(int top)
  {
    //below accounts for all the 
    if(USING_XI_VALUE)
    {
      _universal_classified_data_set.adjust_info_gain(_classified_data_sets, top);
    }
    else
    {
      _universal_classified_data_set.remove_all_but_top_from_infogain(top);
    }
    for(int i=0; i<_universal_classified_data_set.size(); i++)
    {
      for(auto it=_universal_classified_data_set[i].begin(); it!= _universal_classified_data_set[i].end(); )
      {
      	if(!_universal_classified_data_set.key_in_info_gain(it->first))
      	{
      	  //cout << "it->first " << it->first << endl;
      	  _universal_classified_data_set[i].erase(it++->first);
      	  //cout << "it->first " << it->first << endl;
      	}
      	else
      	{
      	  it++;
      	}
      }
    }
  }
    
  
  //calculate info gain for universal classified data set and data set for each class
  void calculate_info_gain()
  {
    _universal_classified_data_set.info_gain_for_each_value();
    
    for(auto it=_classified_data_sets.begin(); it!=_classified_data_sets.end(); it++)
    {
      if(USING_XI_VALUE)
      {
        it->second.info_gain_for_each_value();
      }
      //it->second.print_ordered();
    }
    
    if(USING_XI_VALUE)
    {
      remove_unwanted_characteristics(1000);
    }
    else
    {
      //remove_unwanted_characteristics(8000);
    }
    set_universal_dataset();
  }
  
  //print the info gain for the universal classified data set
  void print_universal_info_gain()
  {
    cout << "---------------Universal InfoGain---------------------" << endl;
    _universal_classified_data_set.print_ordered(_classified_data_sets, 500);
    cout << endl;
    /*
    for(auto it=_classified_data_sets.begin(); it!=_classified_data_sets.end(); it++)
    {
      it->second.print_ordered();
      cout << endl;
    }*/
  }
  
  //TODO: change name
  void print_ordered()
  {
    _universal_classified_data_set.set_universe();
    _universal_classified_data_set.smooth();
    
    Heap<double,string> myheap;
    map<int, Heap<double,string> > userHeaps;
    
    for(auto it=_universal_classified_data_set.get_universe().begin(); it!=_universal_classified_data_set.get_universe().end(); it++)
    {
      cout << "a: " << it->first << endl;
      myheap.insert(it->second, it->first);
    }
    
    int i=0;
    while(myheap.size() > 0 && i<5000)
    {
      i++;
      cout << setw(8) << "info gain for " << setw(9)  << setprecision(5) << myheap.top_value() << " Data: " << myheap.top_data() << " ----";
      for(int i=0; i<_universal_classified_data_set.size(); i++)
      {
        cout << _universal_classified_data_set[i].get_id() << ": " << setw(8) << setfill(' ') << _universal_classified_data_set[i][myheap.top_data()] << " ";
      }
      cout << endl;
      myheap.pop();
    }
  }
  
  //classify a vector
  string naive_classify(VectorType& vector)
  {
    vector.set_author("test");
    /*
    _universal_classified_data_set.push_vector_back(vector);
    _universal_classified_data_set.set_universe();
    _universal_classified_data_set.smooth();
    _universal_classified_data_set.set_universe();*/
    unordered_map<string, long double> class_to_probability;
    //set all probabilities to 1
    for(int i=0; i<_universal_classified_data_set.size(); i++)
    {
      class_to_probability[_universal_classified_data_set[i].get_author()] = 1.0;
    }

    int m= 0;
    long double last_max_prob = 1.0;
    long double max_prob;
    //iterate through vector and calculate conditional distribution
    for(auto it=vector.begin(); it!=vector.end(); it++)
    {
      string a_str = it->first;
      if(_universal_classified_data_set[0].find(a_str) != _universal_classified_data_set[0].end())
      {
        //cout << "a_str = " << a_str << endl;
	      Distribution dist;
	      dist.conditional_dist_from_dataset(_universal_data_set, a_str);
	
      	//iterate through distribution
      	for(auto it2=class_to_probability.begin(); it2!=class_to_probability.end(); it2++)
      	{
      	  if(it2->first != "test")
      	  {
      	    it2->second += it->second*log2(dist.get_prob(it2->first));//_universal_classified_data_set.get_info_gain(it2->first);
      	  }
    	 }
      }
    }
    
    class_to_probability.begin()->second = -INFINITY;
    string current_class = class_to_probability.begin()->first;
    long double current_prob = class_to_probability.begin()->second;
    for(auto it=class_to_probability.begin(); it!= class_to_probability.end(); it++)
    {
      if(it->second > current_prob && it->first != "test")
      {
      	current_prob = it->second;
      	current_class = it->first;
      }
    }
    return current_class;
  }
  
};

#endif