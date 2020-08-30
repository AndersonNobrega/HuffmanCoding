#ifndef HUFF_HEADER
#define HUFF_HEADER
#include "Heap.hpp"
#include "Node.hpp"
#include <unordered_map>
#include <opencv2/opencv.hpp>

class Huffman {
    private:
        Heap _minHeap;
        std::vector<unsigned char>* _tree;
    public:
        Huffman(int size);
        void compressImage(cv::Mat imgMatrix, std::string filePath);
        void createCode(Node* root, std::string bits, std::unordered_map<int, std::string>* huffmanCodes);
        void saveFile(cv::Mat imgMatrix, std::unordered_map<int, std::string>* huffmanCodes, std::string filePath);
        int readBinaryData(std::string filePath, std::string imageExtension);
        void separateTree(unsigned char* hexValues, int size, std::string* sequence, std::string* treeSequence);
        Node* reconstructTree(std::string treeSequence);
        void reconstructImage(Node* root, std::string sequence, int width, int height, std::string filePath, std::string extension);
};
#endif