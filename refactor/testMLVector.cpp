#include <iostream>
#include <string>
#include "MLVector.h" 
using namespace std;

int main(){
  
  MLVector<string> t, u, v;
  
  t["a"] = 1;
  t["b"] = 1;
  t["c"] = 1;
  
  //u+=t;
  u["a"] = -1;
  u["b"] = -1;
  u["c"] = -1;
  
  v["f"] = 1;
  v["g"] = 1;
  v["h"] = 1;
  
  t.print("vector t");
  u.print("vector u");
  v.print("vector v");
  cout << "====================="<< endl;
  cout << "Cosine distance(t,t): " << t.cosine_distance(t) << endl;
  cout << "Cosine distance(t,u): " << t.cosine_distance(u) << endl;
  cout << "Cosine distance(t,v): " << t.cosine_distance(v) << endl;
  cout << "Cosine distance(u,v): " << v.cosine_distance(u) << endl;
  cout << "====================="<< endl;
  cout << "L0 distance(t,t): " << t.l0_distance(t) << endl;
  cout << "L0 distance(t,u): " << t.l0_distance(u) << endl;
  cout << "L0 distance(t,v): " << t.l0_distance(v) << endl;
  cout << "L0 distance(u,v): " << u.l0_distance(v) << endl;
  cout << "====================="<< endl;
  cout << "L1 distance(t,t): " << t.l1_distance(t) << endl;
  cout << "L1 distance(t,u): " << t.l1_distance(u) << endl;
  cout << "L1 distance(t,v): " << t.l1_distance(v) << endl;
  cout << "L1 distance(u,v): " << u.l1_distance(v) << endl;
  cout << "====================="<< endl;
  cout << "L2 distance(t,t): " << t.l2_distance(t) << endl;
  cout << "L2 distance(t,u): " << t.l2_distance(u) << endl;
  cout << "L2 distance(t,v): " << t.l2_distance(v) << endl;
  cout << "L2 distance(u,v): " << u.l2_distance(v) << endl;
  cout << "====================="<< endl;
  cout << "Linfinity distance(t,t): " << t.linfinity_distance(t) << endl;
  cout << "Linfinity distance(t,u): " << t.linfinity_distance(u) << endl;
  cout << "Linfinity distance(t,v): " << t.linfinity_distance(v) << endl;
  cout << "Linfinity distance(u,v): " << u.linfinity_distance(v) << endl;
  
  
  
  return 0;
}
