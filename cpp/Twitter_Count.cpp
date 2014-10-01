/* 
 * copyright 2014, Phillip Martin
 * Twitter_Count.cpp provides data structures and implementations for the
 * purposes of holding the three character vectors for each particular 
 * twitter user id.
 */
#include <iostream>
#include <map>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>

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

three_char_vector average_vector(vector_map *map)
{
	three_char_vector ret_vect = three_char_vector();

	//iterate through map
	three_char_vector temp_vect;
	vector_map::iterator iter;
	for(iter = map->begin(); iter != map->end(); ++iter)
	{
		temp_vect = unit_vector(&iter->second);
		ret_vect = add_dict(&temp_vect, &ret_vect);
	}

	return ret_vect;
}



void print_vect_with_id(vector_map *map, int id)
{
	three_char_vector *vect;
	vect = &(*map)[id];
	print_vector(vect);
}

void print_all_ids(vector_map *map)
{
	vector_map::iterator it;
	for(it=map->begin(); it!=map->end(); ++it)
	{
		cout << "id: " << it->first << endl;
		//print_vect_with_id(map, it->first);
	}
}

void print_all_distances(vector_map *map)//map<int, three_char_vector> copy)
{
	vector_map::iterator it;
	for(it=map->begin(); it!=map->end(); ++it)
	{
		vector_map::iterator it2;
		for(it2 = map->begin(); it2!=map->end(); ++it2)
		{
			double temp = VAngle(&it->second, &it2->second);
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

//writes each three_char_vector to a .csv file at the location of "path" with the user_id as file name
void write_vector_map_to_file(vector_map * map, string path)
{
	//check to see if directory exists
	struct stat info;

	if( stat( path.c_str(), &info ) != 0 )
	{
	    printf( "%s is no directory\n", path.c_str() );
		printf( "creating directory %s\n", path.c_str() );
		mkdir(path.c_str(),0777);
	}

	string temp = "";
	temp.append(path);
	vector_map::iterator iter;
	for(iter = map->begin(); iter!=map->end(); ++iter)
	{
		//create local varables
		three_char_vector vect = iter->second;
		dictionary dict = vect.dict;

		//reset temp to path
		temp = "";
		temp.append(path);

		//append proper filename
		string file_name = to_string(iter->first);
		file_name.append(".csv");
		temp.append(file_name);

		ofstream fout(temp);
	    // for each key
	    dictionary::iterator iter2;
	    for (iter2 = dict.begin(); iter2 != dict.end(); ++iter2) {
	    	//cout << " x x x" << endl;
	        // print key and value
	        //cout << iter2->first << ',' << iter2->second << "\n";
	        fout << "\"" << iter2->first << "\"" << ',' << iter2->second << "\n";
	    }
	    fout.close();
	}
}