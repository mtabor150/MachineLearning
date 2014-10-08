#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "NgramVector.h" 
using namespace std; 

int main(){
  
  NgramVector a("1","Me","eng",3);
  a.input_string("aaaaaaaaafasdfasdfasdfjghapsdfubpqwebnfpiqnadfiaspdfugbpqwefbpov");
  a.print();
  
  
  ifstream fin("test-tweets.txt");
  
  NgramVector b("2","twitter","multi",3);
  int i = 0;
  while(!fin.eof()){
    string line;
    getline(fin, line);
    b.input_string(line.substr(line.rfind('\t')+1,line.size()));
  }
  b.print();
  
  
  
  
  return 0;
}