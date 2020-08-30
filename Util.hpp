#ifndef AUX_HEADER
#define AUX_HEADER
#include <opencv2/opencv.hpp>
#include "Node.hpp"
#include "string"

void countFrequencies(cv::Mat imgMatrix, int* frequenciesArray);
void swap(Node* x, Node* y);
int fileSize(FILE* file);
std::string decimalToBinary(int n);
int binaryToDecimal(std::string n);
#endif