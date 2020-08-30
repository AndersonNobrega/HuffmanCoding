#include <opencv2/opencv.hpp>
#include "Huffman.hpp"
#include <string>

using namespace std;

int main(int argc, char** argv ) {
    string filePath = argv[1], filePathCompressed, imageExtension;
    int* values;
    int const n = 512;
    int extensionIndex;

    cv::Mat image;
    image = cv::imread(filePath, cv::IMREAD_GRAYSCALE);

    extensionIndex = filePath.find_last_of(".") + 1;
    imageExtension = filePath.substr(filePath.find_last_of(".") + 1);
    filePathCompressed = filePath.replace(extensionIndex, filePath.substr(filePath.find_last_of(".") + 1).length(), "wic");

    Huffman huff(n);
    huff.compressImage(image, filePathCompressed);
    huff.readBinaryData(filePathCompressed, imageExtension);
}