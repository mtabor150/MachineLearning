#ifndef NJDISTANCEMATRIX_H
#define NJDISTANCEMATRIX_H

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include "NGramVector.h"
#include "DataSet.h"

/*
 * For now NJDistanceMatrix will only take in NGramVectors (technical debt)
 */
class NJDistanceMatrix {

public:
  struct pair {
    string element1;
    string element2;

    pair(string el1, string el2) : element1(el1), element2(el2) {}
  };

private:

  //DataSet to hold all vectors
  DataSet<NgramVector> vector_set;

  //matrix for distances
  map<string, map<string, double> > distance_matrix;

  

  //q distance matrix
  map<string, map<string, double> > q_matrix;
  //map to keep track of all ordered distances
  pair closest_q_pair= pair("0","0");

  //next id for nodes connecting combined pairs
  int next_id;

public:

  //returns whether a pair is valid or not
  //this is synonymous with the pair being in the distance_matrix
  bool pair_is_valid(pair p)
  {
    if(distance_matrix.find(p.element1) == distance_matrix.end()
    || distance_matrix.find(p.element2) == distance_matrix.end()
    || p.element1==p.element2 )
    {
      return false;
    }
    return true;
  }

  //returns the closest pair that is still in the distance matrix
  pair get_closest_pair()
  {
    return closest_q_pair;
  }

  //finds the distance between the given ids
  double distance_at(string i, string j)
  {
    return distance_matrix[i][j];
  }

  //finds the distance between the given ids
  double q_distance_at(string i, string j)
  {
    return q_matrix[i][j];
  }

  //finds the distance sum for a given id
  double distance_sum_at(string i)
  {
    return (--distance_matrix[i].end())->second;
  }

  //returns bool depecting equality of two pairs
  bool pairs_equal(pair p1, pair p2)
  {
    return ( ( (p1.element1 == p2.element1) && (p1.element2 == p2.element2) )
          || ( (p1.element1 == p2.element2) && (p1.element2 == p2.element1) ) );
  }

  double get_closest_distance()
  {
    return distance_at(closest_q_pair.element1, closest_q_pair.element2);
  }

  //get q_qistance between closest pair
  double get_closest_q_distance()
  {
    return q_distance_at(closest_q_pair.element1, closest_q_pair.element2);
  }

  //Erases all data corresponding to the elment corresponding id 
  //TODO: eventually move to private
  void remove_element(string id)
  {
    map<string, double> dist_map = distance_matrix[id];

    //erase column in disance_matrix
    distance_matrix.erase(id);

    //erase distance from all other columns
    map<string, map<string, double> >::iterator it2;
    for(it2=distance_matrix.begin(); it2!=distance_matrix.end(); it2++)
    {
      double distance = it2->second[id];
      it2->second["total_dist"] -= distance;
      it2->second.erase(id);
    }

    cout << endl;
  }

  void construct_q_matrix()
  {
    //erase contents of the q_matrix for a fresh matrix
    q_matrix.erase(q_matrix.begin(), q_matrix.end());

    //keep track of the number n for the Q(i,j) formula
    int n = distance_matrix.size();

    double shortest_q_distance = 100000000;//set as large number
    map<string, map<string, double> >::iterator it;
    for(it=distance_matrix.begin(); it!=distance_matrix.end(); it++)
    {
      string id_i = it->first;
      map<string, double> *q_map = new map<string, double>();
      map<string, double>::iterator it2;
      for(it2 = it->second.begin(); it2 != it->second.end(); it2++)
      {
        if(it2->first == "total_dist")
        {
          break;
        }
        string id_j = it2->first;

        //formula for Q(i,j)
        double q_distance_ij = ((double)n-2.0)*(it2->second) - distance_sum_at(it->first) - distance_sum_at(it2->first);
        (*q_map)[id_j] = q_distance_ij;

        if(shortest_q_distance > q_distance_ij)
        {
          shortest_q_distance = q_distance_ij;
          closest_q_pair.element1 = id_i;
          closest_q_pair.element2 = id_j;
        }

      }
      q_matrix[it->first] = (*q_map);
    }
  }


  //calculates the matrix from the given vector_set
  //this will always be the matrix that contains all distances for every NgramVector
  //in the data set
  void calculate_matrix()
  {
    next_id = vector_set.size() +1;
    //iterate through vector_set creating a new map
    for(int i=0; i<vector_set.size(); i++)
    {
      cout << i << endl;
      //set a string for the first id (this may be modified eventually)
      string id_i = to_string(i+1);

      double total_distance = 0.0;
      map<string, double> *distance_map = new map<string, double>();
      for(int j=0; j<vector_set.size(); j++)
      {
        if(j==i) //no code should go before this check. this has, and will, cause bugs.
        {
          j++;
          if(j==vector_set.size())
          {
            break;
          }
        }

        //set a string for the second id (this may be modified eventually)
        string id_j = to_string(j+1);

        double distance_ij = vector_set[i].distance(vector_set[j], COS_DIST);

        total_distance += distance_ij;

        //add distance and corresponding id to distance map.
        (*distance_map)[id_j] = distance_ij;
      }
      (*distance_map)["total_dist"] = total_distance;

      //add distance_map to the distance matrix
      distance_matrix[id_i] = (*distance_map);
    }
    construct_q_matrix();
    cout << "end" << endl;
  }

  //set vector_set
  void set_data(DataSet<NgramVector>& set)
  {
    vector_set = set;
    calculate_matrix();
  }

  //combines the closest pair and returns a pair with the values of the two id's
  pair combine_closest_pair()
  {
    string id1 = closest_q_pair.element1;
    string id2 = closest_q_pair.element2;
    double closest_distance = get_closest_distance();
    //find distance from element1 to new node and element2 to new node
    double dist_id1_to_new = 0.5*get_closest_distance() + (distance_sum_at(id1) - distance_sum_at(id2))/(2.0 * ((double)distance_matrix.size()-2.0));
    double dist_id2_to_new = get_closest_distance() - dist_id1_to_new;

    cout << "dist_id1_to_new: " << dist_id1_to_new << endl;
    cout << "dist_id2_to_new: " << dist_id2_to_new << endl;

    //calculate distance from all elements outside of the pair to the new node
    double total_distance = 0.0;
    map<string, double> *new_distance_map = new map<string, double>();
    map<string, map<string, double> >::iterator it;
    for(it=distance_matrix.begin(); it!=distance_matrix.end(); it++)
    {
      if(it->first != id1 && it->first !=id2)
      {
        double new_distance = 0.5*(it->second[id1] + it->second[id2] - closest_distance);
        total_distance += new_distance;
        (*new_distance_map)[it->first] = new_distance;
        it->second[to_string(next_id)] = new_distance;
        it->second["total_dist"] += new_distance;
      }
    }
    (*new_distance_map)["total_dist"] = total_distance;
    distance_matrix[to_string(next_id)] = (*new_distance_map);
    next_id++;
    remove_element(id1);
    remove_element(id2);
    construct_q_matrix();

    pair ret_pair(id1, id2);
    return ret_pair;
  }

  //prints the values of the distance matrix
  void print()
  {
    cout << "----------printing distance_matrix-----------" << endl;
    map<string, map<string, double> >::iterator it;
    for(it = distance_matrix.begin(); it!= distance_matrix.end(); it++)
    {
      cout << it->first << " : ";
      map<string, double>::iterator it2;
      for(it2 = it->second.begin(); it2!=(--it->second.end()); it2++)
      {

        cout<< it2->first << ": "<< setw(7) << setprecision(5) << distance_at(it->first, it2->first) << "|";
      }
      cout << "| total_distance = " << distance_sum_at(it->first);
      cout << endl;
      for(int i=0; i<8*(distance_matrix.size()-1)+30; i++)
      {
        cout <<"-";
      }
      cout << endl;
    }
  }

  void print_q_matrix()
  {
    cout << "----------printing q_matrix-----------" << endl;
    map<string, map<string, double> >::iterator it;
    for(it = q_matrix.begin(); it!= q_matrix.end(); it++)
    {
      cout << it->first << " : ";
      map<string, double>::iterator it2;
      for(it2 = it->second.begin(); it2!=(it->second.end()); it2++)
      {

        cout<< it2->first << ": " << setw(7) << setprecision(5) << q_distance_at(it->first, it2->first) << "|";
      }
      cout << "|";
      //cout << "| total_distance = " << distance_sum_at(it->first);
      cout << endl;
      for(int i=0; i<8*(distance_matrix.size()-1)+30; i++)
      {
        cout <<"-";
      }
      cout << endl;
    }
  }

  void print_pair(pair p)
  {
    cout << "(" << p.element1 << ", " << p.element2 << ")";
  }




};

#endif