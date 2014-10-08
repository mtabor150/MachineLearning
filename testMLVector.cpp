#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include "MLVector.h"
using namespace std;

void check_distance(const MLVector<string>& first, const MLVector<string>& other, double expected_val, dist_type type)
{
  double dist = ((MLVector<string>)first).distance(other, type);
  if(dist != expected_val )
  {
    cout << "expected: " << expected_val << " actual: " << dist << " difference: " << expected_val-dist << endl;
  }
}

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

  /* test cosine_distance() */
  //cos_dist to self
  check_distance(t,t,0,COS_DIST);

  //cos_dist from t to u
  check_distance(t,u,2,COS_DIST);

  //cos_dist from t to v
  check_distance(t,v,1,COS_DIST);
  
  //cos_dist from u to v
  check_distance(u,v,1,COS_DIST);
  /* end test cosine_distance() */


  /* test l0_distance() */
  //l0_dist to self
  check_distance(t,t,0,L0_DIST);

  //l0_dist from t to u
  check_distance(t,u,6,L0_DIST);

  //l0_dist from t to v
  check_distance(t,v,0,L0_DIST);
  
  //l0_dist from u to v
  check_distance(u,v,0,L0_DIST);
  /* end test l0_distance() */


  /* test l1_distance() */
  //l1_dist to self
  check_distance(t,t,0,L1_DIST);

  //l1_dist from t to u
  check_distance(t,u,6,L1_DIST);

  //l1_dist from t to v
  check_distance(t,v,6,L1_DIST);
  
  //;1_dist from u to v
  check_distance(u,v,6,L1_DIST);
  /* end test l1_distance() */


  /* test l2_distance() */
  //l2_dist to self
  check_distance(t,t,0,L2_DIST);

  //l2_dist from t to u
  check_distance(t,u,3.4641,L2_DIST);

  //l2_dist from t to v
  check_distance(t,v,2.44949,L2_DIST);
  
  //l2_dist from u to v
  check_distance(u,v,2.44949,L2_DIST);
  /* end test l2_distance() */


  /* test linfinity_distance() */
  //linf_dist to self
  check_distance(t,t,0,LINF_DIST);

  //linf_dist from t to u
  check_distance(t,u,2,LINF_DIST);

  //linf_dist from t to v
  check_distance(t,v,1,LINF_DIST);
  
  //linf_dist from u to v
  check_distance(u,v,1,LINF_DIST);
  /* end test linfinity_distance() */
  
  return 0;
}
