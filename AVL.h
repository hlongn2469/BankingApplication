// AVL.h
// Extension of CSS342 program5
// Implemented by Kray Nguyen on 6/7/2021

#ifndef _AVL_
#define _AVL_
#include <iostream>
#include "Client.h"

// This class models a binary search tree to store client account
class AVL {

    friend ostream& operator<<(ostream & the_stream, const Bst& rhs);

public:
    AVL();
    ~AVL();
    // access tree heights
    int getHeight(const Node* root);
    int setHeight(Node* root);

    // Rotations
    void RotateLeft(Node& root);
    void RotateRight(Node& root);
    void RotateLeftOnce(Node& root);
    void RotateRightOnce(Node& root);
    void RotateLeftTwice(Node& root);
    void RotateRightTwice(Node& root);
    void Rebalance(Node& root);
   
    // Insert and retrieve
    bool Insert(Client * the_account, Node& root);
    bool Retrieve(const int & acct_number, Client *& the_account, root& n);
private:
    typedef Node* Root;
    struct Node{
        Client* p_account;
        int height;
        Node* left;
        Node* right;
        
        Node(Client* acc, Node* left, Node* right){
            this-> p_account = acc;
            this-> left = left;
            this -> right = right;
            this -> height = 1 + max(getHeight(left), getHeight(right));
        }
    };
};
#endif