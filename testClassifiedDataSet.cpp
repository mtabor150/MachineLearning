#include <string>
#include "ClassifiedDataSet.h"
#include "DataSet.h"
#include "Distribution.h" 
using namespace std; 

int main(){
  
  Distribution a,b,c;
  float a_ent, b_ent, c_ent;
  NgramVector m_a("1", "a", "", 1);
  NgramVector m_b("2", "b", "", 1);
  NgramVector m_c("3", "c", "", 1);
  
  //two equally probable values
  m_a["a"] = 1.0;
  m_a["b"] = 1.0;
  a.dist_from_mlvector(m_a);
  a_ent = a.entropy();	//should be 1
  
  //four equally probable values
  m_b["a"]= 1.0;
  m_b["b"]= 1.0;
  m_b["c"]= 1.0;
  m_b["d"]= 1.0;
  b.dist_from_mlvector(m_b);
  b_ent = b.entropy();	//should be 2
  
  //ten equally probably values
  m_c["0"]= 1.0;
  m_c["1"]= 1.0;
  m_c["2"]= 1.0;
  m_c["3"]= 1.0;
  m_c["4"]= 1.0;
  m_c["5"]= 1.0;
  m_c["6"]= 1.0;
  m_c["7"]= 1.0;
  m_c["8"]= 1.0;
  m_c["9"]= 1.0;
  c.dist_from_mlvector(m_c);
  c_ent = c.entropy();	//should be 3.32193...
  
  
  ClassifiedDataSet<NgramVector> classified_data_set;
  classified_data_set.push_back(m_a);
  classified_data_set.push_back(m_b);
  classified_data_set.push_back(m_c);
  
  Distribution author_distribution;
  author_distribution.dist_from_dataset(classified_data_set);
  cout << "Entropy of authors distribution is: " << author_distribution.entropy() << endl;
  Distribution author_distribution_conditional_on_a;
  string a_str = "a";/*
  cout << "a" << endl;
  author_distribution_conditional_on_a.conditional_dist_from_authors_dataset(classified_data_set, a_str);
  cout << "b" << endl;
  cout << "Entropy of conditional authors distribution: " << author_distribution_conditional_on_a.entropy() << endl;*/
  
  classified_data_set.info_gain_for_each_value();
  classified_data_set.print_ordered();
  
  
  //test on bar-tweets.txt
  ifstream fin("data/bar-tweets.txt");
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
      NgramVector temp(tweet_id,user_id,"multi",3);
      vect_map[user_id] = temp;
      cout << user_id << " " << tweet << endl;// tweet << endl;
    }
    vect_map[user_id].input_string(tweet);
  }

  for(auto it=vect_map.begin(); it!=vect_map.end(); it++)
  {
    v.push_back(it->second);
  }
  
  v.info_gain_for_each_value();
  v.print_ordered();
}