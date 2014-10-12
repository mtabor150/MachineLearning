#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
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
    cout << line << endl;
    b.input_string(line.substr(line.rfind('\t')+1,line.size()));
  }
  b.to_csv("frequency_lists");
  //b.print();
  
//   while(!fin.eof()){
//     string line;
//     getline(fin, line);
//     
//     string id = line.substr(0,line.find('\t'));
//     string author = line.substr(line.find('\t')+1,line.rfind('\t')-line.find('\t')-1);
//     string text = line.substr(line.rfind('\t')+1,line.size());
//     NgramVector freq(id,author,"Bavarian",3);
//     freq.input_string(text);
//     freq.to_csv("frequency_lists/");
//   }
  
  
  
  
  return 0;
}