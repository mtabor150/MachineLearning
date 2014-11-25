#include <string>
#include "Distribution.h" 
using namespace std; 

int main(){
  
  Distribution a,b,c;
  float a_ent, b_ent, c_ent;
  NgramVector m_a("1", "a", "", 1);
  NgramVector m_b("2", "b", "", 1);
  NgramVector m_c("3", "c", "", 1);
  
  //two equally probable values
  m_a["a"] = 1.0;
  m_a["b"] = 1.0;
  a.dist_from_mlvector(m_a);
  a_ent = a.entropy();	//should be 1
  
  //four equally probable values
  m_b["a"]= 1.0;
  m_b["b"]= 1.0;
  m_b["c"]= 1.0;
  m_b["d"]= 1.0;
  b.dist_from_mlvector(m_b);
  b_ent = b.entropy();	//should be 2
  
  //ten equally probably values
  m_c["0"]= 1.0;
  m_c["1"]= 1.0;
  m_c["2"]= 1.0;
  m_c["3"]= 1.0;
  m_c["4"]= 1.0;
  m_c["5"]= 1.0;
  m_c["6"]= 1.0;
  m_c["7"]= 1.0;
  m_c["8"]= 1.0;
  m_c["9"]= 1.0;
  c.dist_from_mlvector(m_c);
  c_ent = c.entropy();	//should be 3.32193...
  
  
  DataSet<NgramVector> data_set;
  data_set.push_back(m_a);
  data_set.push_back(m_b);
  data_set.push_back(m_c);
  
  Distribution author_distribution;
  author_distribution.dist_from_authors_dataset(data_set);
  cout << "Entropy of authors distribution is: " << author_distribution.entropy() << endl;
  Distribution author_distribution_conditional_on_a;
  string a_str = "a";
  author_distribution_conditional_on_a.conditional_dist_from_authors_dataset(data_set, a_str);
  cout << "Entropy of conditional authors distribution: " << author_distribution_conditional_on_a.entropy() << endl;
  
  
  cout << "Entropy of distribution with 2 equally probable sample points: " << a_ent << endl;
  cout << "Entropy of distribution with 4 equally probable sample points: " << b_ent << endl;
  cout << "Entropy of distribution with 10 equally probable sample points: " << c_ent << endl << endl;
  
  Distribution english;
  english.dist_from_mlvector_file("frequency_lists/English/english_monograms.fl");
  cout << "Entropy of English monograms: " << english.entropy() << endl << endl;
  
  Distribution french;
  french.dist_from_mlvector_file("frequency_lists/French/french_monograms.fl");
  cout << "Entropy of French monograms: " << french.entropy() << endl << endl;
  
  Distribution bavarian1;
  bavarian1.dist_from_mlvector_file("frequency_lists/Bavarian/bar-tweets-mono.fl");
  Distribution bavarian2;
  bavarian2.dist_from_mlvector_file("frequency_lists/Bavarian/bar-tweets-bi.fl");
  Distribution bavarian3;
  bavarian3.dist_from_mlvector_file("frequency_lists/Bavarian/bar-tweets-tri.fl");
  
  
  float b1_ent = bavarian1.entropy(), b2_ent = bavarian2.entropy(), b3_ent = bavarian3.entropy();
  cout << "Entropy of Bavarian monograms: " << b1_ent << endl;
  cout << "Entropy of Bavarian bigrams: " << b2_ent << endl;
  cout << "Entropy of Bavarian trigrams: " << b3_ent << endl << endl;
  
  Distribution haitian1;
  haitian1.dist_from_mlvector_file("frequency_lists/Haitian/ht-tweets-mono.fl");
  Distribution haitian2;
  haitian2.dist_from_mlvector_file("frequency_lists/Haitian/ht-tweets-bi.fl");
  Distribution haitian3;
  haitian3.dist_from_mlvector_file("frequency_lists/Haitian/ht-tweets-tri.fl");
  float h1_ent = haitian1.entropy(), h2_ent = haitian2.entropy(), h3_ent = haitian3.entropy();
  cout << "Entropy of Haitian monograms: " << h1_ent << endl;
  cout << "Entropy of Haitian bigrams: " << h2_ent << endl;
  cout << "Entropy of Haitian trigrams: " << h3_ent << endl << endl;
  
}