#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <cmath> // for floor()
#include <iostream> 

template <typename T>
class Heap {
 private:
  std::vector<T> values;
  void heapify(size_t);

 public:
  Heap();  // constructs an empty heap

  // constructs a heap with the values from the given vector
  // the type T MUST provide comparison operators <, >, ==
  Heap(std::vector<T>);

  std::vector<T> returnHeap(); 
  int findValueIndex(T value, int currIndex); 

  void insert(T);
  void remove(T);
  T getMin();
};

/*******************************/
// default constructor
/*******************************/

template <typename T>
Heap<T>::Heap() {}

/*******************************/
// constructs a heap with the values in the given vector
// the type T MUST provide comparison operators <, >, ==
/*******************************/

template <typename T>
Heap<T>::Heap(std::vector<T> start_values) {
  // copy the values into our heap vector
  for (size_t i = 0; i < start_values.size(); i++) {
    values.push_back(start_values.at(i));
  }

  // starting from last non-leaf node (last parent), heapify each
  // of the parents
  int initial_parent_index = floor((values.size()-1) / 2);
  for (int parent_index = initial_parent_index; parent_index >= 0;
       parent_index--) {
    heapify(parent_index);
  }
}

/*******************************/
// test function, returns heap values
/*******************************/

template <typename T>
std::vector<T> Heap<T>::returnHeap() {
    return values;
}

/*******************************/
// Find parent index function 
/*******************************/

int findParentIndex(int childIndex){
    return floor((childIndex-1)/2); 
}

/*******************************/
// add values to the heap
/*******************************/

template <typename T>
void Heap<T>::insert(T value) { 
    int currIndex = values.size()-1;
    int parentIndex = findParentIndex(currIndex);

    if(values.at(parentIndex) < value){
        values.push_back(value); 
        return; 
    }
    else if(values.at(parentIndex) > value){ 
        //pushback value and update currIndex 
        values.push_back(value); 
        int currIndex = values.size()-1;

        //if index isn't 0 and parent is larger than value, swap
        while(currIndex > 0 && values.at(findParentIndex(currIndex)) > value){
            T temp = values.at(findParentIndex(currIndex)); 
            values.at(findParentIndex(currIndex)) = value; 
            values.at(currIndex) = temp; 
            currIndex = findParentIndex(currIndex); 
        }
    }
    // if none of these satisfy, then print ERRO
    else std::cout << "ERROR" << std::endl; 

}

/*******************************/
/* find index of value         */
/*******************************/

template <typename T> 
int Heap<T>::findValueIndex(T value, int currIndex){
  //Recursive function to find index of a given value in a vector
    if(values.at(currIndex) == value)
        return currIndex; 
    else{
         return findValueIndex(value, currIndex-1); 
    }
    //if not found return -1
    return -1;  
}


/*******************************/
/* remove values from the heap */
/*******************************/

template <typename T>
void Heap<T>::remove(T value) {
    int valueIndex = findValueIndex(value, values.size()-1); 
    values.at(valueIndex) = values.at(values.size()-1); 
    values.pop_back(); 

    int initial_parent_index = floor((values.size()-1) / 2);
    for (int parent_index = initial_parent_index; parent_index >= 0;
        parent_index--){
        heapify(parent_index);
    }
}

/*******************************/
// find the smallest value in the heap
/*******************************/

template <typename T>
T Heap<T>::getMin() {
  return values.at(0); 
}

/*******************************/
// private function to heapify a given 'node'
/*******************************/

template <typename T>
void Heap<T>::heapify(size_t parent_index) {
  // if we're outside the index range, return
  if (parent_index < 0 || parent_index >= values.size()) return;

  // find children indexes
  size_t left_child_index = parent_index * 2 + 1;
  size_t right_child_index = parent_index * 2 + 2;

  // if parent is larger than child, swap with smallest child
  size_t index_of_smallest = parent_index;

  // check if left child exists and if exists, is smallest value there
  if (left_child_index < values.size() &&
      values.at(left_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = left_child_index;
  }

  // check if left child exists and if exists, is smallest value there
  if (right_child_index < values.size() &&
      values.at(right_child_index) < values.at(index_of_smallest)) {
    // make this index the current smallest
    index_of_smallest = right_child_index;
  }

  // if parent is not smallest, swap with smallest child
  if (index_of_smallest != parent_index) {
    T temp = values.at(parent_index);
    values.at(parent_index) = values.at(index_of_smallest);
    values.at(index_of_smallest) = temp;

    // heapify the swapped index - it may need to move
    // further down the 'tree'
    heapify(index_of_smallest);
  }
}

#endif