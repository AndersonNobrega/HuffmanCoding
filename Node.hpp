#ifndef NODE_HEADER
#define NODE_HEADER

class Node {
    private:
        int _nodeValue;
        int _nodeFrequency;
        Node* _leftNode;
        Node* _rightNode;
    public:
        Node();
        Node(int value, int frequency, Node* leftNode, Node* rightNode);
        int getNodeValue();
        int getNodeFrequency();
        Node* getLeftNode();
        Node* getRightNode();
        void setNodeValue(int value);
        void setNodeFrequency(int frequency);
        void setLeftNode(Node* leftNode);
        void setRightNode(Node* rightNode);
};
#endif