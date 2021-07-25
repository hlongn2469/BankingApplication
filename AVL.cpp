// AVL.cpp
// extension of CSS342 program5
// Implemented by Kray Nguyen on 6/7/2021
#include "AVL.h"

AVL::AVL() {
    
}

AVL::~AVL() {
    
}

int AVL::getHeight(const Root n){
    if(n == nullptr){
        return 0;
    } else {
        return n->height;
    }
}


int AVL::setHeight(Root n){
    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

// Rotations
void AVL::RotateLeft(Root& n){
    Root r = n->right;
    if(getHeight(r->right) > getHeight(r->left)){
        rotateLeftOnce(n);
    } else {
        RotateLeftTwice(n);
    }
}

void AVL::RotateRight(Root& n){
    Root l = n->left;
    if(getHeight(r->left) > getHeight(r->right)){
        rotateRightOnce(n);
    } else {
        RotateRightTwice(n);
    }
}

void AVL::RotateLeftOnce(Root& n){
    Root r = n -> right;
    n -> right = r -> left;
    setHeight(n);

    r-> left = n;
    n = r;
    setHeight(n);
}

void AVL::RotateRightOnce(Root& n){
    Root l = n -> left;
    n -> left = l -> right;
    setHeight(n);

    l-> right = n;
    n = l;
    setHeight(n);
}

void AVL::RotateLeftTwice(Root& n){
    RotateRightOnce(n->right);
    RotateLeftOnce(n);
}

void AVL::RotateRightTwice(Root& n){
    RotateLeftOnce(n->left);
    RotateRightOnce(n);
}

void AVL::Rebalance(Root& n){
    if(getHeight(n->right) > getHeight(n->left)+1){
        rotateLeft(n);
    } else if(getHeight(n->left) > getHeight(n->right)+1){
        rotateRight(n);
    } else {
        setHeight(n);
    }
}
   
// Insert and retrieve
bool AVL::Insert(Client * the_account, Root& n){
    if(n == nullptr){
        n = new Node(the_account, NULL, NULL);
        return true;
    } else if(*the_account < *n->p_account){
        Insert(the_account, n->left);
        Rebalance(n);
    } else if(*the_account > *n->p_account){
        Insert(the_account, n->right);
        Rebalance(n);
    }
    return false;
}

bool AVL::Retrieve(const int & acct_number, Client *& retreiver, Root& n){
    if(n == nullptr){
        retreiver = nullptr;
        return false;
    }

    // lesser case
    else if(acct_number < n->p_account->getFirstAccount()){
        Retrieve(acct_number, retreiver, n->left);
    }

    // greater case
    else if(target > reRoot->p_account->getFirstAccount()){
        Retrieve(acct_number, retreiver, n->right);
    } 

    // found
    else{
        retreiver = n->p_account;
        return true;
    }
}