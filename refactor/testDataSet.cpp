#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include "DataSet.h" 
using namespace std;

/* character vector constructor
 * works with utf-8 but not other unicode values
 * look into switching to ICU library
 */
void makeVector(MLVector<string>& charVector, string text = ""){
  int keyLength = 3;
  
  char* str = (char*)text.c_str();    	// utf-8 string
  char* begin = str;			//begining of string
  char* end = str+strlen(str);      	// end iterator
  char* it = end;       		// string iterator
  
  int size = end-begin;
  if(size <= keyLength){
    charVector[text] = 1;
  }
  
  else{
    for(int i = 0; i < keyLength; i++){
      it--;
      if(it[0] < 0 && it[1] >= 0)it--;
    }
    
    while(it >= begin){
      charVector[it] += 1;
      
      if(end[0] <= 0){
	end[0] = '\0';
	end--;
      }
      end[0] = '\0';
      end--;
      
      it--;
      if(it[0] < 0)it--;
     }
  }
}


int main(){
  
  ifstream fin("test-tweets.txt");
  
  DataSet<string> v;
  
  while(!fin.eof()){
    MLVector<string> temp;
    string line;
    getline(fin, line);
    makeVector(temp, line.substr(line.rfind('\t')+1,line.size()));
    v.push_back(temp);
  }
  
  vector<DataSet<string> > clusters;
  v.kmeans(6, clusters);

  
  return 0;
} 
