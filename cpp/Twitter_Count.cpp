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
#define vector_map map<int, three_char_vector>
#define EPS pow(10,-8)


vector_map vector_map_constructor(string filename)
{
	tweet_list t_list;
	t_list = parse_tweet_file(filename);

	vector_map ret_map = vector_map();

	//loop through tweet list counting up all three character occurencs
	//for each user_id
	int t_list_size = t_list.size();
	id_tweet_pair pair;
	int u_id;
	string tweet;
	int i = 0;
	struct three_char_vector temp_vect;
	//TODO: implement with multithreading for use on Turing
	for(tweet_list::iterator it = t_list.begin(); it !=t_list.end(); it++)
	{
		cout << i << endl;
		pair = *it;
		u_id = pair.user_id;
		tweet = pair.tweet;
		//check if user id is in return map
		if(ret_map.count(u_id))
		{
			three_char_count_with_vector(tweet, &ret_map[u_id]);
		}
		else
		{
			ret_map[u_id] = three_char_count(tweet);
		}
		i++;
	}

	return ret_map;
}



void print_vect_with_id(vector_map map, int id)
{
	three_char_vector vect;
	vect = map[id];
	print_vector(vect);
}

void print_all_ids(vector_map map)
{
	std::vector_map::iterator it;
	for(it=map.begin(); it!=map.end(); ++it)
	{
		cout << "id: " << it->first << endl;
		//print_vect_with_id(map, it->first);
	}
}

void copy_map(vector_map map, std::vector_map copy)
{
	std::vector_map::iterator it;
	for(it=map.begin(); it!=map.end(); ++it)
	{
		copy[it->first] = it->second;
	}
}

void print_all_distances(vector_map map)//map<int, three_char_vector> copy)
{
	std::vector_map::iterator it;
	for(it=map.begin(); it!=map.end(); ++it)
	{
		std::vector_map::iterator it2;
		for(it2 = map.begin(); it2!=map.end(); ++it2)
		{
			double temp = VAngle(it->second, it2->second);
			if(abs(temp) < EPS)
			{
				cout << " 0.00000";
			}
			else
			{
			cout << " " << temp;
			}
		}
		cout << endl;
	}
}

int main()
{
	std::vector_map vect_map = std::vector_map();

	vect_map = vector_map_constructor("../twitter_text/ht-tweets.txt");
	print_all_ids(vect_map);
	print_all_distances(vect_map);
}