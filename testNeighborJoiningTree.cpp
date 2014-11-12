#include <map>
#include "NeighborJoiningTree.h"
#include "NgramVector.h"
#include "MLVector.h"

using namespace std;

int main()
{
  /*
  cout << "first" << endl;
  NJTree<string> nj_tree;
  NJTree<string> nj_tree2;
  NJTree<string> nj_tree3;
  cout << "second" << endl;
  DataSet<MLVector<string> > dataSet;
  MLVector<string> t, u, v;
  
  t["a"] = 1;
  t["b"] = 1;
  t["c"] = 1;
  
  //u+=t;
  u["a"] = -1;
  u["b"] = -1;
  u["c"] = -1;
  
  v["a"] = 1;
  v["g"] = 1;
  v["h"] = 1;

  dataSet.push_back(t);
  dataSet.push_back(u);
  dataSet.push_back(v);

  dataSet.print();

  nj_tree.setDataSet(dataSet);

  nj_tree.createNJTreeFromDataSet();

  nj_tree.createRoot("1");
  nj_tree2.createRoot("2");
  nj_tree3.createRoot("3");
  nj_tree3.setSubTrees(nj_tree, nj_tree2);
  nj_tree.setSubTrees(nj_tree2, nj_tree3);

  //cout << *(nj_tree.root()) << endl;
  */
  /*
  cout << "a" << endl;

  ifstream sfin("data/small-test.txt");
  //ifstream fin("data/ht-tweets.txt");

  DataSet<NgramVector> d_set;
  
  int i = 1;
  while(!sfin.eof()){
    
    string line;
    getline(sfin, line);
    string id = line.substr(0,line.find('\t'));
    string author = line.substr(line.find('\t')+1,line.rfind('\t')-line.find('\t')-1);
    string text = line.substr(line.rfind('\t')+1,line.size());
    NgramVector temp(to_string(i++),author,"multi",3);
    temp.input_string(text);
    d_set.push_back(temp);
  }

  cout << "b" << endl;

  NJTree<string> v_tree;
  v_tree.setDataSet(d_set);
  cout << "c" << endl;
  v_tree.createNJTreeFromDataSet("bavarian-tweets");
  */

  /*
   * individual user test
   */
  ifstream fin("data/ht-tweets.txt");
  //ifstream fin("data/ht-tweets.txt");
  
  DataSet<NgramVector> v;
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
  //v.print();
  NeighborJoiningTree<string> first_tree;
  first_tree.set_data(v);
  first_tree.createNJTreeFromDataSet("ht-users-new");
/*
  NgramVector vect1 = NgramVector("1", "1", "1", 1);
  NgramVector vect2 = NgramVector("2", "2", "2", 1);
  NgramVector vect3 = NgramVector("3", "3", "3", 1);
  NgramVector vect4 = NgramVector("4", "4", "4", 1);

  vect1["a"] = 1;
  vect1["b"] = 1;
  vect1["c"] = 1;

  vect2["d"] = 1;
  vect2["e"] = 1;
  vect2["f"] = 1;

  vect3["a"] = 1;
  vect3["b"] = 1;
  vect3["d"] = 1;

  vect4["a"] = 1;
  vect4["d"] = 1;
  vect4["e"] = 1;

  DataSet<NgramVector> data_set;
  data_set.push_back(vect1);
  data_set.push_back(vect2);
  data_set.push_back(vect3);
  data_set.push_back(vect4);


  NeighborJoiningTree<string> second_tree;
  second_tree.set_data(data_set);
  second_tree.createNJTreeFromDataSet("sample");*/

  //nj_tree.draw("a");
  return 0;
};