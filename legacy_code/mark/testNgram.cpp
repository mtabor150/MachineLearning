#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "NgramVector.h" 
using namespace std; 

int main(){
  
  NgramVector a("1","2","brit",3);
  a.input("aaaaaaaaafasdfasdfasdfjghapsdfubpqwebnfpiqnadfiaspdfugbpqwefbpov");
  a.print();
  
  
  
  
  
  return 0;
}