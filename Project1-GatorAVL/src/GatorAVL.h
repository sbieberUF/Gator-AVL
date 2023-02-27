#pragma once 
#include <iostream>
#include <vector>
#include <queue> 
using namespace std; 


struct Node {
    string name;
    string ufid;
    Node* right;
    Node* left;
    int height;
    int balanceFactor;
    Node() : name(""), ufid(""), left(nullptr), right(nullptr) {}
};

class AVLTree {
    private:
    Node* insertHelper(Node* node, string name, string ufid);
    
    int height(Node* node);
    Node* balanceTree(Node* node);
    int balanceFactor(Node* node);
    Node* leftRotation(Node* node);
    Node* rightRotation(Node* node);

    void printInorder(Node* node, bool& firstInList);
    void printPreorder(Node* node, bool& firstInList);
    void printPostorder(Node* node, bool& firstInList);

    Node* findParent(string ufid);

    public:
       Node* root;

       Node* searchID(string ufid);

       vector<string> searchName(string name);

       void printTreeInorder();

       void printTreePreorder();

       void printTreePostorder();

       void printLevelCount();

       void removeID(string ufid);

       void removeInorderN(string N);

        void insert(string name, string ufid) 
        { 
            this->root = insertHelper(this->root, name, ufid);
        }
        
        AVLTree() : root() {}
};

Node* AVLTree::insertHelper(Node* node, string name, string ufid) {
    //Base case 
    if (node == nullptr) {
        node = new Node();
        node->name = name;
        node->ufid = ufid;
        return node; 
    }
    
    if (ufid < node->ufid) {
            node->left = insertHelper(node->left, name, ufid);
        }
    else if(ufid > node->ufid) {
            node->right = insertHelper(node->right, name, ufid);
        }
    else {
            node->name = name;
            return node;
        }
    
        node->height = max(height(node->left), height(node->right)) + 1;

        node = balanceTree(node);

        return node; 
}

int AVLTree::height(Node* node) {

    if (node == nullptr) {
        return 0;
    }
    else {
        return 1 + max(height(node->left), height(node->right));
    }
}

int AVLTree::balanceFactor(Node* node) {
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    int bf = leftHeight - rightHeight;
    return bf; 
}

Node* AVLTree::leftRotation(Node* node) { //From Balanced Trees PPT slides 
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    return newParent; 
}

Node* AVLTree::rightRotation(Node* node) { 
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    return newParent; 
}

Node* AVLTree::balanceTree(Node* node) {
    int bf = balanceFactor(node); //Calculate balance factor

    
    if (bf > 1) { //If balance factor is > 1, left subtree is taller than right subtree
        
        if(balanceFactor(node->left) < 0) { //If the balance factor of the left child < 0, perform left-right rotation
            node->left = leftRotation(node->left);
        }
        node = rightRotation(node); //Right rotation
    }
    else if (bf < -1) { //If balance factor is < -1, the right subtree is taller than the left subtree
        if(balanceFactor(node->right) > 0) { //If balance factor of right child is > 0, perform right-left rotation
            node->right = rightRotation(node->right); 
        }
        node = leftRotation(node); //Left rotation
    }

    node->height = max(height(node->left), height(node->right)) + 1; //Updates height of nodes in subtree

    return node; 

}

Node* AVLTree::searchID(string ufid) {
    Node* node = root;
    while(node != nullptr) {
        if (ufid == node->ufid) {
            return node;
        }
        else if(ufid < node->ufid) {
            node = node->left;
        }
        else {
            node = node->right;
        }
    }

    return nullptr; // ufid not found, returns null
}


vector<string> AVLTree::searchName(string name) {
    vector<string> coresspondingIDs;
    
     if (root == nullptr) {
         return coresspondingIDs;
     }

    queue<Node*> myQueue;
 
    myQueue.push(root);

    while(!myQueue.empty()) {
       Node* node = myQueue.front();
       myQueue.pop();

        if(node->name == name) { // if there is one name tied to multiple IDs, prints in preorder traversal 
            coresspondingIDs.push_back(node->ufid);
        }

        if (node->left != nullptr) {
            myQueue.push(node->left);
        }

        if (node->right != nullptr) {
            myQueue.push(node->right);
        }
    }

    return coresspondingIDs; 
}

void AVLTree::printInorder(Node* node, bool& firstInList) { //some from trees PPT
//firstInList variable being used to keep track of whether the current name being printed is the first name
//in the list or not. If first in the list, comma will not be printed before it.

    if (node == nullptr) {
        return;
    }

    printInorder(node->left, firstInList);

    if(firstInList) { //first item in list passes this if statement, thus comma is skipped from printing before it 
        cout << node->name;
        firstInList = false; 
    }
    else {
        cout << ", " << node->name;
    }

    printInorder(node->right, firstInList);
}

void AVLTree::printTreeInorder() { //prints out a comma separated inorder traversal of the names in the tree.
    bool isFirst = true; 
    printInorder(root, isFirst); 
    
}

void AVLTree::printPreorder(Node* node, bool& firstInList) { //pseudocode from trees PPT
   if (node == nullptr) {
        return;
    }

    if (firstInList) { //first item in list passes this if statement, thus comma is skipped from printing before it 
        cout << node->name;
        firstInList = false; 
    }
    else {
        cout << ", " << node->name; 
    }

    printPreorder(node->left, firstInList);
    printPreorder(node->right, firstInList);
}

void AVLTree::printTreePreorder() { //prints out a comma separated preorder traversal of the names in the tree.
    bool firstInList = true; 
    printPreorder(root, firstInList);
}

void AVLTree::printPostorder(Node* node, bool& firstInList) { //pseudocode from trees PPT
    if (node == nullptr) {
        return;
    }
    
    printPostorder(node->left, firstInList);
    printPostorder(node->right, firstInList);

    if (firstInList) { //first item in list passes this if statement, thus comma is skipped from printing before it 
        cout << node->name;
        firstInList = false;
    }
    else {
        cout << ", " << node->name; 
    }
}

void AVLTree::printTreePostorder() { //prints out a comma separated postorder traversal of the names in the tree.
    bool firstInList = true;
    printPostorder(root, firstInList);
}

void AVLTree::printLevelCount() {
     int treeHeight = height(root);
     if(height(root) == 0) { //prints 0 if the head of the tree is null
        cout << "0" << endl; 
     }
     else {
        cout << treeHeight << endl;
     }
}

void AVLTree::removeID(string ufid) {
    Node* node = searchID(ufid); // Find node to remove
    Node* parent = findParent(ufid); // Finds parent node of node to remove 
    
    if (searchID(ufid) == nullptr) {
        cout << "unsuccessful" << endl;
        return; 
    }
   
    //1st Case : Node is leaf node (no kids) // some from balanced trees PPT 
    if(node->left == nullptr && node->right == nullptr) {
        if(parent == nullptr) { //parent = null means there is no parent, so the node must be the root node
            root == nullptr; //sets root to null to delete it 
        }
        else if(parent->left == node) { //if node is on the left side of the parent, sets that side to point to null
            parent->left = nullptr; 
        }
        else {
            parent->right = nullptr;//if node is on right side of parent, sets that side to point to null
        }
        
        delete node; 

        cout << "successful" << endl; 
        return; 
    }
    //2nd Case : Node has one child // some from balanced trees PPT
   else if (node->left == nullptr || node->right == nullptr) {
        Node* child = nullptr; //initializes child of node pointer, which will be pointed to after node is deleted 
        
        if (node->left != nullptr) { //checks if child is left of node, child stores node childs value 
            child = node->left; 
        }
        else if (node->right != nullptr) { //otherwise stores value on right 
            child = node->right; 
        }

        if (parent == nullptr) { //if parent does not exist, the child becomes the root 
            root == child; 
        }
        else if(parent->left == node) { //if node is to the left of parent, parents left points to child 
            parent->left = child;
        }
        else {
            parent->right = child; //otherwise right points to child 
        }

        delete node;

        cout << "successful" << endl; 
        return;
    }

    else { //3rd Case : Node has two children (use of inorder successor(next node in inorder traversal of tree))
        Node* inorderSuccessor = node->right; //to find the inorder successor, we have to start at the node's rightmost child 
        Node* parentsSuccessor = node; 

        while (inorderSuccessor->left != nullptr) { //we then have to traverse until we reach the leftmost
            parentsSuccessor = inorderSuccessor; 
            inorderSuccessor = inorderSuccessor->left; 
        }
        node->ufid = inorderSuccessor->ufid; //once inorder successor is found, values are copied over to the node we will be removing 
        node->name = inorderSuccessor->name;
        
        if(parentsSuccessor == node) { //if parent of inorder successor is node being removed 
           parentsSuccessor->right = inorderSuccessor->right;  //right child of successor points to parent of the node being removed
        }
        else { //otherwise, right child of successor points to left child of its parent 
           parentsSuccessor->left = inorderSuccessor->right;
        }
        
        delete inorderSuccessor; 

        cout << "successful" << endl; 
        return;

    }
}

Node* AVLTree::findParent(string ufid) {// because tree is sorted and stored by ufids, only searching for parent by those values 
   if (root == nullptr) {
       return nullptr;
   }

   Node* node = root; 
   Node* parent = nullptr;

   while (node != nullptr) {
        if(ufid == node->ufid) {
            return parent;
        }
        else if(ufid < node->ufid) {
            parent = node;
            node = node->left;
        }
        else {
            parent = node;
            node = node->right;
        }
   }
   return nullptr; //ufid not found, returns null
}

void AVLTree::removeInorderN(string N) {
    int counter = 0; //keeps track of # of nodes we visit 
    bool isN = false; //checks if we have arrived at Nth ufid 

    if (root == nullptr) { //if tree is empty, returns unsuccessful 
        cout << "unsuccessful" << endl;
        return;
    }

    queue<Node*> myQueue; 
    Node* node = root;

    while (!myQueue.empty() || node != nullptr) { //using a queue to traverse through, when node != nullptr, we know we have traversed the whole tree
        while (node != nullptr) {
            myQueue.push(node); //pushes leftmost nodes on stack due to inorder traversal 
            node = node->left; 
        }
        node = myQueue.front();
        myQueue.pop();

        if (counter == stoi(N)) { //checks if node that we are currently at (counter) is the Nth node 
            isN = true;
            removeID(node->ufid); //if it is, we remove that node and break to return; 
            break;
        }
        counter++; //if it is not, we keep traversing until we find the Nth ufid
        node = node->right;
    }
    if (!isN) { //unless we find out that the Nth node doesn't exist after we traverse, then we print unsuccessful 
        cout << "unsuccessful" << endl;
    }
}

