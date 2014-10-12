#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

using namespace std;


template < class Key,                                    // unordered_map::key_type
           class T = float,                              // unordered_map::mapped_type
           class Hash = hash<Key>,                       // unordered_map::hasher
           class Pred = equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
           > 

           
class Distribution: public unordered_map<Key, T, Hash, Pred, Alloc>{

public:
  
  
  
  
}

#endif
