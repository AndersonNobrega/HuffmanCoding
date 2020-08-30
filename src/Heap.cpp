#include "Heap.hpp"
#include "Util.hpp"
#include <vector>

using namespace std;

Heap::Heap(int size) : _heapSize(0), _elementsArray(size) {};

int Heap::parent(int index) {
    return (index - 1) / 2;
}

int Heap::leftNode(int index) {
    return (2*index + 1);
}

int Heap::rightNode(int index) {
    return (2*index + 2);
}

int Heap::getSize() {
    return _heapSize;
}

Node* Heap::extractMin() { 
    if (_heapSize <= 0) 
        return nullptr; 
    if (_heapSize == 1) { 
        _heapSize--; 
        return _elementsArray[0]; 
    } 

    Node* root;

    root = _elementsArray[0]; 
    _elementsArray[0] = _elementsArray[_heapSize-1]; 
    _heapSize--; 

    minHeapify(0); 
  
    return root; 
} 

Node* Heap::getMin() {
    return _elementsArray[0];
}

void Heap::insertKey(Node* node) {
    int i;

    _heapSize++;
    i = _heapSize - 1;
    _elementsArray[i] = node;

    while (i != 0 && _elementsArray[parent(i)]->getNodeFrequency() > _elementsArray[i]->getNodeFrequency()){
        swap(_elementsArray[i], _elementsArray[parent(i)]); 
        i = parent(i);
    }

}

void Heap::decreaseKey(int index, Node* newNode) { 
    _elementsArray[index] = newNode; 

    while (index != 0 && _elementsArray[parent(index)]->getNodeFrequency() > _elementsArray[index]->getNodeFrequency()) { 
       swap(_elementsArray[index], _elementsArray[parent(index)]); 
       index = parent(index); 
    } 
} 

void Heap::deleteKey(int i) { 
    decreaseKey(i, nullptr); 
    extractMin(); 
} 

void Heap::buildHeap(int* values) {
    int i;
    int const n = 256;
    Node* temp;

    for(i = 0; i < n; i++) {
        temp = new Node(i, values[i], nullptr, nullptr);
        insertKey(temp);
    }
}
  
void Heap::minHeapify(int index) { 
    int left, right, smallest;

    left = leftNode(index); 
    right = rightNode(index); 
    smallest = index; 

    if (left < _heapSize && _elementsArray[left]->getNodeFrequency() < _elementsArray[index]->getNodeFrequency()) {
        smallest = left; 
    }
    if (right < _heapSize && _elementsArray[right]->getNodeFrequency() < _elementsArray[smallest]->getNodeFrequency()) {
        smallest = right; 
    }
    if (smallest != index) { 
        swap(_elementsArray[index], _elementsArray[smallest]); 
        minHeapify(smallest); 
    } 
} 