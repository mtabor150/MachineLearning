#ifndef CLASSIFIEDDATASET_H
#define CLASSIFIEDDATASET_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>
#include "Heap.h"
#include "DataSet.h"
#include "Distribution.h"

using namespace std;

#define DIST_TYPE COS_DIST

#define DEBUGGING false
         
template <class VectorType = NgramVector>

class ClassifiedDataSet : public DataSet<VectorType> {
  
private:
  unordered_map<string, double> _info_gain_map;
  
  bool adjusted_info_gain = false;

public:
  
  //infogain for each value in universe
  void info_gain_for_each_value()
  {
    //smooth if we haven't already
    (*this).set_universe();
    (*this).smooth();
    
    Distribution all_dist;
    DataSet<NgramVector> temp_dataset = ((DataSet<NgramVector>)*this);
    all_dist.dist_from_dataset(temp_dataset);
    double all_entropy = all_dist.entropy();
    
    //iterate through all values in _universe
    for(auto it=this->_universe.begin(); it!=this->_universe.end(); it++)
    {
      //cout << it->first << endl;
      Distribution temp_dist;
      string temp_str = it->first;
      temp_dist.conditional_dist_from_dataset(temp_dataset, temp_str);
      
      //print out entroyp difference
      double temp_entropy = temp_dist.entropy();
      double info_gain = all_entropy - temp_entropy;
      _info_gain_map[it->first] = info_gain/all_entropy;
      //cout << "info gain for " << it->first << ": " << info_gain << endl;
    }
    if(DEBUGGING)
    {
      cout << "all_entropy: " << all_entropy << endl;
    }
  }
  
  bool key_in_info_gain(string key)
  {
    if(_info_gain_map.find(key) == _info_gain_map.end())
    {
      return true;
    }
    return false;
  }

  double get_info_gain(string key)
  {
    if(_info_gain_map.find(key) != _info_gain_map.end())
    {
      return _info_gain_map[key];
    }
    else
    {
      return 0.0;
    }
  }

  //removes all
  void remove_all_but_top_from_infogain(int top)
  {
    Heap<double,string> myheap;
    //remove all but top CEILING values from info_gain
    for(auto it=_info_gain_map.begin(); it!=_info_gain_map.end(); it++)
    {
      myheap.insert(it->second, it->first);
    }
    
    _info_gain_map.erase(_info_gain_map.begin(), _info_gain_map.end());
    
    for(int i=0; i<top; i++)
    {
      if(DEBUGGING)
      {
       cout << myheap.top_data() << " " << myheap.top_value() << endl;
      }
      _info_gain_map[myheap.top_data()] = myheap.top_value();
      myheap.pop();
    }
      
    
  }
  
  //subtract sub info gain from main info gain
  void adjust_info_gain(unordered_map<string, ClassifiedDataSet<VectorType> >& class_map, int ceiling)
  {
    if(adjusted_info_gain)
    {
      return;
    }
    //iterate through info_gain_map and subtract sub-info gain for each classified data set in class_map
    for(auto it=_info_gain_map.begin(); it!=_info_gain_map.end(); it++)
    {
      string key = it->first;
      
      //iterate through class_map to subtract sub-info gain for each classified data set
      for(auto it2=class_map.begin(); it2!=class_map.end(); it2++)
      {
    	if(it2->second.key_in_info_gain(key))
    	{
    	  it->second -= it2->second._info_gain_map[key];
    	}
      }
    }
    remove_all_but_top_from_infogain(ceiling);

    adjusted_info_gain = true;
  }
  
  void print_ordered(unordered_map<string, ClassifiedDataSet<VectorType> >& class_map, int ceiling)
  {
    Heap<double,string> myheap;
    Heap<double,string> myheap2;
    map<int, Heap<double,string> > userHeaps;
    int i=0;
    for(auto it=_info_gain_map.begin(); it!=_info_gain_map.end() ; it++)
    {
      i++;
      double value = it->second;
      myheap.insert(value, it->first);
      
      for(auto it2=class_map.begin(); it2!=class_map.end(); it2++)
      {
	if(it2->second._info_gain_map.find(it->first) != it2->second._info_gain_map.end())
	{
	  value -= it2->second._info_gain_map[it->first];
	}
      }
      myheap2.insert(value, it->first);
    }
    i=0;
    for(auto it=class_map.begin(); it!=class_map.end(); it++)
    {
      i++;
      int k = 0;
      Heap<double,string> *new_heap = new Heap<double,string>();
      for(auto it2=it->second._info_gain_map.begin(); it2!=it->second._info_gain_map.end() ; it2++)
      {
	k++;
	//cout << k << endl;
	//cout << it2->second << "-" << it2->first << endl;
	
	new_heap->insert(it2->second, it2->first);
      }
      userHeaps[i] = (*new_heap);
    }
    
    i=0;
    while(myheap.size() > 0 && i<ceiling-1)
    {
      i++;
      double value = myheap.top_value();
      cout << "number " << setw(4) << i << " key before correction: " << myheap.top_data() << "  info gain = " << setw(7)  << setprecision(5) << value << " -";
      for(auto it=class_map.begin(); it!=class_map.end(); it++)
      {
	if(it->second._info_gain_map.find(myheap.top_data()) != it->second._info_gain_map.end())
	{
	  value -= it->second._info_gain_map[myheap.top_data()];
	}
      }
      cout << " after correction = "<< setw(8)  << setprecision(5)  << value << " ----";
      
      cout << "  number " << setw(2)<< i << " key after correction: " << myheap2.top_data() << "  info gain = " << setw(7)  << setprecision(5) << myheap2.top_value() << " ----";
      cout << endl;
      myheap.pop();
      myheap2.pop();
    }
  }
  
};

#endif