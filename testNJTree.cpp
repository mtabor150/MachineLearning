#include "NJTree.h"
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
  cout << "a" << endl;

  ifstream fin("data/small-test.txt");
  //ifstream fin("data/ht-tweets.txt");

  DataSet<NgramVector> d_set;
  
  int i = 1;
  while(!fin.eof()){
    
    string line;
    getline(fin, line);
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
  v_tree.createNJTreeFromDataSet();

  //nj_tree.draw("a");
  return 0;
};