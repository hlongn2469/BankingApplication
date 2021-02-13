// Bst.h
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020

#ifndef _BST_
#define _BST_
#include <iostream>
#include "Client.h"

// This class models a binary search tree to store client account
class Bst {

    friend ostream& operator<<(ostream & the_stream, const Bst& rhs);

public:
    Bst();
    ~Bst();
    bool isEmpty() const;
    int get_count() const;
    void flush();
    bool Retrieve(const int & acct_number, Client *& the_account);
    bool Insert(Client * the_account);
private:
    struct Node{
        Client* p_account;
        Node* left;
        Node* right;
    };
    Node* root_;
    bool retrieveHelper(Node* current, const int & target, Client *& retriever);
    bool insertHelper(Node*& root, Client* p_accountptr);
    void flushHelper(Node*& root);
    void printHelper(ostream & the_stream, Node* root) const;
    void print(ostream & the_stream) const;
};
#endif