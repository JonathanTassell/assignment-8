#include "Heap.tpp"

int main(){
    std::vector<int> nums = {3, 2, 5, 6, 7, 9, 11};  

    Heap<int> heap(nums); 

    
    heap.remove(5); 
    std::vector<int> heapValues = heap.returnHeap(); 
    
    for(size_t i=0; i<heapValues.size(); i++){
        std::cout << heapValues.at(i) << std::endl; 
    }
}