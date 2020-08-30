#ifndef HEAP_HEADER
#define HEAP_HEADER
#include "Node.hpp"
#include <vector>

class Heap {
    private:
        std::vector<Node*> _elementsArray;
        int _maxSize;
        int _heapSize;
    public:
        Heap(int size);
        void buildHeap(int* values);
        void minHeapify(int index);
        int parent(int index);
        int leftNode(int index);
        int rightNode(int index);
        int getSize();
        Node* extractMin();
        Node* getMin();
        void decreaseKey(int index, Node* newNode);
        void deleteKey(int index);
        void insertKey(Node* node);
};
#endif