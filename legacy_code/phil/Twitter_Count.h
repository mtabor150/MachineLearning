/* 
 * copyright 2014, Phillip Martin
 * Twitter_Count.cpp provides data structures and implementations for the
 * purposes of holding the three character vectors for each particular 
 * twitter user id.
 */
#include <iostream>
#include <map>
#include <cmath>

#include "Three_Char_Vector.h"
#include "Twitter_Parse.h"

using namespace std;

//struct to hold vector and user_id
struct id_vector_pair
{
	int user_id;
	three_char_vector tc_vector;
};


//define a map for id_vector_pairs
typedef map<int, three_char_vector> vector_map;

#define EPS pow(10,-8)


vector_map vector_map_constructor(string filename);

three_char_vector average_vector(vector_map *map);

void print_vect_with_id(vector_map *map, int id);

void print_all_ids(vector_map *map);

void print_all_vectors(vector_map *map);

void print_all_distances(vector_map *map);

void write_vector_map_to_file(vector_map * map, string path);

vector_map read_file_to_vector_map(string path);
