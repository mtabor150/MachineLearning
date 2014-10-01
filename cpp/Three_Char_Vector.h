/* 
 * copyright 2014, Phillip Martin
 * Three_Char_Vector will provide a datastructure and implementations for
 * three character language vector comparisons
 */

//only declare contents of file if it has not been declared yet
#ifndef TCV
#define TCV

#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <math.h>
#include <fstream>
using namespace std;

/*---------------------------------------------------------
three_char_dict is a struct that will contain a vector 
which will record all of the three character
occurences from that particular user.
---------------------------------------------------------*/
typedef unordered_map<string, double> dictionary;

struct three_char_vector
{
	dictionary dict;
	dictionary::iterator iter;
};

//returns whether a particular key exists in a vector
bool key_exists(three_char_vector vect, string key);

//adds the three char count of the text to an existing vector
void three_char_count_with_vector(string text, three_char_vector *vect);

//adds the three char count of the text to the vector
three_char_vector three_char_count(string text);

//adds two vectors together and returns the value
three_char_vector add_dict(three_char_vector * vect1, three_char_vector * vect2);

//gets angle between two vectors
double VAngle(three_char_vector * vect1, three_char_vector * vect2);

three_char_vector unit_vector(three_char_vector *vect);

bool three_char_vector_equal(three_char_vector *vect1, three_char_vector *vect2);

void print_vector(three_char_vector *vect);

#endif