/*
 *Twitter_Parse.cpp Test File
 */
 #include "Twitter_Parse.h"

 int main()
 {
 	tweet_list pair_list = tweet_list();
 	pair_list = parse_tweet_file("bar-tweets.txt");

	print_pair(pair_list);

	pair_list = parse_tweet_file("ht-tweets.txt");
	
	print_pair(pair_list);
 }