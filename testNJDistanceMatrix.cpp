#include <map>
#include "NgramVector.h"
#include "NJDistanceMatrix.h"

using namespace std;

int main()
{

  //test declaration and instantiation
  NJDistanceMatrix dist_matrix = NJDistanceMatrix();

  //create NGramVectors and DataSet to test matrix creation
  NgramVector vect1 = NgramVector("1", "1", "1", 1);
  NgramVector vect2 = NgramVector("2", "2", "2", 1);
  NgramVector vect3 = NgramVector("3", "3", "3", 1);
  NgramVector vect4 = NgramVector("4", "4", "4", 1);

  vect1["a"] = 1;
  vect1["b"] = 1;
  vect1["c"] = 1;

  vect2["d"] = 1;
  vect2["e"] = 1;
  vect2["f"] = 1;

  vect3["a"] = 1;
  vect3["b"] = 1;
  vect3["d"] = 1;

  vect4["a"] = 1;
  vect4["d"] = 1;
  vect4["e"] = 1;

  DataSet<NgramVector> data_set;
  data_set.push_back(vect1);
  data_set.push_back(vect2);
  data_set.push_back(vect3);
  data_set.push_back(vect4);

  dist_matrix.set_data(data_set);
  dist_matrix.print();
  dist_matrix.print_q_matrix();
  cout << endl;
  dist_matrix.combine_closest_pair();

  dist_matrix.print();
  dist_matrix.print_q_matrix();

  cout << endl;
  //check pair_is_valid()
  bool checking_PAIR_IS_VALID = false;
  if(checking_PAIR_IS_VALID)
  {
    //test pair_is_valid()
    cout << "Testing pair_is_valid()" << endl;
    cout << "the following should evaluate true:" << endl;
    
    cout << "pair(1,2): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "2"))<< endl;
    cout << "pair(1,3): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "3"))<< endl;
    cout << "pair(1,4): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "4"))<< endl;
    cout << "pair(2,3): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("2", "3"))<< endl;
    cout << "pair(2,4): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("2", "4"))<< endl;
    cout << "pair(3,4): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("3", "4"))<< endl;
    cout << "pair(3,1): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("3", "1"))<< endl;
    

    cout << "the following should evalute false:" << endl;
    cout << "pair(1,1): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "1"))<< endl;
    cout << "pair(1,5): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "5"))<< endl;
    cout << "pair(2,2): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("2", "2"))<< endl;
    cout << "pair(2,5): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("2", "5"))<< endl;
    cout << "pair(3,3): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("3", "3"))<< endl;
    cout << "pair(3,5): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("3", "5"))<< endl;
    cout << "pair(1,-1): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("1", "-1"))<< endl;
    cout << "pair(4,5): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("4", "5"))<< endl;
    cout << "pair(5,5): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("5", "5"))<< endl;
    cout << "pair(5,2): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("5", "2"))<< endl;
    cout << "pair(100000,100000): " << dist_matrix.pair_is_valid(NJDistanceMatrix::pair("100000", "100000"))<< endl;
    //end test pair_is_valid()
  }

  bool checking_GET_CLOSEST_PAIR = true;
  if(checking_GET_CLOSEST_PAIR)
  {
    //test get_closest_pair()
    cout << endl;
    cout << "Testing get_closest_pair()" << endl;
    dist_matrix.print_pair(dist_matrix.get_closest_pair());
    cout << endl;
    cout << endl;
  }

  bool checking_PAIRS_EQUAL = false;
  if(checking_PAIRS_EQUAL)
  {
    cout << "Testing pairs_equal()" << endl;
    cout << "should evaluate to true";
    cout << "pair(1,1) == pair(1,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "1"), NJDistanceMatrix::pair("1", "1"))<< endl;
    cout << "pair(1,2) == pair(1,2): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "2"), NJDistanceMatrix::pair("1", "2"))<< endl;
    cout << "pair(1,2) == pair(2,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "2"), NJDistanceMatrix::pair("2", "1"))<< endl;
    cout << "pair(2,1) == pair(2,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("2", "1"), NJDistanceMatrix::pair("2", "1"))<< endl;
    cout << "pair(2,1) == pair(1,2): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("2", "1"), NJDistanceMatrix::pair("1", "2"))<< endl;
    cout << "should evaluate to false";
    cout << "pair(1,2) == pair(1,3): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "2"), NJDistanceMatrix::pair("1", "3"))<< endl;
    cout << "pair(1,2) == pair(3,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "2"), NJDistanceMatrix::pair("3", "1"))<< endl;
    cout << "pair(2,1) == pair(1,3): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("2", "1"), NJDistanceMatrix::pair("1", "3"))<< endl;
    cout << "pair(2,1) == pair(3,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("2", "2"), NJDistanceMatrix::pair("3", "1"))<< endl;
    cout << "pair(1,3) == pair(1,2): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "3"), NJDistanceMatrix::pair("1", "2"))<< endl;
    cout << "pair(1,3) == pair(2,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("1", "3"), NJDistanceMatrix::pair("2", "1"))<< endl;
    cout << "pair(3,1) == pair(1,2): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("3", "1"), NJDistanceMatrix::pair("1", "2"))<< endl;
    cout << "pair(3,1) == pair(2,1): " << dist_matrix.pairs_equal(NJDistanceMatrix::pair("3", "1"), NJDistanceMatrix::pair("2", "1"))<< endl;
  }

  bool checking_ERASE_PAIR_FROM_ORDERED_DISTANCES = false;
  if(checking_ERASE_PAIR_FROM_ORDERED_DISTANCES)
  {
    cout << "Testing erase_pair_from_ordered_distances()" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "attemp remove 1" << endl;
    dist_matrix.remove_element("1");
    dist_matrix.print();
    dist_matrix.construct_q_matrix();
    dist_matrix.print_q_matrix();

    cout << "-------------------------------------------" << endl;
    cout << "attempt remove 1" << endl;
    dist_matrix.remove_element("1");
    dist_matrix.print();
    dist_matrix.construct_q_matrix();
    dist_matrix.print_q_matrix();

    cout << "-------------------------------------------" << endl;
    cout << "attempt remove 0" << endl;
    dist_matrix.remove_element("0");
    dist_matrix.print();
    dist_matrix.construct_q_matrix();
    dist_matrix.print_q_matrix();

    cout << "-------------------------------------------" << endl;
    cout << "attempt remove 2" << endl;
    dist_matrix.remove_element("2");
    dist_matrix.print();
    dist_matrix.construct_q_matrix();
    dist_matrix.print_q_matrix();

    cout << "-------------------------------------------" << endl;
    cout << "attempt remove 3" << endl;
    dist_matrix.remove_element("3");
    dist_matrix.print();
    dist_matrix.construct_q_matrix();
    dist_matrix.print_q_matrix();
  }

  bool testing_COMBINE_CLOSEST_PAIR = false;
  if(testing_COMBINE_CLOSEST_PAIR)
  {

  }
    
    
}