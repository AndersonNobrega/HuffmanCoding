#include "Node.hpp"

using namespace std;

Node::Node() {
    _nodeValue = -1;
    _nodeFrequency = -1;
    _leftNode = nullptr;
    _rightNode = nullptr;
}

Node::Node(int value, int frequency, Node* leftNode, Node* rightNode) {
    _nodeValue = value;
    _nodeFrequency = frequency;
    _leftNode = leftNode;
    _rightNode = rightNode;
}

int Node::getNodeValue() {
    return _nodeValue;
}

int Node::getNodeFrequency() {
    return _nodeFrequency;
}

Node* Node::getLeftNode() {
    return _leftNode;
}

Node* Node::getRightNode() {
    return _rightNode;
}

void Node::setNodeValue(int value) {
    _nodeValue = value;
}

void Node::setNodeFrequency(int frequency) {
    _nodeFrequency = frequency;
}

void Node::setLeftNode(Node* leftNode) {
    _leftNode = leftNode;
}

void Node::setRightNode(Node* rightNode) {
    _rightNode = rightNode;
}