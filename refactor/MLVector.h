#ifndef MLVECTOR_H
#define MLVECTOR_H

#include <cmath>
#include <iostream>
#include <unordered_map>
using namespace std;

enum dist_type
{
  COS_DIST,
  L0_DIST,
  L1_DIST,
  L2_DIST,
  LINF_DIST
};

template < class Key,                                    // unordered_map::key_type
           class T = float,                              // unordered_map::mapped_type
           class Hash = hash<Key>,                       // unordered_map::hasher
           class Pred = equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
           > 
           
class MLVector : public unordered_map<Key, T, Hash, Pred, Alloc>  {

public:
  
  /* operator+=() */
  MLVector& operator+=(const MLVector& other){
    for(auto it=other.cbegin(); it!=other.cend(); ++it){
      (*this)[it->first] += it->second;
    }
  }
  /* end operator+=() */
  

  /* operator/=() */
  MLVector& operator/=(float divisor){
    for(auto it=(*this).begin(); it!=(*this).end(); ++it){
      (*this)[it->first] /= divisor;
    }
  }
  /* end operator/=() */

  
  /* print()
   * function for easy printing of vectors*/
  void print(const string& header = "vector" ){
    cout << endl;
    int i = 0;
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      cout << "{" << it->first << ":" << it -> second << "} ";
      i++;
      if(i%15 == 0) cout << endl;
    }
    cout << endl;
  }
  /* end print() */
  
  
  /* cosine_distance() 
   * dot product divided by product of vector magnitudes*/
  float cosine_distance(const MLVector& other){
    float this_magnitude = 0, other_magnitude = 0, this_dot_other = 0;
    
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      float value = it->second;
      this_magnitude += (value*value);
      if(other.find(it->first) != other.end()){
	      this_dot_other += (value*other.at(it->first));
      }
    }
    
    for(auto it=other.cbegin(); it!=other.cend(); ++it){
      float value = it->second;
      other_magnitude += (value*value);
    }
    
    float cosine = this_dot_other/(sqrt(this_magnitude)*sqrt(other_magnitude));
    cosine = 1 - cosine;
    return cosine;
  }
  /* end cosine_distance() */
  
  
  /* l0_distance()
   * absolute difference between like elements*/
  float l0_distance(const MLVector& other){
    float l0 = 0;
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      //take the abs() of the difference of like elements
      if(other.find(it->first) != other.end()){
	      l0 += abs(it->second-other.at(it->first));
      }
    }
    return l0;
  }
  /* end l0_distance() */
  
  
  /* l1_distance()
   * manhattan distance - sum of absolute values of differences between elements*/
  float l1_distance(const MLVector& other){
    float l1 = 0;
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      //take the abs() of the difference of like elements
      if(other.find(it->first) != other.end()){
	      l1 += abs(it->second-other.at(it->first));
      }
      //add everything in this thats not in other
      else l1 += abs(it->second);
    }
    
    //find everything in other thats not in this
    for(auto it=other.cbegin(); it!=other.cend(); ++it){
      if((*this).find(it->first) == (*this).end()){
	      l1 += abs(it->second);
      }

    }
    return l1;
  }
  /* end l1_distance() */
  
  
  /* l2_distance()
   * euclidean distance*/
  float l2_distance(const MLVector& other){
    float l2 = 0;
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      //square the difference of like elements
      if(other.find(it->first) != other.end()){
	      float value = it->second-other.at(it->first);
	      l2 += (value*value);
      }
      //add squared unlike elements
      else l2 += (it->second*it->second);
    }

    //find everything in other thats not in this
    for(auto it=other.cbegin(); it!=other.cend(); ++it){
      if((*this).find(it->first) == (*this).end()){
	      l2 += (it->second*it->second);
      }
    }
    return sqrt(l2);
  }
  /* end l2_distance */
  

  /* linfinity_distance()
   * absolute max distance between elements*/
  float linfinity_distance(const MLVector& other){
    float linf = 0;
    for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
      //shared elements
      if(other.find(it->first) != other.end()){
	      float current = abs(it->second-other.at(it->first));
	      if(current > linf){
	        linf = current;
	      }
      }
      //elements only in this
      else {
	      float current = abs(it->second);
	      if(current > linf){
	        linf = current;
	      }
      }
    }
    //find everything in other thats not in this
    for(auto it=other.cbegin(); it!=other.cend(); ++it){
      if((*this).find(it->first) == (*this).end()){
	      float current = abs(it->second);
	      if(current > linf){
	        linf = current;
	      }
      }
    }
    return linf;
  }
  /* end linfinity_distance() */


  /* distance()
   * mutli-purpose distance function */
  float distance(const MLVector& other, dist_type type){
    float ret_dist; // return distance
    switch(type){
      case COS_DIST:
        ret_dist = cosine_distance(other);
        break;
      case L0_DIST:
        ret_dist = l0_distance(other);
        break;
      case L1_DIST:
        ret_dist = l1_distance(other);
        break;
      case L2_DIST:
        ret_dist = l2_distance(other);
        break;
      case LINF_DIST:
        ret_dist = linfinity_distance(other);
        break;
      default:
        cout << "default in distance hit" << endl;
        ret_dist = -1.0;
        break;
    }
    return ret_dist;
  }
  /* end distance() */

};

#endif
