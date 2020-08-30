#include "Huffman.hpp"
#include "Util.hpp"
#include "string"
#include <vector>
#include <unordered_map>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

using namespace std;

Huffman::Huffman(int size) : _minHeap(size) {
    _tree = new vector<unsigned char>;
};

void Huffman::compressImage(cv::Mat imgMatrix, string filePath) {
    int i;
    int const n = 256;
    int valuesFrequencies[n];
    int codes[n];
    string bits = "";
    unordered_map<int, string>* huffmanCodes = new unordered_map<int, string>;

    for(i = 0; i < n; i++) {
        valuesFrequencies[i] = 0;
    }

    countFrequencies(imgMatrix, valuesFrequencies);

    _minHeap.buildHeap(valuesFrequencies);

    while(_minHeap.getSize() > 1) {
        Node* node = new Node();
        Node* temp_x = _minHeap.extractMin();
        Node* temp_y = _minHeap.extractMin();

        node->setNodeValue(-1);
        if(temp_x->getNodeFrequency() > temp_y->getNodeFrequency()) {
            node->setLeftNode(temp_y);
            node->setRightNode(temp_x);
        } else {
            node->setLeftNode(temp_x);
            node->setRightNode(temp_y);
        }
        node->setNodeFrequency(temp_x->getNodeFrequency() + temp_y->getNodeFrequency());
        _minHeap.insertKey(node);
    }

    createCode(_minHeap.extractMin(), bits, huffmanCodes);
    saveFile(imgMatrix, huffmanCodes, filePath);
}

void Huffman::createCode(Node* root, string bits, unordered_map<int, string>* huffmanCodes) {
    if(root->getLeftNode() == nullptr && root->getRightNode() == nullptr) {
        _tree->push_back('0');
        _tree->push_back(root->getNodeValue());
        huffmanCodes->insert(pair<int, string>(root->getNodeValue(), bits));
    } else {
        _tree->push_back('1');
        createCode(root->getLeftNode(), bits + "0", huffmanCodes);
        createCode(root->getRightNode(), bits + "1", huffmanCodes);
    }
}

void Huffman::saveFile(cv::Mat imgMatrix, unordered_map<int, string>* huffmanCodes, string filePath) {
    int i, j, bitStreamLength, index = 0, bitCount = 0, byteLenght;
    unsigned short height, width;
    string bitStream;
    unsigned char* bitArray;
    unsigned char* treeArray;
    ofstream outputFile(filePath, ios::out | ios::binary);

    height = imgMatrix.rows;
    width = imgMatrix.cols;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            bitStream += huffmanCodes->at((int) imgMatrix.at<uchar>(i, j));
        }
    }

    /*
    byteLenght = (_tree->size()/8) + 1;
    treeArray = (unsigned char*) malloc(byteLenght * sizeof(unsigned char));
    memset(treeArray, 0, byteLenght);
    bitCount = 0;
    index = 0;

    for (i = 0; i < _tree->size(); i++) {
        treeArray[index] = (treeArray[index] << 1) | ((int)(_tree->at(i) - '0'));
        bitCount++;
        if (bitCount == 8) {
            bitCount = 0;
            index++;
        }
    }*/

    outputFile.write((char*)&height, sizeof(height));
    outputFile.write((char*)&width, sizeof(width));

    /*
    for (i = 0; i < index; i++) {
        outputFile << (treeArray[i]);
    }*/

    bitStreamLength = bitStream.size();
    byteLenght = (bitStreamLength/8) + 1;
    bitArray = (unsigned char*) malloc(byteLenght * sizeof(unsigned char));
    memset(bitArray, 0, byteLenght);

    for (i = 0; i < bitStreamLength; i++) {
        bitArray[index] = (bitArray[index] << 1) | ((int)(bitStream[i] - '0'));
        bitCount++;
        if (bitCount == 8) {
            bitCount = 0;
            index++;
        }
    }

    for (i = 0; i < index; i++) {
        outputFile << (bitArray[i]);
    }

    outputFile.close();
}

int Huffman::readBinaryData(string filePath, string imageExtension) { 
    unsigned char* hexValues;
    unsigned char buffer[1];
    unsigned char tempHeight[2];
    unsigned char tempWidth[2];
    FILE* compressedFile;
    int fSize, i, j, value;
    int const HEADERCONT = 4;
    int height = 0, width = 0;
    string sequence = "", treeSequence = "";

    compressedFile = fopen(filePath.c_str(), "rb");

    if (compressedFile == nullptr) {
        cout << "Failed to open file" << endl;
        return EXIT_FAILURE;
    }
    
    fSize = fileSize(compressedFile) - HEADERCONT;

    hexValues = (unsigned char*) malloc(fSize*sizeof(unsigned char));

    i = 0;
    while(fread(buffer, 1, 1, compressedFile) == 1) {
        if(i < HEADERCONT) {
            if(i < 2) {
                tempHeight[i] = buffer[0]; 
            } else {
                tempWidth[i - 2] = buffer[0];
            }
        } else {
            hexValues[i - HEADERCONT] = buffer[0];
        }
        i++;
    }

    height = (int) ((tempHeight[0]) | tempHeight[1] << 8);
    width = (int) ((tempWidth[0]) | tempWidth[1] << 8);

    fclose(compressedFile);

    for(i = 0; i < fSize; i++) {
        value = hexValues[i];
        sequence += decimalToBinary(value);
    }

    reconstructImage(_minHeap.getMin(), sequence, width, height, filePath, imageExtension);

    //separateTree(hexValues, fSize*8, &sequence, &treeSequence);
    //Node* root = reconstructTree(treeSequence);
    //reconstructImage(root, sequence, width, height);
} 

void Huffman::separateTree(unsigned char* hexValues, int size, string* sequence, string* treeSequence) {
    int i = 0, quantUm = 0, quantZero = 0, num;

    for(i = 0; i < size/8; i++) {
        num = hexValues[i];
        *sequence += decimalToBinary(num);
    }

    i = 0;

    while (i < sequence->size()) {
        if(sequence->at(i) == '0') {
            *treeSequence += sequence->substr(i, 9);
            i += 9;
            quantZero++;
        } else if (sequence->at(i) == '1') {
            *treeSequence += sequence->at(i);
            i++;
            quantUm++;
        }

        if(i >= 94*8) {
            break;
        }
    }

    *sequence = sequence->substr(95*8, size-i);
}


Node* Huffman::reconstructTree(string treeSequence) {
    int index = 0;
    Node* root;
    queue<Node*> toBuild;

    toBuild.push(root);

    while(!toBuild.empty() && index < treeSequence.size()){
        Node* node = toBuild.front();

        toBuild.pop();

        if (treeSequence[index] == '1') {
            Node* temp = new Node();
            node->setLeftNode(temp);
            toBuild.push(node->getLeftNode());
            index++;
        } else {
            node->setNodeValue(binaryToDecimal(treeSequence.substr(index+1, 8)));
            index += 9;
        }

        if(treeSequence.size() < index) {
            break;
        }

        if(treeSequence[index] == '1'){
            Node* temp = new Node();
            node->setRightNode(temp);
            toBuild.push(node->getRightNode());
            index++;
        } else {
            node->setNodeValue(binaryToDecimal(treeSequence.substr(index+1, 8)));
            index += 9;
        }
    }

    return root;
}

void Huffman::reconstructImage(Node* root, string sequence, int width, int height, string filePath, string extension) {
    int** imageMatrix;
    int i, j, heightIndex = 0, widthIndex = 0, extensionIndex;
    string imageFilePath;

    Node* current = root;

    imageMatrix = (int**) malloc(height*sizeof(int*));

    for(i = 0; i < height; i++) {
        imageMatrix[i] = (int*) malloc(width*sizeof(int));
    }

    for(i = 0; i < sequence.size(); i++) {
        if(sequence.at(i) == '0') {
            current = current->getLeftNode();
        } else {
            current = current->getRightNode();
        }

        if(current->getLeftNode() == nullptr && current->getRightNode() == nullptr) {
            imageMatrix[heightIndex][widthIndex] = current->getNodeValue();
            current = root;

            widthIndex++;
            if(widthIndex >= width) {
                widthIndex = 0;
                heightIndex++;
            }

            if(heightIndex >= height) {
                break;
            }
        }
    }

    extensionIndex = filePath.find_last_of(".");
    imageFilePath = filePath.replace(extensionIndex, filePath.substr(filePath.find_last_of(".")).length(), "Decompressed." + extension);

    cv::Mat imageDecompressed(height, width, CV_8U);

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            imageDecompressed.at<uchar>(i, j) = imageMatrix[i][j];
        }
    } 

    cv::imwrite(imageFilePath, imageDecompressed); 
  
}