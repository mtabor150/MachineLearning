/* 
 * copyright 2014, Phillip Martin
 * Twitter_Parse will provide a datastructure and implementations for
 * parsing twitter data into that datastructure
 */

#include <iostream>
#include <map>
#include <string>
#include <math.h>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "Three_Char_Vector.h"

using namespace std;

#define MAX_TWEET_CHARS 140


//struct to hold user id and tweet
struct id_tweet_pair
{
	int user_id;
	char tweet[MAX_TWEET_CHARS];
};

//define tweet_list as a vector of id_tweet pairs
#define tweet_list vector<id_tweet_pair>

//function will parse file delimited by new lines and tabs into a
//vector with id-tweet pairs
vector<id_tweet_pair> parse_tweet_file(string filename);

void print_pair(vector<id_tweet_pair> vect_pair);