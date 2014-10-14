#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <unordered_map>
#include "NgramVector.h" 
using namespace std; 

int main(){
  
  //NgramVector a("1","Me","eng",3);
  //a.input_string("aaaaaaaaafasdfasdfasdfjghapsdfubpqwebnfpiqnadfiaspdfugbpqwefbpov");
  //a.print();
  
  
  //ifstream fin("data/test-tweets.txt");
  ifstream fin("data/bar-tweets.txt");
  //ifstream fin("data/ht-tweets.txt");
  
  NgramVector b("bar-tweets","","Bavarian",3);
  int i = 0;
  while(!fin.eof()){
    string line;
    getline(fin, line);
    //cout << line << endl;
    b.input_string(line.substr(line.rfind('\t')+1,line.size()));
  }
  b.to_file("frequency_lists");
  //b.print();
  
  /*
  unordered_map<string, NgramVector> ngvectors;
  while(!fin.eof()){
    string line;
    getline(fin, line);

    string id = line.substr(0,line.find('\t'));
    string author = line.substr(line.find('\t')+1,line.rfind('\t')-line.find('\t')-1);
    string text = line.substr(line.rfind('\t')+1,line.size());
    NgramVector freq(id,author,"Haitian",3);
    freq.input_string(text);
    if(ngvectors.find(author) == ngvectors.end()){
      id = author;
      id.append("_comp");
      freq.set_id(id);
      ngvectors[author] = freq;
    }
    else
      ngvectors[author]+=freq;
  }
  for(auto it=ngvectors.begin(); it!=ngvectors.end(); ++it){
    it->second.to_tsv("frequency_lists/");
  }*/
  
  
  
  return 0;
}