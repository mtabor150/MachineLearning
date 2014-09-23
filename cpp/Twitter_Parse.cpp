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
tweet_list parse_tweet_file(string filename)
{
	

	//read in tweet text
	cout << filename << endl;
	ifstream t(filename);
	string tweet_text;
	t.seekg(0, ios::end);   
	tweet_text.reserve(t.tellg());
	t.seekg(0, ios::beg);
	tweet_text.assign((istreambuf_iterator<char>(t)), istreambuf_iterator<char>());

	//get numlines in file
	int file_size = count(tweet_text.begin(), tweet_text.end(), '\n');

	//return vector
	tweet_list return_vector = vector<id_tweet_pair>(file_size);

	size_t pos = 0;
	string token;
	string delimiter = "\n";
	//iterate through new lines
	struct id_tweet_pair temp_pair;
	int i =0;
	while ((pos = tweet_text.find(delimiter)) != string::npos) 
	{
		//cout << i << ": ";
	    token = tweet_text.substr(0, pos);
	    tweet_text.erase(0, pos + delimiter.length());

	    //iterate through tabs
	    int j = 0;
	    size_t inner_pos = 0;
	    string delim2 = "\t";
	    string inner_token = "d";
	    string last_token;
	    while(j<3)
	    {
	    	inner_pos = token.find(delim2);
	    	last_token = inner_token;
	    	inner_token = token.substr(0, inner_pos-1);
	    	//tweet_text.erase(0, inner_pos + delim2.length());
	    	//if last_token is same as inner_token, then most likely we have found a newline within a tweet
	    	if(last_token == inner_token)
	    			break;
	    	token.erase(0, inner_pos + delim2.length());
	    	switch(j)
	    	{
	    		case 0:
	    			break;
	    		case 1:
	    			
	    			temp_pair.user_id = stoi(inner_token);
	    			break;
	    		case 2:
	    			strncpy(temp_pair.tweet, inner_token.c_str(), sizeof(temp_pair.tweet));
	    			temp_pair.tweet[sizeof(temp_pair.tweet)-1] = 0;
					break;
				default:
					break;
	    	}
	    	j++;
	    }
	    return_vector[i] = temp_pair;
	    i++;
	}
	return return_vector;
}

//print all id-tweet pairs
void print_pair(tweet_list vect_pair)
{
	for(int i = 0; i<vect_pair.size(); i++)
	{
		cout << "[" << i << "] " << vect_pair[i].user_id << " : " << vect_pair[i].tweet;
		cout << endl;
	}
}