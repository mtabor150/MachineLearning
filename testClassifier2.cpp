#include <string>
#include <stdlib.h>
#include "ClassifiedDataSet.h"
#include "DataSet.h"
#include "Distribution.h" 
#include "Classifier.h"
using namespace std; 

int main(){
  
  vector<int> percentage;
  vector<int> attempts;
  vector<int> incorrect;
  
  for(int percent_held=40; percent_held<51; percent_held+=10)
  {
    percentage.push_back(percent_held);
    int num_wrong = 0;
    int iterations =0;
    int iter = 0;
    for(int iter=0; iter<10; iter++)
    {
      Classifier<NgramVector> classifier;
      
      vector<string> file_names;
      file_names.push_back("data/bar-tweets.txt");
      file_names.push_back("data/ht-tweets.txt");
      
      ClassifiedDataSet<NgramVector> test;
      
      for(int j=0; j<file_names.size(); j++)
      {
	//test on bar-tweets.txt
	ifstream fin(file_names[j]);
	//ifstream fin("data/ht-tweets.txt");
	
	
	
	ClassifiedDataSet<NgramVector> v;
	map<string, NgramVector> vect_map;

	int i = 1;
	while(!fin.eof()){
	  //NgramVector temp(to_string(i++),"2","multi",3);

	  //get line
	  string line;
	  getline(fin, line);

	  //get tweet_id
	  string tweet_id = line.substr(0,line.find('\t'));
	  line.erase(0, tweet_id.size()+1);

	  //get user_id
	  string user_id = line.substr(0,line.find('\t'));
	  line.erase(0, tweet_id.size()+1);

	  //get tweet
	  string tweet = line.substr(0,line.find('\t'));

	  //if user_id not in map
	  if(vect_map.find(user_id) == vect_map.end())
	  {
	    NgramVector temp(tweet_id,user_id,file_names[j],3);
	    vect_map[user_id] = temp;
	    //cout << user_id << " " << tweet << endl;// tweet << endl;
	  }
	  vect_map[user_id].input_string(tweet);
	}
	
	srand (time(NULL));
	//create c++ vector of random integers from 0 to vect_map.size()
	//want random 20 percent of vectors not included in training set.
	unordered_map<int,int> test_set;
	for(int i=0; i<= ((double)percent_held/(double)100)*vect_map.size(); i++)
	{
	  int iSecret;
	  bool found = false;
	  while(!found)
	  {
	    //cout << "a" << endl;
	    //find random int not yet in test set;
	    /* initialize random seed: */
	    

	    /* generate secret number between 1 and 10: */
	    iSecret = rand() % (vect_map.size()-1);
	    
	    if(test_set.find(iSecret) == test_set.end())
	    {
	      found = true;
	      test_set[iSecret] = 0;
	    }
	  }
	  //cout << iSecret << endl;
	}
	
	int m=0;
	for(auto it=vect_map.begin(); it!=vect_map.end(); it++)
	{
	  
	  if(test_set.find(m) == test_set.end())
	  {
	    v.push_back(it->second);
	    //cout << it->second.get_lang() << endl;
	  }
	  else
	  {
	    test.push_back(it->second);
	    //cout << "-"<< it->second.get_lang() << endl;
	  }
	  m++;
	}
	//v.info_gain_for_each_value();
	//v.print_ordered();
	
	classifier.add_classified_dataset(v, file_names[j]);
      }
      //classifier.print_ordered();
      classifier.calculate_info_gain();
      
      
      for(int i=0; i<test.size(); i++)
      {
	iterations++;
	cout << "------------------------------" << endl;
	string expected = test[i].get_lang();
	cout << "exptected: " << expected << endl;
	string return_val = classifier.naive_classify(test[i]);
	cout << "actual:    " << return_val << endl;
	if(expected != return_val)
	{
	  cout << "incorrectly guessed value" << endl;
	  num_wrong++;
	}
      }
      
      cout << "number wrong for " << iterations << " iterations = " << num_wrong << endl;
      //classifier.print_universal_info_gain();
      
      //add error and iterations
      
    }
    attempts.push_back(iterations);
    incorrect.push_back(num_wrong);
    for(int num=0; num<percentage.size(); num++)
      {
	cout << "==============================================" << endl;
	cout << "-----------------------------------" << endl;
	cout << "trial percentage: " << percentage[num] << endl;
	cout << "attempst        : " << attempts[num] << endl;
	cout << "incorrect       : " << incorrect[num] << endl;
	cout << "error           : " << incorrect[num]/attempts[num] << endl;
      }
  }
}