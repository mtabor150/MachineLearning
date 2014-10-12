#ifndef NGRAMVECTOR_H
#define NGRAMVECTOR_H

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include "MLVector.h"
using namespace std;


class NgramVector: public MLVector<string> {
private:
  string _id;  
  string _author;
  string _lang;
  int _keyLength;
  
public:
  /*constructor*/
  NgramVector(string id="", string author="", string lang="", int k=3) : _id(id), _author(author), _lang(lang), _keyLength(k) {}
  
  /*setters*/
  void set_id(const string& id){
    _id = id;
  }
  
  
  void set_author(const string& author){
    _author = author;
  }
  
  
  void set_lang(const string& lang){
    _lang = lang;
  }
  
  
  void set_keyLength(int k){
    _keyLength = k;
  }
  
  
  /*getters*/
  string get_id(const string& id){
    return _id;
  }
  
  
  string get_author(const string& author){
    return _author;
  }
  
  
  string get_lang(const string& lang){
    return _lang;
  }
  
  
  int get_keyLength(int k){
    return _keyLength;
  }
  
  
  void print(){
    cout << endl;
    cout << "=================================================================" << endl;  
    cout << "ID: " << _id << "     Author: " << _author << "     Language: " << _lang << "     Key length: " << _keyLength << endl;
    (*this).MLVector::print();
  }
  
  void to_csv(string directory = "/"){
    struct stat info;
    
    int size = directory.size();
    if(directory[size-1] != '/')
      directory.append("/");
    if(strcmp(_lang.c_str(), "") != 0){
      directory.append(_lang);
      directory.append("/");
    }
    
    if(strcmp(_author.c_str(), "") != 0){
      directory.append(_author);
      directory.append("/");
    }
    
    if(stat(directory.c_str(), &info) != 0 ){
      mkdir(directory.c_str(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    
    if(strcmp(_id.c_str(), "") != 0){
      directory.append(_id);
      
    }
    else
      directory.append("foo");
    directory.append(".csv");
    
    ofstream file(directory);
    
    if (file.is_open()){
      priority_queue<string> heap;
      
      file << "Key,Value" << endl;
      for(auto it=(*this).cbegin(); it!=(*this).cend(); ++it){
	file << "\"" << it->first << "\"," << it->second << endl;
      }
      file.close();
    }
    else{
      cout << "File: " << directory << endl;
      throw runtime_error("unable to open file");
    }
  }
  
  
  /* splits strings and enters them in the vector
   * works with utf-8 but not other unicode values
   * look into switching to ICU library
   */
  NgramVector& input_string(const string& text){
    char* str = (char*)text.c_str();    // utf-8 string
    char* begin = str;			// begining of string
    char* end = str+strlen(str);      	// end iterator
    char* it = end;       		// string iterator
    
    int size = end-begin;
    if(size <= _keyLength){
      (*this)[text] = 1;
    }
    
    else{
      for(int i = 0; i < _keyLength; i++){
	it--;
	while(it[0] < -64){
	  it--;
	}
      }
      while(it >= begin){
	(*this)[it] += 1;
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
  
};
#endif