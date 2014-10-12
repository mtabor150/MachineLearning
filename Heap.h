#ifndef HEAP_H
#define HEAP_H

/* Class to store a max heap/priority queue */

template <typename SortType, typename Data> 
class Heap {

  private:
    SortType* _values;			//pointer to underlying array to hold sortable data
    Data* _data;			//pointer to underlying array to hold associated data
    unsigned int _capacity, _size;	//max capacity and size of array

  public:

    /* Contructor: makes empty heap */
    Heap() : _values(new SortType[1]), _data(new Data[1]), _capacity(1), _size(0) {}
    
    /* Destructor */
    ~Heap() {
      delete[] _values;
      delete[] _data;
    }

    /*  Insert function: inserts into the heap
      input val: the value to be added
    */
    void insert(const SortType& val, const Data& data) {
      
      //check if size == capacity, expand if so
      if (_size == _capacity) {
	_capacity = _capacity*2;
	SortType* newsarray = new SortType[_capacity];
	Data* newvarray = new Data[_capacity];
	for (int i = 0; i < _size; i++){
	  newsarray[i] = _values[i];
	  newvarray[i] = _data[i];
	}
	delete[] _values;
	_values = newsarray;
	delete[] _data;
	_data = newvarray;
      }
      
      //insert the new value
      _values[_size] = val;
      _data[_size] = data;
      _size++;
      
      //"bubble-up" if not a heap
      int current = _size-1;
      int parent = (current-1)/2;
      
      //loop to bubble up
      while ((_values[current] > _values[parent]) && (current != 0)) {
	
	//swap current and parent
	SortType temp = _values[current];
	_values[current] = _values[parent];
	_values[parent] = temp;
	Data dtemp = _data[current];
	_data[current] = _data[parent];
	_data[parent] = dtemp;
	
	//update loop control variables
	current = parent;
	parent = (current-1)/2;
      }
      
    } //end insert

    /* removeMax: removes maximum value from the head */
    void pop() {
      if(_size != 0){
	//move last leaf up to root
	_values[0] = _values[_size-1];
	_data[0] = _data[_size-1];
	_size--;
	
	//need to "bubble" down
	int current = 0;
	int left = 1;
	int right = 2;
	SortType temp;
	Data dtemp;
	
	while (((left < _size) && (_values[current] < _values[left])) || (right < _size) && (_values[current] < _values[right])) {
	  
	  if (right >= _size) {
	    //swap with left
	    temp= _values[left];
	    _values[left] = _values[current];
	    _values[current] = temp;
	    dtemp= _data[left];
	    _data[left] = _data[current];
	    _data[current] = dtemp;
	    current = left;
	  }
	  else {
	    //find bigger child
	    if (_values[left] > _values[right]) {
	    //swap with left 
	    temp= _values[left];
	    _values[left] = _values[current];
	    _values[current] = temp;
	    dtemp= _data[left];
	    _data[left] = _data[current];
	    _data[current] = dtemp;
	    current = left;
	    }
	    else {
	      //swap with right
	      temp = _values[right];
	      _values[right] = _values[current];
	      _values[current] = temp;
	      dtemp= _data[right];
	    _data[right] = _data[current];
	    _data[current] = dtemp;
	      current = right;
	      
	    }
	  }
	  //update loop control variables
	  left = current*2 + 1;
	  right = left+1;
	  
	}
      }
    } //end removeMax

    
    /* getMaxValue: returns maximum value in heap 
    Note: returns const reference so that user cannot destroy heap property 
    */
    const SortType& top_value() const {
      return _values[0];
    }
    
    
    /* getMaxData: returns maximum data in heap 
    Note: returns const reference so that user cannot destroy heap property 
    */
    const Data& top_data() const {
      return _data[0];
    }

    
    /* size: returns current size of the heap */
    unsigned int size() const {
      return _size;
    }

    
    /* empty: returns true if the heap is empty, false otherwise */
    bool empty() const {
      return (_size == 0);
    }

    
    /* clear: empties heap of data */
    void clear() {
      _size = 0;
    }
};

#endif
