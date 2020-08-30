#include "Util.hpp"
#include "string"

using namespace std;

void countFrequencies(cv::Mat imgMatrix, int* frequenciesArray) {
    unsigned short i, j, height, width;

    width = imgMatrix.cols;
    height = imgMatrix.rows;

    for(i = 0; i < height; i++) {
        for(j = 0; j < width; j++) {
            frequenciesArray[(int) imgMatrix.at<uchar>(i, j)]++;
        }
    }
}

void swap(Node* x, Node* y) { 
    Node temp;
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 

int fileSize(FILE* file) {
    int size;
    
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    rewind(file);

    return size;
}

string decimalToBinary(int n) { 
    int k;
    string binarySequence = "";

    for (int i = 7; i >= 0; i--) { 
        k = n >> i; 
        if (k & 1) 
            binarySequence += "1"; 
        else
            binarySequence += "0";  
    } 

    return binarySequence;
} 

int binaryToDecimal(string n) { 
    string num = n; 
    int decValue = 0, base = 1, len = num.size(), i; 
  
    for (i = len - 1; i >= 0; i--) { 
        if (num.at(i) == '1') 
            decValue += base; 
        base = base * 2; 
    } 
  
    return decValue; 
} 