#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct tweet{
  string tid;  
  string uid;
  unordered_map<string, float> charVector;
};

tweet makeTweet(string tid, string uid, string data);
void readInTweets(unordered_map<string, tweet>* vectors, string filename);
void printTweet(tweet* t);
void consolidate(unordered_map<string, tweet>* tweets);