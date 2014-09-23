/* 
 * copyright 2014, Phillip Martin
 * Three_Char_Vector will provide a datastructure and implementations for
 * three character language vector comparisons
 */

#include <iostream>
#include <map>
#include <string>
#include <cmath>
#include <math.h>
#include <fstream>
using namespace std;

#define EPS pow(10,-8)

/*---------------------------------------------------------
three_char_dict is a struct that will contain a vector 
which will record all of the three character
occurences from that particular user.
---------------------------------------------------------*/
struct three_char_vector
{
	map<string, int> dict;
	map<string, int>::iterator iter;
};

//returns whether a particular key exists in a vector
bool key_exists(three_char_vector vect, string key)
{
	return vect.dict.count(key);
}

//adds the three char count of the text to an existing vector
void three_char_count_with_vector(string text, struct three_char_vector * vect)
{
	//iterate through text and count three char sequences
	map<string, int> ret_dict = vect->dict;
	int dictionarySize = text.length()-2;
	string str;
	for(int i = 0; i<dictionarySize; i++)
	 {
	 	if(i%100000 == 0)
	 	{
	 		//cout << i << endl;
	 	}
	    str = text.substr(i, 3);
		if(ret_dict.count(str))
		{
			ret_dict[str] = ret_dict[str]+1;
		}
		else
		{
			ret_dict[str] = 1;
		}
	}
	vect->dict = ret_dict;
}

//adds the three char count of the text to the vector
three_char_vector three_char_count(string text)
{
	//iterate through text and count three char sequences
	struct three_char_vector ret_vect;
	three_char_count_with_vector(text, &ret_vect);
	return ret_vect;
}



//adds vector 2 to vector 1
three_char_vector add_dict(struct three_char_vector *vect1, struct three_char_vector *vect2)
{
	//cout << "a" << endl;
	//loop through vector 1 adding each key-value pair to return dict
	map<string, int> ret_dict = vect1->dict;
	map<string, int> add_dict = vect2->dict;
	string key;
	int val1;
	map<string, int>::iterator iter;
	//loop through vector 2 adding each key-value pair to return dict
	for(iter = add_dict.begin();
		iter != add_dict.end(); ++iter)
	{
		//cout << "b" <<endl;
		key = iter->first;
		val1 = iter->second;
		if(ret_dict.count(key))
		{
			ret_dict[key] += val1;
		}
		else
		{
			ret_dict[key] = val1;
		}
	}
	vect1->dict = ret_dict;
	return *vect1;
}

//gets angle between two vectors
double VAngle(three_char_vector vect1, three_char_vector vect2)
{
	double mag_1 = 0.0;
	double dot_product = 0.0;

	//magnitude of vector a should equal the square root of 
	//the sum of the squares of each component.
	//the dot product is the sum of the product of any components
	//the two vectors have in common.
	map<string, int> dict1 = vect1.dict;
	map<string, int> dict2 = vect2.dict;
	string key;
	double val1;
	//int i =0;
	map<string, int>::iterator iter;
	for(iter = dict1.begin(); 
		iter != dict1.end(); iter++) 
	{
		//cout << i++ << endl;
		key = iter->first;
		val1 = iter->second;
		mag_1 = mag_1 + val1*val1;

		//add to dot product if key exists in both vectors
		if(dict2.count(key))
		{
			dot_product = dot_product + dict2[key]*val1;
		}
	}
	mag_1 = sqrt(mag_1);

	double mag_2 = 0;
	double val2;
	//only need to calculate the magnitude of vector2
	for(iter = dict2.begin(); 
		iter != dict2.end(); iter++) 
	{
		key = iter->first;
		val2 = iter->second;

		mag_2 = mag_2 + val2*val2;
	}
	mag_2 = sqrt(mag_2);

	double angle;
	if(mag_1>0 && mag_2 > 0)
	{
		double tempAngle;
		angle = dot_product/(mag_1*mag_2);
		if(abs(angle - 1.0) < EPS && abs(angle-1.0) > 0.0)
		{
			angle = 0.0;
		}
		else
		{
			tempAngle = angle;
			angle = acos(angle)*180/M_PI;
			if(angle != angle)
			{
				cout << " tAng: " << tempAngle << " ";
			}
		}
		return angle;
	}
	else
	{
		return -1.0;
	}
}

void print_vector(three_char_vector vect)
{
	for(vect.iter = vect.dict.begin(); 
		vect.iter != vect.dict.end(); vect.iter++) 
	{
		string key = vect.iter->first;
		double val2 = vect.iter->second;

		cout << key << " : " << val2 << endl;
	}
}