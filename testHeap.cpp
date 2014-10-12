#include "Heap.h"
#include <iostream>
using namespace std;

int main() {

  Heap<float,string> myheap;
  
  myheap.insert(11.2, "abc");
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;
  
  myheap.insert(13.6, "bcd");
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;
 
  myheap.insert(9.9, "cde");
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;
  
  myheap.insert(17.1, "def");
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;
  
  myheap.removeMax();
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;

  myheap.removeMax();
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;
  
  myheap.removeMax();
  cout << "max priority is " << myheap.getMaxValue() << " Data: " << myheap.getMaxData() << endl;

} 
