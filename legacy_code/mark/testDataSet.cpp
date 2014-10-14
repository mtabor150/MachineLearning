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
      if(it[0] < 0){
	while(it[0] < -64){
	  it--;
	}
      }
    }
    
    while(it >= begin){
      charVector[it] += 1;
      end--;
      while(end[0] < -64){
	  end[0] = '\0';
	  end--;
      }
      end[0] = '\0';
      
      it--;
      while(it[0] < -64){
	it--;
      }
    }
  }
}


int main(){
  
//   string t = "💃”😍😩😂èå";
//   
//   int size = t.size();
//   for(int i = 0; i < size; i++) cout << (int)t[i] <<" ";
//   cout << endl;
//   
//   char a = 0b10000000;
//   char b = 0b10110000;
//   char c = 0b10111111;
//   char d = 0b11000000;
//   char e = 0b11100000;
//   
//   cout << (int)a << " " << (int)b << " "<< (int)c << " "<< (int)d << " " << (int)e << endl;
 

//   string a = "Woup woup 💃💃💃💃💃💃💃💃“@VwaDeZil: Bon fanatik vwadezil yo prezidan an sot fe relem li ba nou cha, mesi anpil anpil pou support nou”";
//   string b = "😍😍😍😍 😩😩😩 😂😂😂😂😂😂😂";
//   string c = "💃”😍😩😂èå";
//   MLVector<string> temp;
//   makeVector(temp, a);
//   makeVector(temp, b);
//   makeVector(temp, c);
  
  ifstream fin("test-tweets.txt");
  
  DataSet<string> v;
  
  while(!fin.eof()){
    MLVector<string> temp;
    string line;
    getline(fin, line);
    makeVector(temp, line.substr(line.rfind('\t')+1,line.size()));
    v.push_back(temp);
  }
  
  int size = v.size();
  for(int i = 0; i < size; i++){
    v[i].print(to_string(i));
  }
  
  //vector<DataSet<string> > clusters;
  //v.kmeans(6, clusters);

  
  return 0;
} 
