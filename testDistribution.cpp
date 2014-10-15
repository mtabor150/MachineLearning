#include <string>
#include "Distribution.h" 
using namespace std; 

int main(){
  
  Distribution a,b,c;
  float a_ent, b_ent, c_ent;
  
  a.add_point("a", .5);
  a.add_point("b", .5);
  a_ent = a.entropy();	//should be 1
  
  b.add_point("a", .25);
  b.add_point("b", .25);
  b.add_point("c", .25);
  b.add_point("d", .25);
  b_ent = b.entropy();	//should be 2
  
  c.add_point("0", .1);
  c.add_point("1", .1);
  c.add_point("2", .1);
  c.add_point("3", .1);
  c.add_point("4", .1);
  c.add_point("5", .1);
  c.add_point("6", .1);
  c.add_point("7", .1);
  c.add_point("8", .1);
  c.add_point("9", .1);
  
  c_ent = c.entropy();	//should be 3.32193...
  
  
  cout << "Entropy of distribution with 2 equally probable sample points: " << a_ent << endl;
  cout << "Entropy of distribution with 4 equally probable sample points: " << b_ent << endl;
  cout << "Entropy of distribution with 10 equally probable sample points: " << c_ent << endl << endl;
  
  Distribution english("frequency_lists/English/english_monograms.fl");
  cout << "Entropy of English monograms: " << english.entropy() << endl << endl;
  
  Distribution french("frequency_lists/French/french_monograms.fl");
  cout << "Entropy of French monograms: " << french.entropy() << endl << endl;
  
  Distribution bavarian1("frequency_lists/Bavarian/bar-tweets-mono.fl");
  Distribution bavarian2("frequency_lists/Bavarian/bar-tweets-bi.fl");
  Distribution bavarian3("frequency_lists/Bavarian/bar-tweets-tri.fl");
  float b1_ent = bavarian1.entropy(), b2_ent = bavarian2.entropy(), b3_ent = bavarian3.entropy();
  cout << "Entropy of Bavarian monograms: " << b1_ent << endl;
  cout << "Entropy of Bavarian bigrams: " << b2_ent << endl;
  cout << "Entropy of Bavarian trigrams: " << b3_ent << endl << endl;
  
  Distribution haitian1("frequency_lists/Haitian/ht-tweets-mono.fl");
  Distribution haitian2("frequency_lists/Haitian/ht-tweets-bi.fl");
  Distribution haitian3("frequency_lists/Haitian/ht-tweets-tri.fl");
  float h1_ent = haitian1.entropy(), h2_ent = haitian2.entropy(), h3_ent = haitian3.entropy();
  cout << "Entropy of Haitian monograms: " << h1_ent << endl;
  cout << "Entropy of Haitian bigrams: " << h2_ent << endl;
  cout << "Entropy of Haitian trigrams: " << h3_ent << endl << endl;
  
}