// Bst.cpp
// CSS342 program5
// Implemented by Kray Nguyen on 9/12/2020
#include "Bst.h"

Bst::Bst() {
    root_ = nullptr;
}

Bst::~Bst() {
    flush();
}

bool Bst::isEmpty() const{
    if(root_ == nullptr){
        return true;
    }
    return false;
}

// Delete all parent leaf and children leaf within the tree
// to avoid memory leak
void Bst::flush() {
    if (this->root_ != nullptr){
        flushHelper(root_);
    }
    root_ = nullptr;
}

void Bst::flushHelper(Node *& delRoot){
    if (delRoot != nullptr) {
        flushHelper(delRoot->left);
        flushHelper(delRoot->right);
        delete delRoot->p_account;
        delete delRoot;
    }
}

// Get Client reference as a pointer if the account exists 
bool Bst::Retrieve(const int & acct_number, Client*& the_account) {
    return retrieveHelper(root_, acct_number, the_account);
}

bool Bst::retrieveHelper(Node* reRoot, const int & target, Client *& retriever) {

    // base case
    if(reRoot == nullptr){
        retriever = nullptr;
        return false;
    }

    // lesser case
    else if(target < reRoot->p_account->getFirstAccount()){
        return retrieveHelper(reRoot->left, target, retriever);
    }

    // greater case
    else if(target > reRoot->p_account->getFirstAccount()){
        return retrieveHelper(reRoot->right, target, retriever);
    } 

    // found
    else{
        retriever = reRoot->p_account;
        return true;
    }
}

// Insert Client pointer at correct place in the BST
bool Bst::Insert(Client* p_accountptr) {
    if(root_ == nullptr){
        root_ = new Node { p_accountptr, nullptr, nullptr };
        return true;
    } else {
        return insertHelper(root_, p_accountptr);
    }
}

bool Bst::insertHelper(Node*& root, Client* p_accountptr) {

    // base case
    if(root == nullptr){
        root = new Node { p_accountptr, nullptr, nullptr };
        return true;
    }

    // lesser case
    else if(*p_accountptr < *root->p_account){
        return insertHelper(root->left,p_accountptr);
    }

    // greater case
    else if(*p_accountptr > *root->p_account){
        return insertHelper(root->right,p_accountptr);
    } 

    // duplicate case
    else{
        return false;
    }
}

void Bst::print(ostream & the_stream) const {
    printHelper(the_stream, root_);
}

void Bst::printHelper(ostream & the_stream, Node* printRoot) const{
    if (printRoot == nullptr) {
        return;
    }
    else {
        printHelper(the_stream, printRoot->left);
        the_stream << *printRoot->p_account << endl;
        printHelper(the_stream, printRoot->right);
    }
}

ostream& operator<<(ostream & the_stream, const Bst& rhs) {
    rhs.print(the_stream);
    return the_stream;
}